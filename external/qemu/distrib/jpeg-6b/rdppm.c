/*
 * rdppm.c
 *
 * Copyright (C) 1991-1997, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains routines to read input images in PPM/PGM format.
 * The extended 2-byte-per-sample raw PPM/PGM formats are supported.
 * The PBMPLUS library is NOT required to compile this software
 * (but it is highly useful as a set of PPM image manipulation programs).
 *
 * These routines may need modification for non-Unix environments or
 * specialized applications.  As they stand, they assume input from
 * an ordinary stdio stream.  They further assume that reading begins
 * at the start of the file; start_input may need work if the
 * user interface has already read some data (e.g., to determine that
 * the file is indeed PPM format).
 */

#include "cdjpeg.h"		

#ifdef PPM_SUPPORTED


/* Portions of this code are based on the PBMPLUS library, which is:
**
** Copyright (C) 1988 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/



#ifdef HAVE_UNSIGNED_CHAR
typedef unsigned char U_CHAR;
#define UCH(x)	((int) (x))
#else 
#ifdef CHAR_IS_UNSIGNED
typedef char U_CHAR;
#define UCH(x)	((int) (x))
#else
typedef char U_CHAR;
#define UCH(x)	((int) (x) & 0xFF)
#endif
#endif 


#define	ReadOK(file,buffer,len)	(JFREAD(file,buffer,len) == ((size_t) (len)))





typedef struct {
  struct cjpeg_source_struct pub; 

  U_CHAR *iobuffer;		
  JSAMPROW pixrow;		
  size_t buffer_width;		
  JSAMPLE *rescale;		
} ppm_source_struct;

typedef ppm_source_struct * ppm_source_ptr;


LOCAL(int)
pbm_getc (FILE * infile)
{
  register int ch;

  ch = getc(infile);
  if (ch == '#') {
    do {
      ch = getc(infile);
    } while (ch != '\n' && ch != EOF);
  }
  return ch;
}


LOCAL(unsigned int)
read_pbm_integer (j_compress_ptr cinfo, FILE * infile)
{
  register int ch;
  register unsigned int val;

  
  do {
    ch = pbm_getc(infile);
    if (ch == EOF)
      ERREXIT(cinfo, JERR_INPUT_EOF);
  } while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

  if (ch < '0' || ch > '9')
    ERREXIT(cinfo, JERR_PPM_NONNUMERIC);

  val = ch - '0';
  while ((ch = pbm_getc(infile)) >= '0' && ch <= '9') {
    val *= 10;
    val += ch - '0';
  }
  return val;
}




METHODDEF(JDIMENSION)
get_text_gray_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;
  FILE * infile = source->pub.input_file;
  register JSAMPROW ptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;

  ptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    *ptr++ = rescale[read_pbm_integer(cinfo, infile)];
  }
  return 1;
}


METHODDEF(JDIMENSION)
get_text_rgb_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;
  FILE * infile = source->pub.input_file;
  register JSAMPROW ptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;

  ptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    *ptr++ = rescale[read_pbm_integer(cinfo, infile)];
    *ptr++ = rescale[read_pbm_integer(cinfo, infile)];
    *ptr++ = rescale[read_pbm_integer(cinfo, infile)];
  }
  return 1;
}


METHODDEF(JDIMENSION)
get_scaled_gray_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;
  register JSAMPROW ptr;
  register U_CHAR * bufferptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;

  if (! ReadOK(source->pub.input_file, source->iobuffer, source->buffer_width))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  ptr = source->pub.buffer[0];
  bufferptr = source->iobuffer;
  for (col = cinfo->image_width; col > 0; col--) {
    *ptr++ = rescale[UCH(*bufferptr++)];
  }
  return 1;
}


METHODDEF(JDIMENSION)
get_scaled_rgb_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;
  register JSAMPROW ptr;
  register U_CHAR * bufferptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;

  if (! ReadOK(source->pub.input_file, source->iobuffer, source->buffer_width))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  ptr = source->pub.buffer[0];
  bufferptr = source->iobuffer;
  for (col = cinfo->image_width; col > 0; col--) {
    *ptr++ = rescale[UCH(*bufferptr++)];
    *ptr++ = rescale[UCH(*bufferptr++)];
    *ptr++ = rescale[UCH(*bufferptr++)];
  }
  return 1;
}


METHODDEF(JDIMENSION)
get_raw_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;

  if (! ReadOK(source->pub.input_file, source->iobuffer, source->buffer_width))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  return 1;
}


METHODDEF(JDIMENSION)
get_word_gray_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;
  register JSAMPROW ptr;
  register U_CHAR * bufferptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;

  if (! ReadOK(source->pub.input_file, source->iobuffer, source->buffer_width))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  ptr = source->pub.buffer[0];
  bufferptr = source->iobuffer;
  for (col = cinfo->image_width; col > 0; col--) {
    register int temp;
    temp  = UCH(*bufferptr++);
    temp |= UCH(*bufferptr++) << 8;
    *ptr++ = rescale[temp];
  }
  return 1;
}


METHODDEF(JDIMENSION)
get_word_rgb_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;
  register JSAMPROW ptr;
  register U_CHAR * bufferptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;

  if (! ReadOK(source->pub.input_file, source->iobuffer, source->buffer_width))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  ptr = source->pub.buffer[0];
  bufferptr = source->iobuffer;
  for (col = cinfo->image_width; col > 0; col--) {
    register int temp;
    temp  = UCH(*bufferptr++);
    temp |= UCH(*bufferptr++) << 8;
    *ptr++ = rescale[temp];
    temp  = UCH(*bufferptr++);
    temp |= UCH(*bufferptr++) << 8;
    *ptr++ = rescale[temp];
    temp  = UCH(*bufferptr++);
    temp |= UCH(*bufferptr++) << 8;
    *ptr++ = rescale[temp];
  }
  return 1;
}



METHODDEF(void)
start_input_ppm (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  ppm_source_ptr source = (ppm_source_ptr) sinfo;
  int c;
  unsigned int w, h, maxval;
  boolean need_iobuffer, use_raw_buffer, need_rescale;

  if (getc(source->pub.input_file) != 'P')
    ERREXIT(cinfo, JERR_PPM_NOT);

  c = getc(source->pub.input_file); 

  
  switch (c) {
  case '2':			
  case '3':			
  case '5':			
  case '6':			
    break;
  default:
    ERREXIT(cinfo, JERR_PPM_NOT);
    break;
  }

  
  w = read_pbm_integer(cinfo, source->pub.input_file);
  h = read_pbm_integer(cinfo, source->pub.input_file);
  maxval = read_pbm_integer(cinfo, source->pub.input_file);

  if (w <= 0 || h <= 0 || maxval <= 0) 
    ERREXIT(cinfo, JERR_PPM_NOT);

  cinfo->data_precision = BITS_IN_JSAMPLE; 
  cinfo->image_width = (JDIMENSION) w;
  cinfo->image_height = (JDIMENSION) h;

  
  need_iobuffer = TRUE;		
  use_raw_buffer = FALSE;	
  need_rescale = TRUE;		

  switch (c) {
  case '2':			
    cinfo->input_components = 1;
    cinfo->in_color_space = JCS_GRAYSCALE;
    TRACEMS2(cinfo, 1, JTRC_PGM_TEXT, w, h);
    source->pub.get_pixel_rows = get_text_gray_row;
    need_iobuffer = FALSE;
    break;

  case '3':			
    cinfo->input_components = 3;
    cinfo->in_color_space = JCS_RGB;
    TRACEMS2(cinfo, 1, JTRC_PPM_TEXT, w, h);
    source->pub.get_pixel_rows = get_text_rgb_row;
    need_iobuffer = FALSE;
    break;

  case '5':			
    cinfo->input_components = 1;
    cinfo->in_color_space = JCS_GRAYSCALE;
    TRACEMS2(cinfo, 1, JTRC_PGM, w, h);
    if (maxval > 255) {
      source->pub.get_pixel_rows = get_word_gray_row;
    } else if (maxval == MAXJSAMPLE && SIZEOF(JSAMPLE) == SIZEOF(U_CHAR)) {
      source->pub.get_pixel_rows = get_raw_row;
      use_raw_buffer = TRUE;
      need_rescale = FALSE;
    } else {
      source->pub.get_pixel_rows = get_scaled_gray_row;
    }
    break;

  case '6':			
    cinfo->input_components = 3;
    cinfo->in_color_space = JCS_RGB;
    TRACEMS2(cinfo, 1, JTRC_PPM, w, h);
    if (maxval > 255) {
      source->pub.get_pixel_rows = get_word_rgb_row;
    } else if (maxval == MAXJSAMPLE && SIZEOF(JSAMPLE) == SIZEOF(U_CHAR)) {
      source->pub.get_pixel_rows = get_raw_row;
      use_raw_buffer = TRUE;
      need_rescale = FALSE;
    } else {
      source->pub.get_pixel_rows = get_scaled_rgb_row;
    }
    break;
  }

  
  if (need_iobuffer) {
    source->buffer_width = (size_t) w * cinfo->input_components *
      ((maxval<=255) ? SIZEOF(U_CHAR) : (2*SIZEOF(U_CHAR)));
    source->iobuffer = (U_CHAR *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  source->buffer_width);
  }

  
  if (use_raw_buffer) {
    
    
    
    source->pixrow = (JSAMPROW) source->iobuffer;
    source->pub.buffer = & source->pixrow;
    source->pub.buffer_height = 1;
  } else {
    
    source->pub.buffer = (*cinfo->mem->alloc_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE,
       (JDIMENSION) w * cinfo->input_components, (JDIMENSION) 1);
    source->pub.buffer_height = 1;
  }

  
  if (need_rescale) {
    INT32 val, half_maxval;

    
    source->rescale = (JSAMPLE *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  (size_t) (((long) maxval + 1L) * SIZEOF(JSAMPLE)));
    half_maxval = maxval / 2;
    for (val = 0; val <= (INT32) maxval; val++) {
      
      source->rescale[val] = (JSAMPLE) ((val*MAXJSAMPLE + half_maxval)/maxval);
    }
  }
}



METHODDEF(void)
finish_input_ppm (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  
}



GLOBAL(cjpeg_source_ptr)
jinit_read_ppm (j_compress_ptr cinfo)
{
  ppm_source_ptr source;

  
  source = (ppm_source_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(ppm_source_struct));
  
  source->pub.start_input = start_input_ppm;
  source->pub.finish_input = finish_input_ppm;

  return (cjpeg_source_ptr) source;
}

#endif 
