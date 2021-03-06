/* Copyright (C) 2007-2010 The Android Open Source Project
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


#ifndef QEMU_MEMCHECK_MEMCHECK_LOGGING_H
#define QEMU_MEMCHECK_MEMCHECK_LOGGING_H

#include "qemu-common.h"
#include "android/utils/debug.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MD(...)  VERBOSE_PRINT(memcheck, __VA_ARGS__)

#define ME(...)  \
    do { if (VERBOSE_CHECK(memcheck)) derror(__VA_ARGS__); } while (0)


#define TRACE_PROC_FORK_ENABLED                 0x00000001
#define TRACE_PROC_CLONE_ENABLED                0x00000002
#define TRACE_PROC_NEW_PID_ENABLED              0x00000004
#define TRACE_PROC_START_ENABLED                0x00000008
#define TRACE_PROC_EXIT_ENABLED                 0x00000010
#define TRACE_PROC_LIBC_INIT_ENABLED            0x00000020
#define TRACE_CHECK_LEAK_ENABLED                0x00000040
#define TRACE_CHECK_INVALID_PTR_ENABLED         0x00000080
#define TRACE_CHECK_READ_VIOLATION_ENABLED      0x00000100
#define TRACE_CHECK_WRITE_VIOLATION_ENABLED     0x00000200
#define TRACE_PROC_MMAP_ENABLED                 0x00000400
#define TRACE_ALL_ENABLED   (TRACE_PROC_FORK_ENABLED                | \
                             TRACE_PROC_CLONE_ENABLED               | \
                             TRACE_PROC_NEW_PID_ENABLED             | \
                             TRACE_PROC_START_ENABLED               | \
                             TRACE_PROC_LIBC_INIT_ENABLED           | \
                             TRACE_PROC_EXIT_ENABLED                | \
                             TRACE_CHECK_INVALID_PTR_ENABLED        | \
                             TRACE_CHECK_READ_VIOLATION_ENABLED     | \
                             TRACE_CHECK_WRITE_VIOLATION_ENABLED    | \
                             TRACE_PROC_MMAP_ENABLED                | \
                             TRACE_CHECK_LEAK_ENABLED)

#define T(level, ...)                                   \
    do {                                                \
        if (trace_flags & TRACE_##level##_ENABLED) {    \
            printf(__VA_ARGS__);                        \
        }                                               \
    } while (0)

extern uint32_t trace_flags;

#ifdef __cplusplus
};  
#endif

#endif  
