/* Copyright (C) 2007-2008 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/
#include "qemu_file.h"
#include "goldfish_trace.h"
#include "goldfish_vmem.h"
#include "sysemu.h"
#include "android-trace.h"
#ifdef CONFIG_MEMCHECK
#include "memcheck/memcheck.h"
#include "memcheck/memcheck_util.h"
#endif  

#define DEBUG   0

#if DEBUG
#  define D(...)  printf(__VA_ARGS__), fflush(stdout)
#else
#  define D(...)  ((void)0)
#endif

#define  DEBUG_PID  0

#if DEBUG_PID
#  define  DPID(...)  printf(__VA_ARGS__), fflush(stdout)
#else
#  define  DPID(...)  ((void)0)
#endif

extern void cpu_loop_exit(void);

extern int tracing;
extern const char *trace_filename;

static char exec_path[CLIENT_PAGE_SIZE];
static char exec_arg[CLIENT_PAGE_SIZE];
static unsigned long vstart;    
static unsigned long vend;      
static unsigned long eoff;      
static unsigned cmdlen;         
static unsigned pid;            
static unsigned tgid;           
static unsigned tid;            
static unsigned long dsaddr;    
static unsigned long unmap_start; 


static void trace_dev_write(void *opaque, target_phys_addr_t offset, uint32_t value)
{
    trace_dev_state *s = (trace_dev_state *)opaque;

    (void)s;

    switch (offset >> 2) {
    case TRACE_DEV_REG_SWITCH:  
        DPID("QEMU.trace: context switch tid=%u\n", value);
        if (trace_filename != NULL) {
            trace_switch(value);
            D("QEMU.trace: kernel, context switch %u\n", value);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            memcheck_switch(value);
        }
#endif  
        tid = (unsigned) value;
        break;
    case TRACE_DEV_REG_TGID:    
        DPID("QEMU.trace: tgid=%u\n", value);
        tgid = value;
        if (trace_filename != NULL) {
            D("QEMU.trace: kernel, tgid %u\n", value);
        }
        break;
    case TRACE_DEV_REG_FORK:    
        DPID("QEMU.trace: fork (pid=%d tgid=%d value=%d)\n", pid, tgid, value);
        if (trace_filename != NULL) {
            trace_fork(tgid, value);
            D("QEMU.trace: kernel, fork %u\n", value);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            memcheck_fork(tgid, value);
        }
#endif  
        break;
    case TRACE_DEV_REG_CLONE:    
        DPID("QEMU.trace: clone (pid=%d tgid=%d value=%d)\n", pid, tgid, value);
        if (trace_filename != NULL) {
            trace_clone(tgid, value);
            D("QEMU.trace: kernel, clone %u\n", value);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            memcheck_clone(tgid, value);
        }
#endif  
        break;
    case TRACE_DEV_REG_EXECVE_VMSTART:  
        vstart = value;
        break;
    case TRACE_DEV_REG_EXECVE_VMEND:    
        vend = value;
        break;
    case TRACE_DEV_REG_EXECVE_OFFSET:   
        eoff = value;
        break;
    case TRACE_DEV_REG_EXECVE_EXEPATH:  
        vstrcpy(value, exec_path, CLIENT_PAGE_SIZE);
        if (trace_filename != NULL) {
            trace_init_exec(vstart, vend, eoff, exec_path);
            D("QEMU.trace: kernel, init exec [%lx,%lx]@%lx [%s]\n",
              vstart, vend, eoff, exec_path);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            if (exec_path[0] == '\0') {
                
                
                memcheck_get_guest_kernel_string(exec_path, value, CLIENT_PAGE_SIZE);
            }
            memcheck_mmap_exepath(vstart, vend, eoff, exec_path);
        }
#endif  
        exec_path[0] = 0;
        break;
    case TRACE_DEV_REG_CMDLINE_LEN:     
        cmdlen = value;
        break;
    case TRACE_DEV_REG_CMDLINE:         
        safe_memory_rw_debug(cpu_single_env, value, (uint8_t*)exec_arg, cmdlen, 0);
        if (trace_filename != NULL) {
            trace_execve(exec_arg, cmdlen);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            memcheck_set_cmd_line(exec_arg, cmdlen);
        }
#endif  
#if DEBUG || DEBUG_PID
        if (trace_filename != NULL) {
            int i;
            for (i = 0; i < cmdlen; i ++)
                if (i != cmdlen - 1 && exec_arg[i] == 0)
                    exec_arg[i] = ' ';
            printf("QEMU.trace: kernel, execve %s[%d]\n", exec_arg, cmdlen);
            exec_arg[0] = 0;
        }
#endif
        break;
    case TRACE_DEV_REG_EXIT:            
        DPID("QEMU.trace: exit tid=%u\n", value);
        if (trace_filename != NULL) {
            trace_exit(value);
            D("QEMU.trace: kernel, exit %x\n", value);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            memcheck_exit(value);
        }
#endif  
        break;
    case TRACE_DEV_REG_NAME:            
        vstrcpy(value, exec_path, CLIENT_PAGE_SIZE);
        DPID("QEMU.trace: thread name=%s\n", exec_path);

        
        int len = strlen(exec_path);
        if (exec_path[len - 1] == '\n') {
            exec_path[len - 1] = 0;
        }
        if (trace_filename != NULL) {
            trace_name(exec_path);
            D("QEMU.trace: kernel, name %s\n", exec_path);
        }
        break;
    case TRACE_DEV_REG_MMAP_EXEPATH:    
        vstrcpy(value, exec_path, CLIENT_PAGE_SIZE);
        DPID("QEMU.trace: mmap exe=%s\n", exec_path);
        if (trace_filename != NULL) {
            trace_mmap(vstart, vend, eoff, exec_path);
            D("QEMU.trace: kernel, mmap [%lx,%lx]@%lx [%s]\n", vstart, vend, eoff, exec_path);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            if (exec_path[0] == '\0') {
                
                
                memcheck_get_guest_kernel_string(exec_path, value, CLIENT_PAGE_SIZE);
            }
            memcheck_mmap_exepath(vstart, vend, eoff, exec_path);
        }
#endif  
        exec_path[0] = 0;
        break;
    case TRACE_DEV_REG_INIT_PID:        
        pid = value;
        DPID("QEMU.trace: pid=%d\n", value);
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            memcheck_init_pid(value);
        }
#endif  
        break;
    case TRACE_DEV_REG_INIT_NAME:       
        vstrcpy(value, exec_path, CLIENT_PAGE_SIZE);
        DPID("QEMU.trace: tgid=%d pid=%d name=%s\n", tgid, pid, exec_path);
        if (trace_filename != NULL) {
            trace_init_name(tgid, pid, exec_path);
            D("QEMU.trace: kernel, init name %u [%s]\n", pid, exec_path);
        }
        exec_path[0] = 0;
        break;

    case TRACE_DEV_REG_DYN_SYM_ADDR:    
        dsaddr = value;
        break;
    case TRACE_DEV_REG_DYN_SYM:         
        vstrcpy(value, exec_arg, CLIENT_PAGE_SIZE);
        if (trace_filename != NULL) {
            trace_dynamic_symbol_add(dsaddr, exec_arg);
            D("QEMU.trace: dynamic symbol %lx:%s\n", dsaddr, exec_arg);
        }
        exec_arg[0] = 0;
        break;
    case TRACE_DEV_REG_REMOVE_ADDR:         
        if (trace_filename != NULL) {
            trace_dynamic_symbol_remove(value);
            D("QEMU.trace: dynamic symbol remove %lx\n", dsaddr);
        }
        break;

    case TRACE_DEV_REG_PRINT_STR:       
        vstrcpy(value, exec_arg, CLIENT_PAGE_SIZE);
        printf("%s", exec_arg);
        exec_arg[0] = 0;
        break;
    case TRACE_DEV_REG_PRINT_NUM_DEC:   
        printf("%d", value);
        break;
    case TRACE_DEV_REG_PRINT_NUM_HEX:   
        printf("%x", value);
        break;

    case TRACE_DEV_REG_STOP_EMU:        
        if (trace_filename != NULL) {
            
            
            trace_exception(0);
        }
        cpu_single_env->exception_index = EXCP_HLT;
        cpu_single_env->halted = 1;
        qemu_system_shutdown_request();
        cpu_loop_exit();
        break;

    case TRACE_DEV_REG_ENABLE:          
        if (value == 1) {
            if (trace_filename != NULL) {
                start_tracing();
            }
        }
        else if (value == 0) {
            if (trace_filename != NULL) {
                stop_tracing();

                
                
                trace_exception(0);
            }
        }
        break;

    case TRACE_DEV_REG_UNMAP_START:
        unmap_start = value;
        break;
    case TRACE_DEV_REG_UNMAP_END:
        if (trace_filename != NULL) {
            trace_munmap(unmap_start, value);
        }
#ifdef CONFIG_MEMCHECK
        if (memcheck_enabled) {
            memcheck_unmap(unmap_start, value);
        }
#endif  
        break;

    case TRACE_DEV_REG_METHOD_ENTRY:
    case TRACE_DEV_REG_METHOD_EXIT:
    case TRACE_DEV_REG_METHOD_EXCEPTION:
    case TRACE_DEV_REG_NATIVE_ENTRY:
    case TRACE_DEV_REG_NATIVE_EXIT:
    case TRACE_DEV_REG_NATIVE_EXCEPTION:
        if (trace_filename != NULL) {
            if (tracing) {
                int call_type = (offset - 4096) >> 2;
                trace_interpreted_method(value, call_type);
            }
        }
        break;

#ifdef CONFIG_MEMCHECK
    case TRACE_DEV_REG_MALLOC:
        if (memcheck_enabled) {
            memcheck_guest_alloc(value);
        }
        break;

    case TRACE_DEV_REG_FREE_PTR:
        if (memcheck_enabled) {
            memcheck_guest_free(value);
        }
        break;

    case TRACE_DEV_REG_QUERY_MALLOC:
        if (memcheck_enabled) {
            memcheck_guest_query_malloc(value);
        }
        break;

    case TRACE_DEV_REG_LIBC_INIT:
        if (memcheck_enabled) {
            memcheck_guest_libc_initialized(value);
        }
        break;

    case TRACE_DEV_REG_PRINT_USER_STR:
        if (memcheck_enabled) {
            memcheck_guest_print_str(value);
        }
        break;
#endif 

    default:
        if (offset < 4096) {
            cpu_abort(cpu_single_env, "trace_dev_write: Bad offset %x\n", offset);
        } else {
            D("%s: offset=%d (0x%x) value=%d (0x%x)\n", __FUNCTION__, offset,
              offset, value, value);
        }
        break;
    }
}

static uint32_t trace_dev_read(void *opaque, target_phys_addr_t offset)
{
    trace_dev_state *s = (trace_dev_state *)opaque;

    (void)s;

    switch (offset >> 2) {
    case TRACE_DEV_REG_ENABLE:          
        return tracing;

    default:
        if (offset < 4096) {
            cpu_abort(cpu_single_env, "trace_dev_read: Bad offset %x\n", offset);
        } else {
            D("%s: offset=%d (0x%x)\n", __FUNCTION__, offset, offset);
        }
        return 0;
    }
    return 0;
}

static CPUReadMemoryFunc *trace_dev_readfn[] = {
   trace_dev_read,
   trace_dev_read,
   trace_dev_read
};

static CPUWriteMemoryFunc *trace_dev_writefn[] = {
   trace_dev_write,
   trace_dev_write,
   trace_dev_write
};

void trace_dev_init()
{
    trace_dev_state *s;

    s = (trace_dev_state *)qemu_mallocz(sizeof(trace_dev_state));
    s->dev.name = "qemu_trace";
    s->dev.id = -1;
    s->dev.base = 0;       
    s->dev.size = 0x2000;
    s->dev.irq = 0;
    s->dev.irq_count = 0;

    goldfish_device_add(&s->dev, trace_dev_readfn, trace_dev_writefn, s);

    exec_path[0] = exec_arg[0] = '\0';
}
