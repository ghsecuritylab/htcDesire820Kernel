/*
 * ismounted.c --- Check to see if the filesystem was mounted
 *
 * Copyright (C) 1995,1996,1997,1998,1999,2000 Theodore Ts'o.
 *
 * %Begin-Header%
 * This file may be redistributed under the terms of the GNU Library
 * General Public License, version 2.
 * %End-Header%
 */

#include <stdio.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_ERRNO_H
#include <errno.h>
#endif
#include <fcntl.h>
#ifdef HAVE_LINUX_FD_H
#include <linux/fd.h>
#endif
#ifdef HAVE_MNTENT_H
#include <mntent.h>
#endif
#ifdef HAVE_GETMNTINFO
#include <paths.h>
#include <sys/param.h>
#include <sys/mount.h>
#endif 
#include <string.h>
#include <sys/stat.h>

#include "ext2_fs.h"
#include "ext2fs.h"

#ifdef HAVE_MNTENT_H
static errcode_t check_mntent_file(const char *mtab_file, const char *file,
				   int *mount_flags, char *mtpt, int mtlen)
{
	struct mntent 	*mnt;
	struct stat	st_buf;
	errcode_t	retval = 0;
	dev_t		file_dev=0, file_rdev=0;
	ino_t		file_ino=0;
	FILE 		*f;
	int		fd;

	*mount_flags = 0;
	if ((f = setmntent (mtab_file, "r")) == NULL)
		return (errno == ENOENT ? EXT2_NO_MTAB_FILE : errno);
	if (stat(file, &st_buf) == 0) {
		if (S_ISBLK(st_buf.st_mode)) {
#ifndef __GNU__ 
			file_rdev = st_buf.st_rdev;
#endif	
		} else {
			file_dev = st_buf.st_dev;
			file_ino = st_buf.st_ino;
		}
	}
	while ((mnt = getmntent (f)) != NULL) {
		if (mnt->mnt_fsname[0] != '/')
			continue;
		if (strcmp(file, mnt->mnt_fsname) == 0)
			break;
		if (stat(mnt->mnt_fsname, &st_buf) == 0) {
			if (S_ISBLK(st_buf.st_mode)) {
#ifndef __GNU__
				if (file_rdev && (file_rdev == st_buf.st_rdev))
					break;
#endif	
			} else {
				if (file_dev && ((file_dev == st_buf.st_dev) &&
						 (file_ino == st_buf.st_ino)))
					break;
			}
		}
	}

	if (mnt == 0) {
#ifndef __GNU__ 
		if (file_rdev && stat("/", &st_buf) == 0) {
			if (st_buf.st_dev == file_rdev) {
				*mount_flags = EXT2_MF_MOUNTED;
				if (mtpt)
					strncpy(mtpt, "/", mtlen);
				goto is_root;
			}
		}
#endif	
		goto errout;
	}
#ifndef __GNU__ 
	
	if (stat(mnt->mnt_dir, &st_buf) < 0) {
		retval = errno;
		if (retval == ENOENT) {
#ifdef DEBUG
			printf("Bogus entry in %s!  (%s does not exist)\n",
			       mtab_file, mnt->mnt_dir);
#endif 
			retval = 0;
		}
		goto errout;
	}
	if (file_rdev && (st_buf.st_dev != file_rdev)) {
#ifdef DEBUG
		printf("Bogus entry in %s!  (%s not mounted on %s)\n",
		       mtab_file, file, mnt->mnt_dir);
#endif 
		goto errout;
	}
#endif 
	*mount_flags = EXT2_MF_MOUNTED;

#ifdef MNTOPT_RO
	
	if (hasmntopt(mnt, MNTOPT_RO))
		*mount_flags |= EXT2_MF_READONLY;
#endif

	if (mtpt)
		strncpy(mtpt, mnt->mnt_dir, mtlen);
	if (!strcmp(mnt->mnt_dir, "/")) {
is_root:
#define TEST_FILE "/.ismount-test-file"
		*mount_flags |= EXT2_MF_ISROOT;
		fd = open(TEST_FILE, O_RDWR|O_CREAT, 0600);
		if (fd < 0) {
			if (errno == EROFS)
				*mount_flags |= EXT2_MF_READONLY;
		} else
			close(fd);
		(void) unlink(TEST_FILE);
	}
	retval = 0;
errout:
	endmntent (f);
	return retval;
}

static errcode_t check_mntent(const char *file, int *mount_flags,
			      char *mtpt, int mtlen)
{
	errcode_t	retval;

#ifdef DEBUG
	retval = check_mntent_file("/tmp/mtab", file, mount_flags,
				   mtpt, mtlen);
	if (retval == 0)
		return 0;
#endif 
#ifdef __linux__
	retval = check_mntent_file("/proc/mounts", file, mount_flags,
				   mtpt, mtlen);
	if (retval == 0 && (*mount_flags != 0))
		return 0;
#endif 
#if defined(MOUNTED) || defined(_PATH_MOUNTED)
#ifndef MOUNTED
#define MOUNTED _PATH_MOUNTED
#endif 
	retval = check_mntent_file(MOUNTED, file, mount_flags, mtpt, mtlen);
	return retval;
#else
	*mount_flags = 0;
	return 0;
#endif 
}

#else
#if defined(HAVE_GETMNTINFO)

static errcode_t check_getmntinfo(const char *file, int *mount_flags,
				  char *mtpt, int mtlen)
{
	struct statfs *mp;
        int    len, n;
        const  char   *s1;
	char	*s2;

        n = getmntinfo(&mp, MNT_NOWAIT);
        if (n == 0)
		return errno;

        len = sizeof(_PATH_DEV) - 1;
        s1 = file;
        if (strncmp(_PATH_DEV, s1, len) == 0)
                s1 += len;

	*mount_flags = 0;
        while (--n >= 0) {
                s2 = mp->f_mntfromname;
                if (strncmp(_PATH_DEV, s2, len) == 0) {
                        s2 += len - 1;
                        *s2 = 'r';
                }
                if (strcmp(s1, s2) == 0 || strcmp(s1, &s2[1]) == 0) {
			*mount_flags = EXT2_MF_MOUNTED;
			break;
		}
                ++mp;
	}
	if (mtpt)
		strncpy(mtpt, mp->f_mntonname, mtlen);
	return 0;
}
#endif 
#endif 

static int is_swap_device(const char *file)
{
	FILE		*f;
	char		buf[1024], *cp;
	dev_t		file_dev;
	struct stat	st_buf;
	int		ret = 0;

	file_dev = 0;
#ifndef __GNU__ 
	if ((stat(file, &st_buf) == 0) &&
	    S_ISBLK(st_buf.st_mode))
		file_dev = st_buf.st_rdev;
#endif	

	if (!(f = fopen("/proc/swaps", "r")))
		return 0;
	
	if (!fgets(buf, sizeof(buf), f))
		goto leave;
	if (*buf && strncmp(buf, "Filename\t", 9))
		goto valid_first_line;

	while (fgets(buf, sizeof(buf), f)) {
valid_first_line:
		if ((cp = strchr(buf, ' ')) != NULL)
			*cp = 0;
		if ((cp = strchr(buf, '\t')) != NULL)
			*cp = 0;
		if (strcmp(buf, file) == 0) {
			ret++;
			break;
		}
#ifndef __GNU__
		if (file_dev && (stat(buf, &st_buf) == 0) &&
		    S_ISBLK(st_buf.st_mode) &&
		    file_dev == st_buf.st_rdev) {
			ret++;
			break;
		}
#endif 	
	}

leave:
	fclose(f);
	return ret;
}


#ifdef __TURBOC__
 #pragma argsused
#endif
errcode_t ext2fs_check_mount_point(const char *device, int *mount_flags,
				  char *mtpt, int mtlen)
{
	struct stat	st_buf;
	errcode_t	retval = 0;
	int		fd;

	if (is_swap_device(device)) {
		*mount_flags = EXT2_MF_MOUNTED | EXT2_MF_SWAP;
		strncpy(mtpt, "<swap>", mtlen);
	} else {
#ifdef HAVE_MNTENT_H
		retval = check_mntent(device, mount_flags, mtpt, mtlen);
#else
#ifdef HAVE_GETMNTINFO
		retval = check_getmntinfo(device, mount_flags, mtpt, mtlen);
#else
#ifdef __GNUC__
 #warning "Can't use getmntent or getmntinfo to check for mounted filesystems!"
#endif
		*mount_flags = 0;
#endif 
#endif 
	}
	if (retval)
		return retval;

#ifdef __linux__ 
	if ((stat(device, &st_buf) != 0) ||
	    !S_ISBLK(st_buf.st_mode))
		return 0;
	fd = open(device, O_RDONLY | O_EXCL);
	if (fd < 0) {
		if (errno == EBUSY)
			*mount_flags |= EXT2_MF_BUSY;
	} else
		close(fd);
#endif

	return 0;
}

errcode_t ext2fs_check_if_mounted(const char *file, int *mount_flags)
{
	return ext2fs_check_mount_point(file, mount_flags, NULL, 0);
}

#ifdef DEBUG
int main(int argc, char **argv)
{
	int	retval, mount_flags;
	char	mntpt[80];

	if (argc < 2) {
		fprintf(stderr, "Usage: %s device\n", argv[0]);
		exit(1);
	}

	add_error_table(&et_ext2_error_table);
	mntpt[0] = 0;
	retval = ext2fs_check_mount_point(argv[1], &mount_flags,
					  mntpt, sizeof(mntpt));
	if (retval) {
		com_err(argv[0], retval,
			"while calling ext2fs_check_if_mounted");
		exit(1);
	}
	printf("Device %s reports flags %02x\n", argv[1], mount_flags);
	if (mount_flags & EXT2_MF_BUSY)
		printf("\t%s is apparently in use.\n", argv[1]);
	if (mount_flags & EXT2_MF_MOUNTED)
		printf("\t%s is mounted.\n", argv[1]);
	if (mount_flags & EXT2_MF_SWAP)
		printf("\t%s is a swap device.\n", argv[1]);
	if (mount_flags & EXT2_MF_READONLY)
		printf("\t%s is read-only.\n", argv[1]);
	if (mount_flags & EXT2_MF_ISROOT)
		printf("\t%s is the root filesystem.\n", argv[1]);
	if (mntpt[0])
		printf("\t%s is mounted on %s.\n", argv[1], mntpt);
	exit(0);
}
#endif 
