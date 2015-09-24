/**
 * @file daemon/opd_kernel.c
 * Dealing with the kernel and kernel module samples
 *
 * @remark Copyright 2002 OProfile authors
 * @remark Read the file COPYING
 *
 * @author John Levon
 * @author Philippe Elie
 * Modified by Aravind Menon for Xen
 * These modifications are:
 * Copyright (C) 2005 Hewlett-Packard Co.
 */

#include "opd_kernel.h"
#include "opd_sfile.h"
#include "opd_trans.h"
#include "opd_printf.h"
#include "opd_stats.h"
#include "oprofiled.h"

#include "op_fileio.h"
#include "op_config.h"
#include "op_libiberty.h"

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

static LIST_HEAD(modules);

static struct kernel_image vmlinux_image;

static struct kernel_image xen_image;

void opd_create_vmlinux(char const * name, char const * arg)
{
	
	list_init(&vmlinux_image.list);

	
	if (no_vmlinux) {
		vmlinux_image.name = "no-vmlinux";
		return;
	}
	
	vmlinux_image.name = xstrdup(name);

	sscanf(arg, "%llx,%llx", &vmlinux_image.start, &vmlinux_image.end);

	verbprintf(vmisc, "kernel_start = %llx, kernel_end = %llx\n",
	           vmlinux_image.start, vmlinux_image.end);

	if (!vmlinux_image.start && !vmlinux_image.end) {
		fprintf(stderr, "error: mis-parsed kernel range: %llx-%llx\n",
		        vmlinux_image.start, vmlinux_image.end);
		exit(EXIT_FAILURE);
	}
}

void opd_create_xen(char const * name, char const * arg)
{
	
	list_init(&xen_image.list);

	
	if (no_xen) {
		xen_image.name = "no-xen";
		return;
	}

	xen_image.name = xstrdup(name);

	sscanf(arg, "%llx,%llx", &xen_image.start, &xen_image.end);

	verbprintf(vmisc, "xen_start = %llx, xen_end = %llx\n",
	           xen_image.start, xen_image.end);

	if (!xen_image.start && !xen_image.end) {
		fprintf(stderr, "error: mis-parsed xen range: %llx-%llx\n",
		        xen_image.start, xen_image.end);
		exit(EXIT_FAILURE);
	}
}


static struct kernel_image *
opd_create_module(char const * name, vma_t start, vma_t end)
{
	struct kernel_image * image = xmalloc(sizeof(struct kernel_image));

	image->name = xstrdup(name);
	image->start = start;
	image->end = end;
	list_add(&image->list, &modules);

	return image;
}


static void opd_clear_modules(void)
{
	struct list_head * pos;
	struct list_head * pos2;
	struct kernel_image * image;

	list_for_each_safe(pos, pos2, &modules) {
		image = list_entry(pos, struct kernel_image, list);
		if (image->name)
			free(image->name);
		free(image);
	}

	list_init(&modules);

	
	sfile_clear_kernel();
}


void opd_reread_module_info(void)
{
	FILE * fp;
	char * line;
	struct kernel_image * image;
	int module_size;
	char ref_count[32+1];
	int ret;
	char module_name[256+1];
	char live_info[32+1];
	char dependencies[4096+1];
	unsigned long long start_address;

	if (no_vmlinux)
		return;

	opd_clear_modules();

	printf("Reading module info.\n");

	fp = op_try_open_file("/proc/modules", "r");

	if (!fp) {
		printf("oprofiled: /proc/modules not readable, "
			"can't process module samples.\n");
		return;
	}

	while (1) {
		line = op_get_line(fp);

		if (!line)
			break;

		if (line[0] == '\0') {
			free(line);
			continue;
		}

		ret = sscanf(line, "%256s %u %32s %4096s %32s %llx",
			     module_name, &module_size, ref_count,
			     dependencies, live_info, &start_address);
		if (ret != 6) {
			printf("bad /proc/modules entry: %s\n", line);
			free(line);
			continue;
		}

		image = opd_create_module(module_name, start_address,
		                          start_address + module_size);

		verbprintf(vmodule, "module %s start %llx end %llx\n",
			   image->name, image->start, image->end);

		free(line);
	}

	op_close_file(fp);
}


struct kernel_image * find_kernel_image(struct transient const * trans)
{
	struct list_head * pos;
	struct kernel_image * image = &vmlinux_image;

	if (no_vmlinux)
		return image;

	if (image->start <= trans->pc && image->end > trans->pc)
		return image;

	list_for_each(pos, &modules) {
		image = list_entry(pos, struct kernel_image, list);
		if (image->start <= trans->pc && image->end > trans->pc)
			return image;
	}

	if (xen_image.start <= trans->pc && xen_image.end > trans->pc)
		return &xen_image;

	return NULL;
}