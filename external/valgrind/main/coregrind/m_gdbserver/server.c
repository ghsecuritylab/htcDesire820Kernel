/* Main code for remote server for GDB.
   Copyright (C) 1989, 1993, 1994, 1995, 1997, 1998, 1999, 2000, 2002, 2003,
   2004, 2005, 2006, 2011
   Free Software Foundation, Inc.

   This file is part of GDB.
   It has been modified to integrate it in valgrind

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

#include "server.h"
#include "regdef.h"
#include "pub_core_options.h"
#include "pub_core_translate.h"
#include "pub_core_mallocfree.h"
#include "pub_core_initimg.h"

unsigned long cont_thread;
unsigned long general_thread;
unsigned long step_thread;
unsigned long thread_from_wait;
unsigned long old_thread_from_wait;

int pass_signals[TARGET_SIGNAL_LAST]; 

static Bool resume_reply_packet_needed = False;

VG_MINIMAL_JMP_BUF(toplevel);


static
int decode_xfer_read (char *buf, char **annex, CORE_ADDR *ofs, unsigned int *len)
{
   
   *annex = buf;
   while (*buf && *buf != ':')
      buf++;
   if (*buf == '\0')
      return -1;
   *buf++ = 0;

   decode_m_packet (buf, ofs, len);

   return 0;
}

static
int write_qxfer_response (char *buf, unsigned char *data, int len, int is_more)
{
   int out_len;

   if (is_more)
      buf[0] = 'm';
   else
      buf[0] = 'l';

   return remote_escape_output (data, len, (unsigned char *) buf + 1, &out_len,
                                PBUFSIZ - POVERHSIZ - 1) + 1;
}

static Bool initial_valgrind_sink_saved = False;
static OutputSink initial_valgrind_sink;

static Bool command_output_to_log = False;

void reset_valgrind_sink(char *info)
{
   if (VG_(log_output_sink).fd != initial_valgrind_sink.fd
       && initial_valgrind_sink_saved) {
      VG_(log_output_sink).fd = initial_valgrind_sink.fd;
      VG_(umsg) ("Reset valgrind output to log (%s)\n",
                 (info = NULL ? "" : info));
   }
}

static
void kill_request (char *msg)
{
   VG_(umsg) ("%s", msg);
   remote_close();
   VG_(exit) (0);
}

static
int handle_gdb_valgrind_command (char* mon, OutputSink* sink_wanted_at_return)
{
   UWord ret = 0;
   char s[strlen(mon)+1]; 
   char* wcmd;
   Char* ssaveptr;
   char* endptr;
   int   kwdid;
   int int_value;

   vg_assert (initial_valgrind_sink_saved);

   strcpy (s, mon);
   wcmd = strtok_r (s, " ", &ssaveptr);
   switch (VG_(keyword_id) ("help v.set v.info v.wait v.kill v.translate",
                            wcmd, kwd_report_duplicated_matches)) {
   case -2:
      ret = 1;
      break;
   case -1: 
      break;
   case  0: 
      ret = 1;
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      if (wcmd == NULL) {
         int_value = 0;
      } else {
         switch (VG_(keyword_id) ("debug", wcmd, kwd_report_all)) {
         case -2: int_value = 0; break;
         case -1: int_value = 0; break;
         case  0: int_value = 1; break;
         default: tl_assert (0);
         }
      }

      VG_(gdb_printf) (
"general valgrind monitor commands:\n"
"  help [debug]             : monitor command help. With debug: + debugging commands\n"
"  v.wait [<ms>]           : sleep <ms> (default 0) then continue\n"
"  v.info all_errors       : show all errors found so far\n"
"  v.info last_error       : show last error found\n"
"  v.info n_errs_found     : show the nr of errors found so far\n"
"  v.kill                  : kill the Valgrind process\n"
"  v.set gdb_output        : set valgrind output to gdb\n"
"  v.set log_output        : set valgrind output to log\n"
"  v.set mixed_output      : set valgrind output to log, interactive output to gdb\n"
"  v.set vgdb-error <errornr> : debug me at error >= <errornr> \n");
      if (int_value) { VG_(gdb_printf) (
"debugging valgrind internals monitor commands:\n"
"  v.info gdbserver_status : show gdbserver status\n"
"  v.info memory [aspacemgr] : show valgrind heap memory stats\n"
"     (with aspacemgr arg, also shows valgrind segments on log ouput)\n"
"  v.info scheduler        : show valgrind thread state and stacktrace\n"
"  v.set debuglog <level>  : set valgrind debug log level to <level>\n"
"  v.translate <addr> [<traceflags>]  : debug translation of <addr> with <traceflags>\n"
"    (default traceflags 0b00100000 : show after instrumentation)\n"
"   An additional flag  0b100000000 allows to show gdbserver instrumentation\n");
      }
      break;
   case  1: 
      ret = 1;
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      switch (kwdid = VG_(keyword_id) 
              ("vgdb-error debuglog gdb_output log_output mixed_output",
               wcmd, kwd_report_all)) {
      case -2:
      case -1: 
         break;
      case 0: 
      case 1: 
         wcmd = strtok_r (NULL, " ", &ssaveptr);
         if (wcmd == NULL) {
            int_value = 0;
            endptr = "empty"; 
         } else {
            int_value = strtol (wcmd, &endptr, 10);
         }
         if (*endptr != '\0') {
            VG_(gdb_printf) ("missing or malformed integer value\n");
         } else if (kwdid == 0) {
            VG_(gdb_printf) ("vgdb-error value changed from %d to %d\n",
                             VG_(dyn_vgdb_error), int_value);
            VG_(dyn_vgdb_error) = int_value;
         } else if (kwdid == 1) {
            VG_(gdb_printf) ("debuglog value changed from %d to %d\n",
                             VG_(debugLog_getLevel)(), int_value);
            VG_(debugLog_startup) (int_value, "gdbsrv");
         } else {
            vg_assert (0);
         }
         break;
      case 2: 
         (*sink_wanted_at_return).fd = -2;
         command_output_to_log = False;
         VG_(gdb_printf) ("valgrind output will go to gdb\n");
         break;
      case 3: 
         (*sink_wanted_at_return).fd = initial_valgrind_sink.fd;
         command_output_to_log = True;
         VG_(gdb_printf) ("valgrind output will go to log\n");
         break;
      case 4: 
         (*sink_wanted_at_return).fd = initial_valgrind_sink.fd;
         command_output_to_log = False;
         VG_(gdb_printf)
            ("valgrind output will go to log, interactive output will go to gdb\n");
         break;
      default:
         vg_assert (0);
      }
      break;
   case  2:  {
      ret = 1;
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      switch (kwdid = VG_(keyword_id) 
              ("all_errors n_errs_found last_error gdbserver_status memory"
               " scheduler",
               wcmd, kwd_report_all)) {
      case -2:
      case -1: 
         break;
      case 0: 
         
         VG_(show_all_errors)( 2,  False);
         break;
      case  1: 
         VG_(gdb_printf) ("n_errs_found %d n_errs_shown %d (vgdb-error %d)\n", 
                          VG_(get_n_errs_found) (),
                          VG_(get_n_errs_shown) (),
                          VG_(dyn_vgdb_error));
         break;
      case 2: 
         VG_(show_last_error)();
         break;
      case  3: 
         VG_(gdbserver_status_output)();
         break;
      case  4: 
         VG_(print_all_arena_stats) ();
         if (VG_(clo_profile_heap))
            VG_(print_arena_cc_analysis) ();
         wcmd = strtok_r (NULL, " ", &ssaveptr);
         if (wcmd != NULL) {
            switch (VG_(keyword_id) ("aspacemgr", wcmd, kwd_report_all)) {
            case -2:
            case -1: break;
            case  0: 
               VG_(am_show_nsegments) (0, "gdbserver v.info memory aspacemgr");
               break;
            default: tl_assert (0);
            }
         }

         ret = 1;
         break;
      case  5: 
         VG_(show_sched_status) ();
         ret = 1;
         break;
      default:
         vg_assert(0);
      }
      break;
   }
   case  3: 
      wcmd = strtok_r (NULL, " ", &ssaveptr);
      if (wcmd != NULL) {
         int_value = strtol (wcmd, &endptr, 10);
         VG_(gdb_printf) ("gdbserver: continuing in %d ms ...\n", int_value);
         VG_(poll)(NULL, 0, int_value);
      }
      VG_(gdb_printf) ("gdbserver: continuing after wait ...\n");
      ret = 1;
      break;
   case  4: 
      kill_request ("monitor command request to kill this process\n");
      break;
   case  5: { 
      Addr address;
      SizeT verbosity = 0x20;
      
      ret = 1;

      VG_(strtok_get_address_and_size) (&address, &verbosity, &ssaveptr);
      if (address != (Addr) 0 || verbosity != 0) {
         int saved_command_output_to_log = command_output_to_log;
         int saved_fd = VG_(log_output_sink).fd;
         Bool single_stepping_on_entry = valgrind_single_stepping();
         int vex_verbosity = verbosity & 0xff;
         VG_(log_output_sink).fd = initial_valgrind_sink.fd;
         if ((verbosity & 0x100) && !single_stepping_on_entry) {
            valgrind_set_single_stepping(True); 
            
         }
#        if defined(VGA_arm)
         
         
         address = thumb_pc (address);
#        endif

         VG_(translate) ( 0 ,
                          address,
                          True, 
                          (Int) vex_verbosity,
                          0,
                          True);
         if ((verbosity & 0x100) && !single_stepping_on_entry) {
            valgrind_set_single_stepping(False);
            
         }
         command_output_to_log = saved_command_output_to_log;
         VG_(log_output_sink).fd = saved_fd;
      }
      break;
   }

   default:
      vg_assert (0);
   }
   return ret;
}

static
int handle_gdb_monitor_command (char* mon)
{
   UWord ret = 0;
   UWord tool_ret = 0;
   
   
   
   OutputSink sink_wanted_at_return = VG_(log_output_sink);

   if (!initial_valgrind_sink_saved) {
      
      initial_valgrind_sink = sink_wanted_at_return;
      initial_valgrind_sink_saved = True;
   }

   if (!command_output_to_log)
      VG_(log_output_sink).fd = -2; 

   ret = handle_gdb_valgrind_command (mon, &sink_wanted_at_return);

   if (VG_(needs).client_requests) {
      Int save_dyn_vgdb_error = VG_(dyn_vgdb_error);
      UWord arg[2];
      VG_(dyn_vgdb_error) = 999999999;
      arg[0] = (UWord) VG_USERREQ__GDB_MONITOR_COMMAND;
      arg[1] = (UWord) mon;
      VG_TDICT_CALL(tool_handle_client_request, VG_(running_tid), arg,
                    &tool_ret);
      VG_(dyn_vgdb_error) = save_dyn_vgdb_error;
   }

   
   VG_(log_output_sink).fd = sink_wanted_at_return.fd;
   if (ret | tool_ret)
      return 1;
   else
      return 0;
}


static
void handle_set (char *arg_own_buf, int *new_packet_len_p)
{
   if (strcmp ("QStartNoAckMode", arg_own_buf) == 0) {
      noack_mode = True;
      write_ok (arg_own_buf);
      return;
   }

   if (strncmp ("QPassSignals:", arg_own_buf, 13) == 0) {
      int i;
      char *from, *to;
      char *end = arg_own_buf + strlen(arg_own_buf);
      CORE_ADDR sig;
      for (i = 0; i < TARGET_SIGNAL_LAST; i++)
         pass_signals[i] = 0;
     
      from = arg_own_buf + 13;
      while (from < end) {
         to = strchr(from, ';');
         if (to == NULL) to = end;
         decode_address (&sig, from, to - from);
         pass_signals[(int)sig] = 1;
         dlog(1, "pass_signal gdb_nr %d %s\n",
              (int)sig, target_signal_to_name(sig));
         from = to;
         if (*from == ';') from++;
      }
      write_ok (arg_own_buf);
      return;
   }
   arg_own_buf[0] = 0;
}

static
void handle_query (char *arg_own_buf, int *new_packet_len_p)
{
   static struct inferior_list_entry *thread_ptr;

   
   if (strncmp ("qRcmd,", arg_own_buf, 6) == 0) {
      char *p = arg_own_buf + 6;
      int cmdlen = strlen(p)/2;
      char cmd[cmdlen+1];
      
      if (unhexify (cmd, p, cmdlen) != cmdlen) {
         write_enn (arg_own_buf);
         return;
      }
      cmd[cmdlen] = '\0';
       
      if (handle_gdb_monitor_command (cmd)) {
         VG_(message_flush) ();
         write_ok (arg_own_buf);
         return;
      } else {
         
         VG_(gdb_printf) 
            ("command '%s' not recognised\n"
             "In gdb,     try 'monitor help'\n"
             "In a shell, try 'vgdb help'\n",
             cmd);
         write_ok (arg_own_buf);
         return;
      }
   }

   
   if (strncmp ("qThreadExtraInfo,", arg_own_buf, 17) == 0) {
      unsigned long gdb_id;
      struct thread_info *ti;
      ThreadState *tst;
      char status[100];
      
      gdb_id = strtoul (&arg_own_buf[17], NULL, 16);
      ti = gdb_id_to_thread (gdb_id);
      if (ti != NULL) {
         tst = (ThreadState *) inferior_target_data (ti);
         
         VG_(snprintf) (status, sizeof(status), "tid %d %s",
                        tst->tid, 
                        VG_(name_of_ThreadStatus)(tst->status));
         hexify (arg_own_buf, status, strlen(status));
         return;
      } else {
         write_enn (arg_own_buf);
         return;
      }
   }
   
   if (strcmp ("qAttached", arg_own_buf) == 0) {
      
      arg_own_buf[0] = '1';
      arg_own_buf[1] = 0;
      return;
   }

   if (strcmp ("qSymbol::", arg_own_buf) == 0) {
      
      write_ok (arg_own_buf);
      return;
   }

   if (strcmp ("qfThreadInfo", arg_own_buf) == 0) {
      thread_ptr = all_threads.head;
      VG_(sprintf) (arg_own_buf, "m%x", 
                    thread_to_gdb_id ((struct thread_info *)thread_ptr));
      thread_ptr = thread_ptr->next;
      return;
   }

   if (strcmp ("qsThreadInfo", arg_own_buf) == 0) {
      if (thread_ptr != NULL) {
         VG_(sprintf) (arg_own_buf, "m%x", 
                       thread_to_gdb_id ((struct thread_info *)thread_ptr));
         thread_ptr = thread_ptr->next;
         return;
      } else {
         VG_(sprintf) (arg_own_buf, "l");
         return;
      }
   }

   if (valgrind_target_xml(VG_(clo_vgdb_shadow_registers)) != NULL
        && strncmp ("qXfer:features:read:", arg_own_buf, 20) == 0) {
      CORE_ADDR ofs;
      unsigned int len, doc_len;
      char *annex = NULL;
      
      
      int fd;

      
      if (decode_xfer_read (arg_own_buf + 20, &annex, &ofs, &len) < 0) {
         strcpy (arg_own_buf, "E00");
         return;
      }
      
      if (strcmp (annex, "target.xml") == 0) {
         annex = valgrind_target_xml(VG_(clo_vgdb_shadow_registers));
         if (annex != NULL && VG_(clo_vgdb_shadow_registers)) {
            
            initialize_shadow_low(True);
         }
         if (annex == NULL) {
            strcpy (arg_own_buf, "E00");
            return;
         }
      }

      {
         char doc[VG_(strlen)(VG_(libdir)) + 1 + VG_(strlen)(annex) + 1];
         struct vg_stat stat_doc;
         char toread[len];
         int len_read;

         VG_(sprintf)(doc, "%s/%s", VG_(libdir), annex);
         fd = VG_(fd_open) (doc, VKI_O_RDONLY, 0);
         if (fd == -1) {
            strcpy (arg_own_buf, "E00");
            return;
         }
         if (VG_(fstat) (fd, &stat_doc) != 0) {
            VG_(close) (fd);
            strcpy (arg_own_buf, "E00");
            return;
         }
         doc_len = stat_doc.size;
         
         if (len > PBUFSIZ - POVERHSIZ)
            len = PBUFSIZ - POVERHSIZ;

         if (ofs > doc_len) {
            write_enn (arg_own_buf);
            VG_(close) (fd);
            return;
         }
         VG_(lseek) (fd, ofs, VKI_SEEK_SET);
         len_read = VG_(read) (fd, toread, len);
         *new_packet_len_p = write_qxfer_response (arg_own_buf, toread,
                                                   len_read, ofs + len_read < doc_len);
         VG_(close) (fd);
         return;
      }
   }

   if (strncmp ("qXfer:auxv:read:", arg_own_buf, 16) == 0) {
      unsigned char *data;
      int n;
      CORE_ADDR ofs;
      unsigned int len;
      char *annex;

      
      if (decode_xfer_read (arg_own_buf + 16, &annex, &ofs, &len) < 0
          || annex[0] != '\0') {
         strcpy (arg_own_buf, "E00");
         return;
      }

      if (len > PBUFSIZ - 2)
         len = PBUFSIZ - 2;
      data = malloc (len);

      {
         UWord *client_auxv = VG_(client_auxv);
         unsigned int client_auxv_len = 0;
         while (*client_auxv != 0) {
            dlog(4, "auxv %lld %llx\n",
                 (ULong)*client_auxv,
                 (ULong)*(client_auxv+1));
            client_auxv++;
            client_auxv++;
            client_auxv_len += 2 * sizeof(UWord);
         }
         client_auxv_len += 2 * sizeof(UWord);
         dlog(4, "auxv len %d\n", client_auxv_len);

         if (ofs >= client_auxv_len)
            n = -1;
         else {
            n = client_auxv_len - ofs;
            VG_(memcpy) (data, (unsigned char *) VG_(client_auxv), n);
         }
      }

      if (n < 0)
         write_enn (arg_own_buf);
      else if (n > len)
         *new_packet_len_p = write_qxfer_response (arg_own_buf, data, len, 1);
      else
         *new_packet_len_p = write_qxfer_response (arg_own_buf, data, n, 0);
      
      free (data);
      
      return;
   }


   
   if (strncmp ("qSupported", arg_own_buf, 10) == 0
       && (arg_own_buf[10] == ':' || arg_own_buf[10] == '\0')) {
      VG_(sprintf) (arg_own_buf, "PacketSize=%x", PBUFSIZ - 1);
      
      strcat (arg_own_buf, ";QStartNoAckMode+");
      strcat (arg_own_buf, ";QPassSignals+");
      if (VG_(client_auxv))
         strcat (arg_own_buf, ";qXfer:auxv:read+");

      if (valgrind_target_xml(VG_(clo_vgdb_shadow_registers)) != NULL) {
         strcat (arg_own_buf, ";qXfer:features:read+");
         initialize_shadow_low(False);
      }
      return;
   }

   arg_own_buf[0] = 0;
}

static
void handle_v_requests (char *arg_own_buf, char *status, int *zignal)
{
   

   arg_own_buf[0] = 0;
   return;
}

static
void myresume (int step, int sig)
{
   struct thread_resume resume_info[2];
   int n = 0;

   if (step || sig) {
      resume_info[0].step = step;
      resume_info[0].sig = sig;
      n++;
   }
   resume_info[n].step = 0;
   resume_info[n].sig = 0;

   resume_reply_packet_needed = True;
   valgrind_resume (resume_info);
}

static char *own_buf;
static unsigned char *mem_buf;

void gdbserver_init (void)
{
   dlog(1, "gdbserver_init gdbserver embedded in valgrind: %s\n", version);
   noack_mode = False;
   valgrind_initialize_target ();
   
   
   if (own_buf == NULL)
      own_buf = malloc (PBUFSIZ);
   if (mem_buf == NULL)
      mem_buf = malloc (PBUFSIZ);
}

void gdbserver_terminate (void)
{
   
   if (VG_MINIMAL_SETJMP(toplevel)) {
      dlog(0, "error caused VG_MINIMAL_LONGJMP to gdbserver_terminate\n");
      return;
   }
   remote_close();
}

void server_main (void)
{
   static char status;
   static int zignal;

   char ch;
   int i = 0;
   unsigned int len;
   CORE_ADDR mem_addr;

   zignal = valgrind_wait (&status);
   if (VG_MINIMAL_SETJMP(toplevel)) {
      dlog(0, "error caused VG_MINIMAL_LONGJMP to server_main\n");
   }
   while (1) {
      unsigned char sig;
      int packet_len;
      int new_packet_len = -1;
      
      if (resume_reply_packet_needed) {
         resume_reply_packet_needed = False;
         prepare_resume_reply (own_buf, status, zignal);
         putpkt (own_buf);
      }

      packet_len = getpkt (own_buf);
      if (packet_len <= 0)
         break;

      i = 0;
      ch = own_buf[i++];
      switch (ch) {
      case 'Q':
         handle_set (own_buf, &new_packet_len);
         break;
      case 'q':
         handle_query (own_buf, &new_packet_len);
         break;
      case 'd':
         
         own_buf[0] = '\0';
         break;
      case 'D':
         reset_valgrind_sink("gdb detaching from process");

         write_ok (own_buf);
         putpkt (own_buf);
         remote_finish (reset_after_error);
         remote_open (VG_(clo_vgdb_prefix));
         myresume (0, 0);
         resume_reply_packet_needed = False;
         return;
      case '!':
         own_buf[0] = '\0';
         break;
      case '?':
         prepare_resume_reply (own_buf, status, zignal);
         break;
      case 'H':
         if (own_buf[1] == 'c' || own_buf[1] == 'g' || own_buf[1] == 's') {
            unsigned long gdb_id, thread_id;
            
            gdb_id = strtoul (&own_buf[2], NULL, 16);
            thread_id = gdb_id_to_thread_id (gdb_id);
            if (thread_id == 0) {
               write_enn (own_buf);
               break;
            }

            if (own_buf[1] == 'g') {
               general_thread = thread_id;
               set_desired_inferior (1);
            } else if (own_buf[1] == 'c') {
               cont_thread = thread_id;
            } else if (own_buf[1] == 's') {
               step_thread = thread_id;
            }
            
            write_ok (own_buf);
         } else {
            own_buf[0] = '\0';
         }
         break;
      case 'g':
         set_desired_inferior (1);
         registers_to_string (own_buf);
         break;
      case 'G':
         set_desired_inferior (1);
         registers_from_string (&own_buf[1]);
         write_ok (own_buf);
         break;
      case 'P': {
         int regno;
         char *regbytes;
         Bool mod;
         ThreadState *tst;
         regno = strtol(&own_buf[1], NULL, 16);
         regbytes = strchr(&own_buf[0], '=') + 1;
         set_desired_inferior (1);
         tst = (ThreadState *) inferior_target_data (current_inferior);
         if (tst->status == VgTs_Runnable || tst->status == VgTs_Yielding) {
            supply_register_from_string (regno, regbytes, &mod);
            write_ok (own_buf);
         } else {
            VG_(sprintf) 
               (own_buf,
"E.\n"
"ERROR changing register %s regno %d\n"
"gdb commands changing registers (pc, sp, ...) (e.g. 'jump',\n"
"set pc, calling from gdb a function in the debugged process, ...)\n"
"can only be accepted if the thread is VgTs_Runnable or VgTs_Yielding state\n"
"Thread status is %s\n",
                find_register_by_number (regno)->name, regno,
                VG_(name_of_ThreadStatus)(tst->status));
            if (VG_(clo_verbosity) > 1)
               VG_(umsg) ("%s\n", own_buf);
         }
         break;            
      }
      case 'm':
         decode_m_packet (&own_buf[1], &mem_addr, &len);
         if (valgrind_read_memory (mem_addr, mem_buf, len) == 0)
            convert_int_to_ascii (mem_buf, own_buf, len);
         else
            write_enn (own_buf);
         break;
      case 'M':
         decode_M_packet (&own_buf[1], &mem_addr, &len, mem_buf);
         if (valgrind_write_memory (mem_addr, mem_buf, len) == 0)
            write_ok (own_buf);
         else
            write_enn (own_buf);
         break;
      case 'X':
         if (decode_X_packet (&own_buf[1], packet_len - 1,
                              &mem_addr, &len, mem_buf) < 0
             || valgrind_write_memory (mem_addr, mem_buf, len) != 0)
            write_enn (own_buf);
         else
            write_ok (own_buf);
         break;
      case 'C':
         convert_ascii_to_int (own_buf + 1, &sig, 1);
         if (target_signal_to_host_p (sig))
            zignal = target_signal_to_host (sig);
         else
            zignal = 0;
         set_desired_inferior (0);
         myresume (0, zignal);
         return; 
      case 'S':
         convert_ascii_to_int (own_buf + 1, &sig, 1);
         if (target_signal_to_host_p (sig))
            zignal = target_signal_to_host (sig);
         else
            zignal = 0;
         set_desired_inferior (0);
         myresume (1, zignal);
         return; 
      case 'c':
         set_desired_inferior (0);
         myresume (0, 0);
         return; 
      case 's':
         set_desired_inferior (0);
         myresume (1, 0);
         return; 
      case 'Z': {
         char *lenptr;
         char *dataptr;
         CORE_ADDR addr = strtoul (&own_buf[3], &lenptr, 16);
         int zlen = strtol (lenptr + 1, &dataptr, 16);
         char type = own_buf[1];
         
         if (type < '0' || type > '4') {
            
            own_buf[0] = '\0';
         } else {
            int res;
            
            res = valgrind_insert_watchpoint (type, addr, zlen);
            if (res == 0)
               write_ok (own_buf);
            else if (res == 1)
               
               own_buf[0] = '\0';
            else
               write_enn (own_buf);
         }
         break;
      }
      case 'z': {
         char *lenptr;
         char *dataptr;
         CORE_ADDR addr = strtoul (&own_buf[3], &lenptr, 16);
         int zlen = strtol (lenptr + 1, &dataptr, 16);
         char type = own_buf[1];
         
         if (type < '0' || type > '4') {
            
            own_buf[0] = '\0';
         } else {
            int res;
            
            res = valgrind_remove_watchpoint (type, addr, zlen);
            if (res == 0)
               write_ok (own_buf);
            else if (res == 1)
               
               own_buf[0] = '\0';
            else
               write_enn (own_buf);
         }
         break;
      }
      case 'k':
         kill_request("Gdb request to kill this process\n");
         break;
      case 'T': {
         unsigned long gdb_id, thread_id;
         
         gdb_id = strtoul (&own_buf[1], NULL, 16);
         thread_id = gdb_id_to_thread_id (gdb_id);
         if (thread_id == 0) {
            write_enn (own_buf);
            break;
         }

         if (valgrind_thread_alive (thread_id))
            write_ok (own_buf);
         else
            write_enn (own_buf);
         break;
      }
      case 'R':
         own_buf[0] = '\0';
         break;
      case 'v':
         
         handle_v_requests (own_buf, &status, &zignal);
         break;
      default:
         own_buf[0] = '\0';
         break;
      }

      if (new_packet_len != -1)
         putpkt_binary (own_buf, new_packet_len);
      else
         putpkt (own_buf);
      
      if (status == 'W')
         VG_(umsg) ("\nChild exited with status %d\n", zignal);
      if (status == 'X')
         VG_(umsg) ("\nChild terminated with signal = 0x%x (%s)\n",
                    target_signal_to_host (zignal),
                    target_signal_to_name (zignal));
      if (status == 'W' || status == 'X') {
         VG_(umsg) ("Process exiting\n");
         VG_(exit) (0);
      }
   }

   if (VG_(clo_verbosity) > 1)
      VG_(umsg) ("Remote side has terminated connection.  "
                 "GDBserver will reopen the connection.\n");
   remote_finish (reset_after_error);
   remote_open (VG_(clo_vgdb_prefix)); 
   myresume (0, 0);
   resume_reply_packet_needed = False;
   return;
}
