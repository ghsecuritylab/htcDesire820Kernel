/*
 * rdbmp.c
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains routines to read input images in Microsoft "BMP"
 * format (MS Windows 3.x, OS/2 1.x, and OS/2 2.x flavors).
 * Currently, only 8-bit and 24-bit images are supported, not 1-bit or
 * 4-bit (feeding such low-depth images into JPEG would be silly anyway).
 * Also, we don't support RLE-compressed files.
 *
 * These routines may need modification for non-Unix environments or
 * specialized applications.  As they stand, they assume input from
 * an ordinary stdio stream.  They further assume that reading begins
 * at the start of the file; start_input may need work if the
 * user interface has already read some data (e.g., to determine that
 * the file is indeed BMP format).
 *
 * This code contributed by James Arthur Boucher.
 */

#include "cdjpeg.h"		

#ifdef BMP_SUPPORTED



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



typedef struct _bmp_source_struct * bmp_source_ptr;

typedef struct _bmp_source_struct {
  struct cjpeg_source_struct pub; 

  j_compress_ptr cinfo;		

  JSAMPARRAY colormap;		

  jvirt_sarray_ptr whole_image;	
  JDIMENSION source_row;	
  JDIMENSION row_width;		

  int bits_per_pixel;		
} bmp_source_struct;


LOCAL(int)
read_byte (bmp_source_ptr sinfo)
{
  register FILE *infile = sinfo->pub.input_file;
  register int c;

  if ((c = getc(infile)) == EOF)
    ERREXIT(sinfo->cinfo, JERR_INPUT_EOF);
  return c;
}


LOCAL(void)
read_colormap (bmp_source_ptr sinfo, int cmaplen, int mapentrysize)
{
  int i;

  switch (mapentrysize) {
  case 3:
    
    for (i = 0; i < cmaplen; i++) {
      sinfo->colormap[2][i] = (JSAMPLE) read_byte(sinfo);
      sinfo->colormap[1][i] = (JSAMPLE) read_byte(sinfo);
      sinfo->colormap[0][i] = (JSAMPLE) read_byte(sinfo);
    }
    break;
  case 4:
    
    for (i = 0; i < cmaplen; i++) {
      sinfo->colormap[2][i] = (JSAMPLE) read_byte(sinfo);
      sinfo->colormap[1][i] = (JSAMPLE) read_byte(sinfo);
      sinfo->colormap[0][i] = (JSAMPLE) read_byte(sinfo);
      (void) read_byte(sinfo);
    }
    break;
  default:
    ERREXIT(sinfo->cinfo, JERR_BMP_BADCMAP);
    break;
  }
}



METHODDEF(JDIMENSION)
get_8bit_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  bmp_source_ptr source = (bmp_source_ptr) sinfo;
  register JSAMPARRAY colormap = source->colormap;
  JSAMPARRAY image_ptr;
  register int t;
  register JSAMPROW inptr, outptr;
  register JDIMENSION col;

  
  source->source_row--;
  image_ptr = (*cinfo->mem->access_virt_sarray)
    ((j_common_ptr) cinfo, source->whole_image,
     source->source_row, (JDIMENSION) 1, FALSE);

  
  inptr = image_ptr[0];
  outptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    t = GETJSAMPLE(*inptr++);
    *outptr++ = colormap[0][t];	
    *outptr++ = colormap[1][t];
    *outptr++ = colormap[2][t];
  }

  return 1;
}


METHODDEF(JDIMENSION)
get_24bit_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  bmp_source_ptr source = (bmp_source_ptr) sinfo;
  JSAMPARRAY image_ptr;
  register JSAMPROW inptr, outptr;
  register JDIMENSION col;

  
  source->source_row--;
  image_ptr = (*cinfo->mem->access_virt_sarray)
    ((j_common_ptr) cinfo, source->whole_image,
     source->source_row, (JDIMENSION) 1, FALSE);

  inptr = image_ptr[0];
  outptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    outptr[2] = *inptr++;	
    outptr[1] = *inptr++;
    outptr[0] = *inptr++;
    outptr += 3;
  }

  return 1;
}



METHODDEF(JDIMENSION)
preload_image (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  bmp_source_ptr source = (bmp_source_ptr) sinfo;
  register FILE *infile = source->pub.input_file;
  register int c;
  register JSAMPROW out_ptr;
  JSAMPARRAY image_ptr;
  JDIMENSION row, col;
  cd_progress_ptr progress = (cd_progress_ptr) cinfo->progress;

  
  for (row = 0; row < cinfo->image_height; row++) {
    if (progress != NULL) {
      progress->pub.pass_counter = (long) row;
      progress->pub.pass_limit = (long) cinfo->image_height;
      (*progress->pub.progress_monitor) ((j_common_ptr) cinfo);
    }
    image_ptr = (*cinfo->mem->access_virt_sarray)
      ((j_common_ptr) cinfo, source->whole_image,
       row, (JDIMENSION) 1, TRUE);
    out_ptr = image_ptr[0];
    for (col = source->row_width; col > 0; col--) {
      
      if ((c = getc(infile)) == EOF)
	ERREXIT(cinfo, JERR_INPUT_EOF);
      *out_ptr++ = (JSAMPLE) c;
    }
  }
  if (progress != NULL)
    progress->completed_extra_passes++;

  
  switch (source->bits_per_pixel) {
  case 8:
    source->pub.get_pixel_rows = get_8bit_row;
    break;
  case 24:
    source->pub.get_pixel_rows = get_24bit_row;
    break;
  default:
    ERREXIT(cinfo, JERR_BMP_BADDEPTH);
  }
  source->source_row = cinfo->image_height;

  
  return (*source->pub.get_pixel_rows) (cinfo, sinfo);
}



METHODDEF(void)
start_input_bmp (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  bmp_source_ptr source = (bmp_source_ptr) sinfo;
  U_CHAR bmpfileheader[14];
  U_CHAR bmpinfoheader[64];
#define GET_2B(array,offset)  ((unsigned int) UCH(array[offset]) + \
			       (((unsigned int) UCH(array[offset+1])) << 8))
#define GET_4B(array,offset)  ((INT32) UCH(array[offset]) + \
			       (((INT32) UCH(array[offset+1])) << 8) + \
			       (((INT32) UCH(array[offset+2])) << 16) + \
			       (((INT32) UCH(array[offset+3])) << 24))
  INT32 bfOffBits;
  INT32 headerSize;
  INT32 biWidth = 0;		
  INT32 biHeight = 0;
  unsigned int biPlanes;
  INT32 biCompression;
  INT32 biXPelsPerMeter,biYPelsPerMeter;
  INT32 biClrUsed = 0;
  int mapentrysize = 0;		
  INT32 bPad;
  JDIMENSION row_width;

  
  if (! ReadOK(source->pub.input_file, bmpfileheader, 14))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  if (GET_2B(bmpfileheader,0) != 0x4D42) 
    ERREXIT(cinfo, JERR_BMP_NOT);
  bfOffBits = (INT32) GET_4B(bmpfileheader,10);
  

  if (! ReadOK(source->pub.input_file, bmpinfoheader, 4))
    ERREXIT(cinfo, JERR_INPUT_EOF);
  headerSize = (INT32) GET_4B(bmpinfoheader,0);
  if (headerSize < 12 || headerSize > 64)
    ERREXIT(cinfo, JERR_BMP_BADHEADER);
  if (! ReadOK(source->pub.input_file, bmpinfoheader+4, headerSize-4))
    ERREXIT(cinfo, JERR_INPUT_EOF);

  switch ((int) headerSize) {
  case 12:
    
    biWidth = (INT32) GET_2B(bmpinfoheader,4);
    biHeight = (INT32) GET_2B(bmpinfoheader,6);
    biPlanes = GET_2B(bmpinfoheader,8);
    source->bits_per_pixel = (int) GET_2B(bmpinfoheader,10);

    switch (source->bits_per_pixel) {
    case 8:			
      mapentrysize = 3;		
      TRACEMS2(cinfo, 1, JTRC_BMP_OS2_MAPPED, (int) biWidth, (int) biHeight);
      break;
    case 24:			
      TRACEMS2(cinfo, 1, JTRC_BMP_OS2, (int) biWidth, (int) biHeight);
      break;
    default:
      ERREXIT(cinfo, JERR_BMP_BADDEPTH);
      break;
    }
    if (biPlanes != 1)
      ERREXIT(cinfo, JERR_BMP_BADPLANES);
    break;
  case 40:
  case 64:
    
    
    biWidth = GET_4B(bmpinfoheader,4);
    biHeight = GET_4B(bmpinfoheader,8);
    biPlanes = GET_2B(bmpinfoheader,12);
    source->bits_per_pixel = (int) GET_2B(bmpinfoheader,14);
    biCompression = GET_4B(bmpinfoheader,16);
    biXPelsPerMeter = GET_4B(bmpinfoheader,24);
    biYPelsPerMeter = GET_4B(bmpinfoheader,28);
    biClrUsed = GET_4B(bmpinfoheader,32);
    

    switch (source->bits_per_pixel) {
    case 8:			
      mapentrysize = 4;		
      TRACEMS2(cinfo, 1, JTRC_BMP_MAPPED, (int) biWidth, (int) biHeight);
      break;
    case 24:			
      TRACEMS2(cinfo, 1, JTRC_BMP, (int) biWidth, (int) biHeight);
      break;
    default:
      ERREXIT(cinfo, JERR_BMP_BADDEPTH);
      break;
    }
    if (biPlanes != 1)
      ERREXIT(cinfo, JERR_BMP_BADPLANES);
    if (biCompression != 0)
      ERREXIT(cinfo, JERR_BMP_COMPRESSED);

    if (biXPelsPerMeter > 0 && biYPelsPerMeter > 0) {
      
      cinfo->X_density = (UINT16) (biXPelsPerMeter/100); 
      cinfo->Y_density = (UINT16) (biYPelsPerMeter/100);
      cinfo->density_unit = 2;	
    }
    break;
  default:
    ERREXIT(cinfo, JERR_BMP_BADHEADER);
    break;
  }

  
  bPad = bfOffBits - (headerSize + 14);

  
  if (mapentrysize > 0) {
    if (biClrUsed <= 0)
      biClrUsed = 256;		
    else if (biClrUsed > 256)
      ERREXIT(cinfo, JERR_BMP_BADCMAP);
    
    source->colormap = (*cinfo->mem->alloc_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE,
       (JDIMENSION) biClrUsed, (JDIMENSION) 3);
    
    read_colormap(source, (int) biClrUsed, mapentrysize);
    
    bPad -= biClrUsed * mapentrysize;
  }

  
  if (bPad < 0)			
    ERREXIT(cinfo, JERR_BMP_BADHEADER);
  while (--bPad >= 0) {
    (void) read_byte(source);
  }

  
  if (source->bits_per_pixel == 24)
    row_width = (JDIMENSION) (biWidth * 3);
  else
    row_width = (JDIMENSION) biWidth;
  while ((row_width & 3) != 0) row_width++;
  source->row_width = row_width;

  
  source->whole_image = (*cinfo->mem->request_virt_sarray)
    ((j_common_ptr) cinfo, JPOOL_IMAGE, FALSE,
     row_width, (JDIMENSION) biHeight, (JDIMENSION) 1);
  source->pub.get_pixel_rows = preload_image;
  if (cinfo->progress != NULL) {
    cd_progress_ptr progress = (cd_progress_ptr) cinfo->progress;
    progress->total_extra_passes++; 
  }

  
  source->pub.buffer = (*cinfo->mem->alloc_sarray)
    ((j_common_ptr) cinfo, JPOOL_IMAGE,
     (JDIMENSION) (biWidth * 3), (JDIMENSION) 1);
  source->pub.buffer_height = 1;

  cinfo->in_color_space = JCS_RGB;
  cinfo->input_components = 3;
  cinfo->data_precision = 8;
  cinfo->image_width = (JDIMENSION) biWidth;
  cinfo->image_height = (JDIMENSION) biHeight;
}



METHODDEF(void)
finish_input_bmp (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  
}



GLOBAL(cjpeg_source_ptr)
jinit_read_bmp (j_compress_ptr cinfo)
{
  bmp_source_ptr source;

  
  source = (bmp_source_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(bmp_source_struct));
  source->cinfo = cinfo;	
  
  source->pub.start_input = start_input_bmp;
  source->pub.finish_input = finish_input_bmp;

  return (cjpeg_source_ptr) source;
}

#endif 
