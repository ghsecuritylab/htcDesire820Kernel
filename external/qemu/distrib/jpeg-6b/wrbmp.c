/*
 * wrbmp.c
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains routines to write output images in Microsoft "BMP"
 * format (MS Windows 3.x and OS/2 1.x flavors).
 * Either 8-bit colormapped or 24-bit full-color format can be written.
 * No compression is supported.
 *
 * These routines may need modification for non-Unix environments or
 * specialized applications.  As they stand, they assume output to
 * an ordinary stdio stream.
 *
 * This code contributed by James Arthur Boucher.
 */

#include "cdjpeg.h"		

#ifdef BMP_SUPPORTED



#if BITS_IN_JSAMPLE != 8
  Sorry, this code only copes with 8-bit JSAMPLEs. 
#endif



typedef struct {
  struct djpeg_dest_struct pub;	

  boolean is_os2;		

  jvirt_sarray_ptr whole_image;	
  JDIMENSION data_width;	
  JDIMENSION row_width;		
  int pad_bytes;		
  JDIMENSION cur_output_row;	
} bmp_dest_struct;

typedef bmp_dest_struct * bmp_dest_ptr;


LOCAL(void) write_colormap
	JPP((j_decompress_ptr cinfo, bmp_dest_ptr dest,
	     int map_colors, int map_entry_size));



METHODDEF(void)
put_pixel_rows (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo,
		JDIMENSION rows_supplied)
{
  bmp_dest_ptr dest = (bmp_dest_ptr) dinfo;
  JSAMPARRAY image_ptr;
  register JSAMPROW inptr, outptr;
  register JDIMENSION col;
  int pad;

  
  image_ptr = (*cinfo->mem->access_virt_sarray)
    ((j_common_ptr) cinfo, dest->whole_image,
     dest->cur_output_row, (JDIMENSION) 1, TRUE);
  dest->cur_output_row++;

  inptr = dest->pub.buffer[0];
  outptr = image_ptr[0];
  for (col = cinfo->output_width; col > 0; col--) {
    outptr[2] = *inptr++;	
    outptr[1] = *inptr++;
    outptr[0] = *inptr++;
    outptr += 3;
  }

  
  pad = dest->pad_bytes;
  while (--pad >= 0)
    *outptr++ = 0;
}

METHODDEF(void)
put_gray_rows (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo,
	       JDIMENSION rows_supplied)
{
  bmp_dest_ptr dest = (bmp_dest_ptr) dinfo;
  JSAMPARRAY image_ptr;
  register JSAMPROW inptr, outptr;
  register JDIMENSION col;
  int pad;

  
  image_ptr = (*cinfo->mem->access_virt_sarray)
    ((j_common_ptr) cinfo, dest->whole_image,
     dest->cur_output_row, (JDIMENSION) 1, TRUE);
  dest->cur_output_row++;

  
  inptr = dest->pub.buffer[0];
  outptr = image_ptr[0];
  for (col = cinfo->output_width; col > 0; col--) {
    *outptr++ = *inptr++;	
  }

  
  pad = dest->pad_bytes;
  while (--pad >= 0)
    *outptr++ = 0;
}



METHODDEF(void)
start_output_bmp (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo)
{
  
}



LOCAL(void)
write_bmp_header (j_decompress_ptr cinfo, bmp_dest_ptr dest)
{
  char bmpfileheader[14];
  char bmpinfoheader[40];
#define PUT_2B(array,offset,value)  \
	(array[offset] = (char) ((value) & 0xFF), \
	 array[offset+1] = (char) (((value) >> 8) & 0xFF))
#define PUT_4B(array,offset,value)  \
	(array[offset] = (char) ((value) & 0xFF), \
	 array[offset+1] = (char) (((value) >> 8) & 0xFF), \
	 array[offset+2] = (char) (((value) >> 16) & 0xFF), \
	 array[offset+3] = (char) (((value) >> 24) & 0xFF))
  INT32 headersize, bfSize;
  int bits_per_pixel, cmap_entries;

  
  if (cinfo->out_color_space == JCS_RGB) {
    if (cinfo->quantize_colors) {
      
      bits_per_pixel = 8;
      cmap_entries = 256;
    } else {
      
      bits_per_pixel = 24;
      cmap_entries = 0;
    }
  } else {
    
    bits_per_pixel = 8;
    cmap_entries = 256;
  }
  
  headersize = 14 + 40 + cmap_entries * 4; 
  bfSize = headersize + (INT32) dest->row_width * (INT32) cinfo->output_height;
  
  
  MEMZERO(bmpfileheader, SIZEOF(bmpfileheader));
  MEMZERO(bmpinfoheader, SIZEOF(bmpinfoheader));

  
  bmpfileheader[0] = 0x42;	
  bmpfileheader[1] = 0x4D;
  PUT_4B(bmpfileheader, 2, bfSize); 
  
  PUT_4B(bmpfileheader, 10, headersize); 

  
  PUT_2B(bmpinfoheader, 0, 40);	
  PUT_4B(bmpinfoheader, 4, cinfo->output_width); 
  PUT_4B(bmpinfoheader, 8, cinfo->output_height); 
  PUT_2B(bmpinfoheader, 12, 1);	
  PUT_2B(bmpinfoheader, 14, bits_per_pixel); 
  
  
  if (cinfo->density_unit == 2) { 
    PUT_4B(bmpinfoheader, 24, (INT32) (cinfo->X_density*100)); 
    PUT_4B(bmpinfoheader, 28, (INT32) (cinfo->Y_density*100)); 
  }
  PUT_2B(bmpinfoheader, 32, cmap_entries); 
  

  if (JFWRITE(dest->pub.output_file, bmpfileheader, 14) != (size_t) 14)
    ERREXIT(cinfo, JERR_FILE_WRITE);
  if (JFWRITE(dest->pub.output_file, bmpinfoheader, 40) != (size_t) 40)
    ERREXIT(cinfo, JERR_FILE_WRITE);

  if (cmap_entries > 0)
    write_colormap(cinfo, dest, cmap_entries, 4);
}


LOCAL(void)
write_os2_header (j_decompress_ptr cinfo, bmp_dest_ptr dest)
{
  char bmpfileheader[14];
  char bmpcoreheader[12];
  INT32 headersize, bfSize;
  int bits_per_pixel, cmap_entries;

  
  if (cinfo->out_color_space == JCS_RGB) {
    if (cinfo->quantize_colors) {
      
      bits_per_pixel = 8;
      cmap_entries = 256;
    } else {
      
      bits_per_pixel = 24;
      cmap_entries = 0;
    }
  } else {
    
    bits_per_pixel = 8;
    cmap_entries = 256;
  }
  
  headersize = 14 + 12 + cmap_entries * 3; 
  bfSize = headersize + (INT32) dest->row_width * (INT32) cinfo->output_height;
  
  
  MEMZERO(bmpfileheader, SIZEOF(bmpfileheader));
  MEMZERO(bmpcoreheader, SIZEOF(bmpcoreheader));

  
  bmpfileheader[0] = 0x42;	
  bmpfileheader[1] = 0x4D;
  PUT_4B(bmpfileheader, 2, bfSize); 
  
  PUT_4B(bmpfileheader, 10, headersize); 

  
  PUT_2B(bmpcoreheader, 0, 12);	
  PUT_2B(bmpcoreheader, 4, cinfo->output_width); 
  PUT_2B(bmpcoreheader, 6, cinfo->output_height); 
  PUT_2B(bmpcoreheader, 8, 1);	
  PUT_2B(bmpcoreheader, 10, bits_per_pixel); 

  if (JFWRITE(dest->pub.output_file, bmpfileheader, 14) != (size_t) 14)
    ERREXIT(cinfo, JERR_FILE_WRITE);
  if (JFWRITE(dest->pub.output_file, bmpcoreheader, 12) != (size_t) 12)
    ERREXIT(cinfo, JERR_FILE_WRITE);

  if (cmap_entries > 0)
    write_colormap(cinfo, dest, cmap_entries, 3);
}



LOCAL(void)
write_colormap (j_decompress_ptr cinfo, bmp_dest_ptr dest,
		int map_colors, int map_entry_size)
{
  JSAMPARRAY colormap = cinfo->colormap;
  int num_colors = cinfo->actual_number_of_colors;
  FILE * outfile = dest->pub.output_file;
  int i;

  if (colormap != NULL) {
    if (cinfo->out_color_components == 3) {
      
      for (i = 0; i < num_colors; i++) {
	putc(GETJSAMPLE(colormap[2][i]), outfile);
	putc(GETJSAMPLE(colormap[1][i]), outfile);
	putc(GETJSAMPLE(colormap[0][i]), outfile);
	if (map_entry_size == 4)
	  putc(0, outfile);
      }
    } else {
      
      for (i = 0; i < num_colors; i++) {
	putc(GETJSAMPLE(colormap[0][i]), outfile);
	putc(GETJSAMPLE(colormap[0][i]), outfile);
	putc(GETJSAMPLE(colormap[0][i]), outfile);
	if (map_entry_size == 4)
	  putc(0, outfile);
      }
    }
  } else {
    
    for (i = 0; i < 256; i++) {
      putc(i, outfile);
      putc(i, outfile);
      putc(i, outfile);
      if (map_entry_size == 4)
	putc(0, outfile);
    }
  }
   
  if (i > map_colors)
    ERREXIT1(cinfo, JERR_TOO_MANY_COLORS, i);
  for (; i < map_colors; i++) {
    putc(0, outfile);
    putc(0, outfile);
    putc(0, outfile);
    if (map_entry_size == 4)
      putc(0, outfile);
  }
}


METHODDEF(void)
finish_output_bmp (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo)
{
  bmp_dest_ptr dest = (bmp_dest_ptr) dinfo;
  register FILE * outfile = dest->pub.output_file;
  JSAMPARRAY image_ptr;
  register JSAMPROW data_ptr;
  JDIMENSION row;
  register JDIMENSION col;
  cd_progress_ptr progress = (cd_progress_ptr) cinfo->progress;

  
  if (dest->is_os2)
    write_os2_header(cinfo, dest);
  else
    write_bmp_header(cinfo, dest);

  
  for (row = cinfo->output_height; row > 0; row--) {
    if (progress != NULL) {
      progress->pub.pass_counter = (long) (cinfo->output_height - row);
      progress->pub.pass_limit = (long) cinfo->output_height;
      (*progress->pub.progress_monitor) ((j_common_ptr) cinfo);
    }
    image_ptr = (*cinfo->mem->access_virt_sarray)
      ((j_common_ptr) cinfo, dest->whole_image, row-1, (JDIMENSION) 1, FALSE);
    data_ptr = image_ptr[0];
    for (col = dest->row_width; col > 0; col--) {
      putc(GETJSAMPLE(*data_ptr), outfile);
      data_ptr++;
    }
  }
  if (progress != NULL)
    progress->completed_extra_passes++;

  
  fflush(outfile);
  if (ferror(outfile))
    ERREXIT(cinfo, JERR_FILE_WRITE);
}



GLOBAL(djpeg_dest_ptr)
jinit_write_bmp (j_decompress_ptr cinfo, boolean is_os2)
{
  bmp_dest_ptr dest;
  JDIMENSION row_width;

  
  dest = (bmp_dest_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(bmp_dest_struct));
  dest->pub.start_output = start_output_bmp;
  dest->pub.finish_output = finish_output_bmp;
  dest->is_os2 = is_os2;

  if (cinfo->out_color_space == JCS_GRAYSCALE) {
    dest->pub.put_pixel_rows = put_gray_rows;
  } else if (cinfo->out_color_space == JCS_RGB) {
    if (cinfo->quantize_colors)
      dest->pub.put_pixel_rows = put_gray_rows;
    else
      dest->pub.put_pixel_rows = put_pixel_rows;
  } else {
    ERREXIT(cinfo, JERR_BMP_COLORSPACE);
  }

  
  jpeg_calc_output_dimensions(cinfo);

  
  row_width = cinfo->output_width * cinfo->output_components;
  dest->data_width = row_width;
  while ((row_width & 3) != 0) row_width++;
  dest->row_width = row_width;
  dest->pad_bytes = (int) (row_width - dest->data_width);

  
  dest->whole_image = (*cinfo->mem->request_virt_sarray)
    ((j_common_ptr) cinfo, JPOOL_IMAGE, FALSE,
     row_width, cinfo->output_height, (JDIMENSION) 1);
  dest->cur_output_row = 0;
  if (cinfo->progress != NULL) {
    cd_progress_ptr progress = (cd_progress_ptr) cinfo->progress;
    progress->total_extra_passes++; 
  }

  
  dest->pub.buffer = (*cinfo->mem->alloc_sarray)
    ((j_common_ptr) cinfo, JPOOL_IMAGE, row_width, (JDIMENSION) 1);
  dest->pub.buffer_height = 1;

  return (djpeg_dest_ptr) dest;
}

#endif 
