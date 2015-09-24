/*
 * Windows compat: POSIX compatibility wrapper
 * Copyright (C) 2009-2010 Pete Batard <pbatard@gmail.com>
 * With contributions from Michael Plante, Orin Eman et al.
 * Parts of poll implementation from libusb-win32, by Stephan Meyer et al.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */
#pragma once

#if defined(_MSC_VER)
#pragma warning(disable:4127) 
#endif

#if !defined(STATUS_REPARSE)	
#define STATUS_REPARSE ((LONG)0x00000104L)
#endif
#define STATUS_COMPLETED_SYNCHRONOUSLY	STATUS_REPARSE
#define HasOverlappedIoCompletedSync(lpOverlapped)	(((DWORD)(lpOverlapped)->Internal) == STATUS_COMPLETED_SYNCHRONOUSLY)

#define DUMMY_HANDLE ((HANDLE)(LONG_PTR)-2)

enum windows_version {
	WINDOWS_UNSUPPORTED,
	WINDOWS_XP,
	WINDOWS_2003,	
	WINDOWS_VISTA_AND_LATER,
};
extern enum windows_version windows_version;

#define MAX_FDS     256

#define POLLIN      0x0001    
#define POLLPRI     0x0002    
#define POLLOUT     0x0004    
#define POLLERR     0x0008    
#define POLLHUP     0x0010    
#define POLLNVAL    0x0020    

struct pollfd {
    int fd;           
    short events;     
    short revents;    
};

enum rw_type {
	RW_NONE,
	RW_READ,
	RW_WRITE,
};

struct winfd {
	int fd;							
	HANDLE handle;					
	OVERLAPPED* overlapped;			
	enum rw_type rw;				
};
extern const struct winfd INVALID_WINFD;

int usbi_pipe(int pipefd[2]);
int usbi_poll(struct pollfd *fds, unsigned int nfds, int timeout);
ssize_t usbi_write(int fd, const void *buf, size_t count);
ssize_t usbi_read(int fd, void *buf, size_t count);
int usbi_close(int fd);

void init_polling(void);
void exit_polling(void);
struct winfd usbi_create_fd(HANDLE handle, int access_mode);
void usbi_free_fd(int fd);
struct winfd fd_to_winfd(int fd);
struct winfd handle_to_winfd(HANDLE handle);
struct winfd overlapped_to_winfd(OVERLAPPED* overlapped);

#if defined(DDKBUILD)
#include <winsock.h>	
#endif

#if !defined(timersub)
#define timersub(a, b, result)                          \
do {                                                    \
	(result)->tv_sec = (a)->tv_sec - (b)->tv_sec;       \
	(result)->tv_usec = (a)->tv_usec - (b)->tv_usec;    \
	if ((result)->tv_usec < 0) {                        \
		--(result)->tv_sec;                             \
		(result)->tv_usec += 1000000;                   \
	}                                                   \
} while (0)
#endif
