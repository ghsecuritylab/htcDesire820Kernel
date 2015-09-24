/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 1999,2000,2001,2003   Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _PC_SLICE_H
#define _PC_SLICE_H


#define PC_MBR_SECTOR  0

#define PC_MBR_SIG_OFFSET  510
#define PC_MBR_SIGNATURE   0xaa55

#define PC_SLICE_OFFSET 446
#define PC_SLICE_MAX    4



#define PC_MBR_CHECK_SIG(mbr_ptr) \
  ( *( (unsigned short *) (((int) mbr_ptr) + PC_MBR_SIG_OFFSET) ) \
   == PC_MBR_SIGNATURE )

#define PC_MBR_SIG(mbr_ptr) \
  ( *( (unsigned short *) (((int) mbr_ptr) + PC_MBR_SIG_OFFSET) ) )

#define PC_SLICE_FLAG(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET \
			  + (part << 4)) ) )

#define PC_SLICE_HEAD(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 1 \
			  + (part << 4)) ) )

#define PC_SLICE_SEC(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 2 \
			  + (part << 4)) ) )

#define PC_SLICE_CYL(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 3 \
			  + (part << 4)) ) )

#define PC_SLICE_TYPE(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 4 \
			  + (part << 4)) ) )

#define PC_SLICE_EHEAD(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 5 \
			  + (part << 4)) ) )

#define PC_SLICE_ESEC(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 6 \
			  + (part << 4)) ) )

#define PC_SLICE_ECYL(mbr_ptr, part) \
  ( *( (unsigned char *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 7 \
			  + (part << 4)) ) )

#define PC_SLICE_START(mbr_ptr, part) \
  ( *( (unsigned long *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 8 \
			  + (part << 4)) ) )

#define PC_SLICE_LENGTH(mbr_ptr, part) \
  ( *( (unsigned long *) (((int) mbr_ptr) + PC_SLICE_OFFSET + 12 \
			  + (part << 4)) ) )



#define PC_SLICE_FLAG_NONE      0
#define PC_SLICE_FLAG_BOOTABLE  0x80


#define PC_SLICE_TYPE_HIDDEN_FLAG	0x10

#define PC_SLICE_TYPE_NONE         	0
#define PC_SLICE_TYPE_FAT12        	1
#define PC_SLICE_TYPE_FAT16_LT32M  	4
#define PC_SLICE_TYPE_EXTENDED     	5
#define PC_SLICE_TYPE_FAT16_GT32M  	6
#define PC_SLICE_TYPE_FAT32		0xb
#define PC_SLICE_TYPE_FAT32_LBA		0xc
#define PC_SLICE_TYPE_FAT16_LBA		0xe
#define PC_SLICE_TYPE_WIN95_EXTENDED	0xf
#define PC_SLICE_TYPE_EZD        	0x55
#define PC_SLICE_TYPE_MINIX		0x80
#define PC_SLICE_TYPE_LINUX_MINIX	0x81
#define PC_SLICE_TYPE_EXT2FS       	0x83
#define PC_SLICE_TYPE_LINUX_EXTENDED	0x85
#define PC_SLICE_TYPE_VSTAFS		0x9e
#define PC_SLICE_TYPE_DELL_UTIL		0xde
#define PC_SLICE_TYPE_LINUX_RAID	0xfd


#define IS_PC_SLICE_TYPE_FAT(type)	\
  ({ int _type = (type) & ~PC_SLICE_TYPE_HIDDEN_FLAG; \
     _type == PC_SLICE_TYPE_FAT12 \
     || _type == PC_SLICE_TYPE_FAT16_LT32M \
     || _type == PC_SLICE_TYPE_FAT16_GT32M \
     || _type == PC_SLICE_TYPE_FAT16_LBA \
     || _type == PC_SLICE_TYPE_FAT32 \
     || _type == PC_SLICE_TYPE_FAT32_LBA \
     || _type == PC_SLICE_TYPE_DELL_UTIL; })

#define IS_PC_SLICE_TYPE_EXTENDED(type)	\
  (((type) == PC_SLICE_TYPE_EXTENDED)	\
   || ((type) == PC_SLICE_TYPE_WIN95_EXTENDED)	\
   || ((type) == PC_SLICE_TYPE_LINUX_EXTENDED))

#define IS_PC_SLICE_TYPE_MINIX(type) \
  (((type) == PC_SLICE_TYPE_MINIX)	\
   || ((type) == PC_SLICE_TYPE_LINUX_MINIX))

#define PC_SLICE_TYPE_FREEBSD		0xa5
#define PC_SLICE_TYPE_OPENBSD		0xa6
#define PC_SLICE_TYPE_NETBSD		0xa9

#define IS_PC_SLICE_TYPE_BSD_WITH_FS(type,fs)	\
  ((type) == (PC_SLICE_TYPE_FREEBSD | ((fs) << 8)) \
   || (type) == (PC_SLICE_TYPE_OPENBSD | ((fs) << 8)) \
   || (type) == (PC_SLICE_TYPE_NETBSD | (fs) << 8))

#define IS_PC_SLICE_TYPE_BSD(type)	IS_PC_SLICE_TYPE_BSD_WITH_FS(type,0)


#define BSD_LABEL_SECTOR 1
#define BSD_LABEL_MAGIC  0x82564557

#define BSD_LABEL_MAG_OFFSET 0
#define BSD_LABEL_MAG2_OFFSET 132
#define BSD_LABEL_NPARTS_OFFSET 138
#define BSD_LABEL_NPARTS_MAX 8

#define BSD_PART_OFFSET 148



#define BSD_LABEL_CHECK_MAG(l_ptr) \
  ( *( (unsigned long *) (((int) l_ptr) + BSD_LABEL_MAG_OFFSET) ) \
   == ( (unsigned long) BSD_LABEL_MAGIC ) )

#define BSD_LABEL_MAG(l_ptr) \
  ( *( (unsigned long *) (((int) l_ptr) + BSD_LABEL_MAG_OFFSET) ) )

#define BSD_LABEL_DTYPE(l_ptr) \
  ( *( (unsigned short *) (((int) l_ptr) + BSD_LABEL_MAG_OFFSET + 4) ) )

#define BSD_LABEL_NPARTS(l_ptr) \
  ( *( (unsigned short *) (((int) l_ptr) + BSD_LABEL_NPARTS_OFFSET) ) )

#define BSD_PART_LENGTH(l_ptr, part) \
  ( *( (unsigned long *) (((int) l_ptr) + BSD_PART_OFFSET \
			  + (part << 4)) ) )

#define BSD_PART_START(l_ptr, part) \
  ( *( (unsigned long *) (((int) l_ptr) + BSD_PART_OFFSET + 4 \
			  + (part << 4)) ) )

#define BSD_PART_FRAG_SIZE(l_ptr, part) \
  ( *( (unsigned long *) (((int) l_ptr) + BSD_PART_OFFSET + 8 \
			  + (part << 4)) ) )

#define BSD_PART_TYPE(l_ptr, part) \
  ( *( (unsigned char *) (((int) l_ptr) + BSD_PART_OFFSET + 12 \
			  + (part << 4)) ) )

#define BSD_PART_FRAGS_PER_BLOCK(l_ptr, part) \
  ( *( (unsigned char *) (((int) l_ptr) + BSD_PART_OFFSET + 13 \
			  + (part << 4)) ) )

#define BSD_PART_EXTRA(l_ptr, part) \
  ( *( (unsigned short *) (((int) l_ptr) + BSD_PART_OFFSET + 14 \
			  + (part << 4)) ) )


#define DTYPE_SMD               1	
#define DTYPE_MSCP              2	
#define DTYPE_DEC               3	
#define DTYPE_SCSI              4	
#define DTYPE_ESDI              5	
#define DTYPE_ST506             6	
#define DTYPE_HPIB              7	
#define DTYPE_HPFL              8	
#define DTYPE_FLOPPY            10	


#define	FS_UNUSED	0	
#define	FS_SWAP		1	
#define	FS_V6		2	
#define	FS_V7		3	
#define	FS_SYSV		4	
#define	FS_V71K		5	
#define	FS_V8		6	
#define	FS_BSDFFS	7	
#define	FS_MSDOS	8	
#define	FS_BSDLFS	9	
#define	FS_OTHER	10	
#define	FS_HPFS		11	
#define	FS_ISO9660	12	
#define	FS_BOOT		13	
#define	FS_ADOS		14	
#define	FS_HFS		15	
#define	FS_FILECORE	16	
#define	FS_EXT2FS	17	


#endif 