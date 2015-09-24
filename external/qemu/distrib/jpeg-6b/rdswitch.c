/*
 * rdswitch.c
 *
 * Copyright (C) 1991-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains routines to process some of cjpeg's more complicated
 * command-line switches.  Switches processed here are:
 *	-qtables file		Read quantization tables from text file
 *	-scans file		Read scan script from text file
 *	-qslots N[,N,...]	Set component quantization table selectors
 *	-sample HxV[,HxV,...]	Set component sampling factors
 */

#include "cdjpeg.h"		
#include <ctype.h>		


LOCAL(int)
text_getc (FILE * file)
{
  register int ch;
  
  ch = getc(file);
  if (ch == '#') {
    do {
      ch = getc(file);
    } while (ch != '\n' && ch != EOF);
  }
  return ch;
}


LOCAL(boolean)
read_text_integer (FILE * file, long * result, int * termchar)
{
  register int ch;
  register long val;
  
  
  do {
    ch = text_getc(file);
    if (ch == EOF) {
      *termchar = ch;
      return FALSE;
    }
  } while (isspace(ch));
  
  if (! isdigit(ch)) {
    *termchar = ch;
    return FALSE;
  }

  val = ch - '0';
  while ((ch = text_getc(file)) != EOF) {
    if (! isdigit(ch))
      break;
    val *= 10;
    val += ch - '0';
  }
  *result = val;
  *termchar = ch;
  return TRUE;
}


GLOBAL(boolean)
read_quant_tables (j_compress_ptr cinfo, char * filename,
		   int scale_factor, boolean force_baseline)
{
  FILE * fp;
  int tblno, i, termchar;
  long val;
  unsigned int table[DCTSIZE2];

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Can't open table file %s\n", filename);
    return FALSE;
  }
  tblno = 0;

  while (read_text_integer(fp, &val, &termchar)) { 
    if (tblno >= NUM_QUANT_TBLS) {
      fprintf(stderr, "Too many tables in file %s\n", filename);
      fclose(fp);
      return FALSE;
    }
    table[0] = (unsigned int) val;
    for (i = 1; i < DCTSIZE2; i++) {
      if (! read_text_integer(fp, &val, &termchar)) {
	fprintf(stderr, "Invalid table data in file %s\n", filename);
	fclose(fp);
	return FALSE;
      }
      table[i] = (unsigned int) val;
    }
    jpeg_add_quant_table(cinfo, tblno, table, scale_factor, force_baseline);
    tblno++;
  }

  if (termchar != EOF) {
    fprintf(stderr, "Non-numeric data in file %s\n", filename);
    fclose(fp);
    return FALSE;
  }

  fclose(fp);
  return TRUE;
}


#ifdef C_MULTISCAN_FILES_SUPPORTED

LOCAL(boolean)
read_scan_integer (FILE * file, long * result, int * termchar)
{
  register int ch;

  if (! read_text_integer(file, result, termchar))
    return FALSE;
  ch = *termchar;
  while (ch != EOF && isspace(ch))
    ch = text_getc(file);
  if (isdigit(ch)) {		
    if (ungetc(ch, file) == EOF)
      return FALSE;
    ch = ' ';
  } else {
    if (ch != EOF && ch != ';' && ch != ':')
      ch = ' ';
  }
  *termchar = ch;
  return TRUE;
}


GLOBAL(boolean)
read_scan_script (j_compress_ptr cinfo, char * filename)
{
  FILE * fp;
  int scanno, ncomps, termchar;
  long val;
  jpeg_scan_info * scanptr;
#define MAX_SCANS  100		
  jpeg_scan_info scans[MAX_SCANS];

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Can't open scan definition file %s\n", filename);
    return FALSE;
  }
  scanptr = scans;
  scanno = 0;

  while (read_scan_integer(fp, &val, &termchar)) {
    if (scanno >= MAX_SCANS) {
      fprintf(stderr, "Too many scans defined in file %s\n", filename);
      fclose(fp);
      return FALSE;
    }
    scanptr->component_index[0] = (int) val;
    ncomps = 1;
    while (termchar == ' ') {
      if (ncomps >= MAX_COMPS_IN_SCAN) {
	fprintf(stderr, "Too many components in one scan in file %s\n",
		filename);
	fclose(fp);
	return FALSE;
      }
      if (! read_scan_integer(fp, &val, &termchar))
	goto bogus;
      scanptr->component_index[ncomps] = (int) val;
      ncomps++;
    }
    scanptr->comps_in_scan = ncomps;
    if (termchar == ':') {
      if (! read_scan_integer(fp, &val, &termchar) || termchar != ' ')
	goto bogus;
      scanptr->Ss = (int) val;
      if (! read_scan_integer(fp, &val, &termchar) || termchar != ' ')
	goto bogus;
      scanptr->Se = (int) val;
      if (! read_scan_integer(fp, &val, &termchar) || termchar != ' ')
	goto bogus;
      scanptr->Ah = (int) val;
      if (! read_scan_integer(fp, &val, &termchar))
	goto bogus;
      scanptr->Al = (int) val;
    } else {
      
      scanptr->Ss = 0;
      scanptr->Se = DCTSIZE2-1;
      scanptr->Ah = 0;
      scanptr->Al = 0;
    }
    if (termchar != ';' && termchar != EOF) {
bogus:
      fprintf(stderr, "Invalid scan entry format in file %s\n", filename);
      fclose(fp);
      return FALSE;
    }
    scanptr++, scanno++;
  }

  if (termchar != EOF) {
    fprintf(stderr, "Non-numeric data in file %s\n", filename);
    fclose(fp);
    return FALSE;
  }

  if (scanno > 0) {
    scanptr = (jpeg_scan_info *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  scanno * SIZEOF(jpeg_scan_info));
    MEMCOPY(scanptr, scans, scanno * SIZEOF(jpeg_scan_info));
    cinfo->scan_info = scanptr;
    cinfo->num_scans = scanno;
  }

  fclose(fp);
  return TRUE;
}

#endif 


GLOBAL(boolean)
set_quant_slots (j_compress_ptr cinfo, char *arg)
{
  int val = 0;			
  int ci;
  char ch;

  for (ci = 0; ci < MAX_COMPONENTS; ci++) {
    if (*arg) {
      ch = ',';			
      if (sscanf(arg, "%d%c", &val, &ch) < 1)
	return FALSE;
      if (ch != ',')		
	return FALSE;
      if (val < 0 || val >= NUM_QUANT_TBLS) {
	fprintf(stderr, "JPEG quantization tables are numbered 0..%d\n",
		NUM_QUANT_TBLS-1);
	return FALSE;
      }
      cinfo->comp_info[ci].quant_tbl_no = val;
      while (*arg && *arg++ != ',') 
	;
    } else {
      
      cinfo->comp_info[ci].quant_tbl_no = val;
    }
  }
  return TRUE;
}


GLOBAL(boolean)
set_sample_factors (j_compress_ptr cinfo, char *arg)
{
  int ci, val1, val2;
  char ch1, ch2;

  for (ci = 0; ci < MAX_COMPONENTS; ci++) {
    if (*arg) {
      ch2 = ',';		
      if (sscanf(arg, "%d%c%d%c", &val1, &ch1, &val2, &ch2) < 3)
	return FALSE;
      if ((ch1 != 'x' && ch1 != 'X') || ch2 != ',') 
	return FALSE;
      if (val1 <= 0 || val1 > 4 || val2 <= 0 || val2 > 4) {
	fprintf(stderr, "JPEG sampling factors must be 1..4\n");
	return FALSE;
      }
      cinfo->comp_info[ci].h_samp_factor = val1;
      cinfo->comp_info[ci].v_samp_factor = val2;
      while (*arg && *arg++ != ',') 
	;
    } else {
      
      cinfo->comp_info[ci].h_samp_factor = 1;
      cinfo->comp_info[ci].v_samp_factor = 1;
    }
  }
  return TRUE;
}
