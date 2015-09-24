/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1995, 96, 99, 2001 Ralf Baechle
 */
#ifndef _ASM_IOCTL_H
#define _ASM_IOCTL_H


#define _IOC_NRBITS	8
#define _IOC_TYPEBITS	8
#define _IOC_SIZEBITS	13
#define _IOC_DIRBITS	3

#define _IOC_NRMASK	((1 << _IOC_NRBITS)-1)
#define _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
#define _IOC_DIRMASK	((1 << _IOC_DIRBITS)-1)

#define _IOC_NRSHIFT	0
#define _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)

#define _IOC_NONE	1U
#define _IOC_READ	2U
#define _IOC_WRITE	4U

#define _IOC_VOID	0x20000000
#define _IOC_OUT	0x40000000
#define _IOC_IN		0x80000000
#define _IOC_INOUT	(IOC_IN|IOC_OUT)

#define _IOC(dir, type, nr, size) \
	(((dir)  << _IOC_DIRSHIFT) | \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr)   << _IOC_NRSHIFT) | \
	 ((size) << _IOC_SIZESHIFT))

extern unsigned int __invalid_size_argument_for_IOC;
#define _IOC_TYPECHECK(t) \
	((sizeof(t) == sizeof(t[1]) && \
	  sizeof(t) < (1 << _IOC_SIZEBITS)) ? \
	  sizeof(t) : __invalid_size_argument_for_IOC)

#define _IO(type, nr)		_IOC(_IOC_NONE, (type), (nr), 0)
#define _IOR(type, nr, size)	_IOC(_IOC_READ, (type), (nr), (_IOC_TYPECHECK(size)))
#define _IOW(type, nr, size)	_IOC(_IOC_WRITE, (type), (nr), (_IOC_TYPECHECK(size)))
#define _IOWR(type, nr, size)	_IOC(_IOC_READ|_IOC_WRITE, (type), (nr), (_IOC_TYPECHECK(size)))
#define _IOR_BAD(type, nr, size)	_IOC(_IOC_READ, (type), (nr), sizeof(size))
#define _IOW_BAD(type, nr, size)	_IOC(_IOC_WRITE, (type), (nr), sizeof(size))
#define _IOWR_BAD(type, nr, size)	_IOC(_IOC_READ|_IOC_WRITE, (type), (nr), sizeof(size))


#define _IOC_DIR(nr)		(((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
#define _IOC_TYPE(nr)		(((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NR(nr)		(((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_SIZE(nr)		(((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)


#define IOC_IN		(_IOC_WRITE << _IOC_DIRSHIFT)
#define IOC_OUT		(_IOC_READ << _IOC_DIRSHIFT)
#define IOC_INOUT	((_IOC_WRITE|_IOC_READ) << _IOC_DIRSHIFT)
#define IOCSIZE_MASK	(_IOC_SIZEMASK << _IOC_SIZESHIFT)
#define IOCSIZE_SHIFT	(_IOC_SIZESHIFT)

#endif 