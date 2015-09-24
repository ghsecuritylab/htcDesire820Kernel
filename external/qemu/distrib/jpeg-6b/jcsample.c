/*
 * jcsample.c
 *
 * Copyright (C) 1991-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains downsampling routines.
 *
 * Downsampling input data is counted in "row groups".  A row group
 * is defined to be max_v_samp_factor pixel rows of each component,
 * from which the downsampler produces v_samp_factor sample rows.
 * A single row group is processed in each call to the downsampler module.
 *
 * The downsampler is responsible for edge-expansion of its output data
 * to fill an integral number of DCT blocks horizontally.  The source buffer
 * may be modified if it is helpful for this purpose (the source buffer is
 * allocated wide enough to correspond to the desired output width).
 * The caller (the prep controller) is responsible for vertical padding.
 *
 * The downsampler may request "context rows" by setting need_context_rows
 * during startup.  In this case, the input arrays will contain at least
 * one row group's worth of pixels above and below the passed-in data;
 * the caller will create dummy rows at image top and bottom by replicating
 * the first or last real pixel row.
 *
 * An excellent reference for image resampling is
 *   Digital Image Warping, George Wolberg, 1990.
 *   Pub. by IEEE Computer Society Press, Los Alamitos, CA. ISBN 0-8186-8944-7.
 *
 * The downsampling algorithm used here is a simple average of the source
 * pixels covered by the output pixel.  The hi-falutin sampling literature
 * refers to this as a "box filter".  In general the characteristics of a box
 * filter are not very good, but for the specific cases we normally use (1:1
 * and 2:1 ratios) the box is equivalent to a "triangle filter" which is not
 * nearly so bad.  If you intend to use other sampling ratios, you'd be well
 * advised to improve this code.
 *
 * A simple input-smoothing capability is provided.  This is mainly intended
 * for cleaning up color-dithered GIF input files (if you find it inadequate,
 * we suggest using an external filtering program such as pnmconvol).  When
 * enabled, each input pixel P is replaced by a weighted sum of itself and its
 * eight neighbors.  P's weight is 1-8*SF and each neighbor's weight is SF,
 * where SF = (smoothing_factor / 1024).
 * Currently, smoothing is only supported for 2h2v sampling factors.
 */

#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"


typedef JMETHOD(void, downsample1_ptr,
		(j_compress_ptr cinfo, jpeg_component_info * compptr,
		 JSAMPARRAY input_data, JSAMPARRAY output_data));


typedef struct {
  struct jpeg_downsampler pub;	

  
  downsample1_ptr methods[MAX_COMPONENTS];
} my_downsampler;

typedef my_downsampler * my_downsample_ptr;



METHODDEF(void)
start_pass_downsample (j_compress_ptr cinfo)
{
  
}



LOCAL(void)
expand_right_edge (JSAMPARRAY image_data, int num_rows,
		   JDIMENSION input_cols, JDIMENSION output_cols)
{
  register JSAMPROW ptr;
  register JSAMPLE pixval;
  register int count;
  int row;
  int numcols = (int) (output_cols - input_cols);

  if (numcols > 0) {
    for (row = 0; row < num_rows; row++) {
      ptr = image_data[row] + input_cols;
      pixval = ptr[-1];		
      for (count = numcols; count > 0; count--)
	*ptr++ = pixval;
    }
  }
}



METHODDEF(void)
sep_downsample (j_compress_ptr cinfo,
		JSAMPIMAGE input_buf, JDIMENSION in_row_index,
		JSAMPIMAGE output_buf, JDIMENSION out_row_group_index)
{
  my_downsample_ptr downsample = (my_downsample_ptr) cinfo->downsample;
  int ci;
  jpeg_component_info * compptr;
  JSAMPARRAY in_ptr, out_ptr;

  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {
    in_ptr = input_buf[ci] + in_row_index;
    out_ptr = output_buf[ci] + (out_row_group_index * compptr->v_samp_factor);
    (*downsample->methods[ci]) (cinfo, compptr, in_ptr, out_ptr);
  }
}



METHODDEF(void)
int_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
		JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int inrow, outrow, h_expand, v_expand, numpix, numpix2, h, v;
  JDIMENSION outcol, outcol_h;	
  JDIMENSION output_cols = compptr->width_in_blocks * DCTSIZE;
  JSAMPROW inptr, outptr;
  INT32 outvalue;

  h_expand = cinfo->max_h_samp_factor / compptr->h_samp_factor;
  v_expand = cinfo->max_v_samp_factor / compptr->v_samp_factor;
  numpix = h_expand * v_expand;
  numpix2 = numpix/2;

  expand_right_edge(input_data, cinfo->max_v_samp_factor,
		    cinfo->image_width, output_cols * h_expand);

  inrow = 0;
  for (outrow = 0; outrow < compptr->v_samp_factor; outrow++) {
    outptr = output_data[outrow];
    for (outcol = 0, outcol_h = 0; outcol < output_cols;
	 outcol++, outcol_h += h_expand) {
      outvalue = 0;
      for (v = 0; v < v_expand; v++) {
	inptr = input_data[inrow+v] + outcol_h;
	for (h = 0; h < h_expand; h++) {
	  outvalue += (INT32) GETJSAMPLE(*inptr++);
	}
      }
      *outptr++ = (JSAMPLE) ((outvalue + numpix2) / numpix);
    }
    inrow += v_expand;
  }
}



METHODDEF(void)
fullsize_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
		     JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  
  jcopy_sample_rows(input_data, 0, output_data, 0,
		    cinfo->max_v_samp_factor, cinfo->image_width);
  
  expand_right_edge(output_data, cinfo->max_v_samp_factor,
		    cinfo->image_width, compptr->width_in_blocks * DCTSIZE);
}



METHODDEF(void)
h2v1_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
		 JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int outrow;
  JDIMENSION outcol;
  JDIMENSION output_cols = compptr->width_in_blocks * DCTSIZE;
  register JSAMPROW inptr, outptr;
  register int bias;

  expand_right_edge(input_data, cinfo->max_v_samp_factor,
		    cinfo->image_width, output_cols * 2);

  for (outrow = 0; outrow < compptr->v_samp_factor; outrow++) {
    outptr = output_data[outrow];
    inptr = input_data[outrow];
    bias = 0;			
    for (outcol = 0; outcol < output_cols; outcol++) {
      *outptr++ = (JSAMPLE) ((GETJSAMPLE(*inptr) + GETJSAMPLE(inptr[1])
			      + bias) >> 1);
      bias ^= 1;		
      inptr += 2;
    }
  }
}



METHODDEF(void)
h2v2_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
		 JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int inrow, outrow;
  JDIMENSION outcol;
  JDIMENSION output_cols = compptr->width_in_blocks * DCTSIZE;
  register JSAMPROW inptr0, inptr1, outptr;
  register int bias;

  expand_right_edge(input_data, cinfo->max_v_samp_factor,
		    cinfo->image_width, output_cols * 2);

  inrow = 0;
  for (outrow = 0; outrow < compptr->v_samp_factor; outrow++) {
    outptr = output_data[outrow];
    inptr0 = input_data[inrow];
    inptr1 = input_data[inrow+1];
    bias = 1;			
    for (outcol = 0; outcol < output_cols; outcol++) {
      *outptr++ = (JSAMPLE) ((GETJSAMPLE(*inptr0) + GETJSAMPLE(inptr0[1]) +
			      GETJSAMPLE(*inptr1) + GETJSAMPLE(inptr1[1])
			      + bias) >> 2);
      bias ^= 3;		
      inptr0 += 2; inptr1 += 2;
    }
    inrow += 2;
  }
}


#ifdef INPUT_SMOOTHING_SUPPORTED


METHODDEF(void)
h2v2_smooth_downsample (j_compress_ptr cinfo, jpeg_component_info * compptr,
			JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int inrow, outrow;
  JDIMENSION colctr;
  JDIMENSION output_cols = compptr->width_in_blocks * DCTSIZE;
  register JSAMPROW inptr0, inptr1, above_ptr, below_ptr, outptr;
  INT32 membersum, neighsum, memberscale, neighscale;

  expand_right_edge(input_data - 1, cinfo->max_v_samp_factor + 2,
		    cinfo->image_width, output_cols * 2);


  memberscale = 16384 - cinfo->smoothing_factor * 80; 
  neighscale = cinfo->smoothing_factor * 16; 

  inrow = 0;
  for (outrow = 0; outrow < compptr->v_samp_factor; outrow++) {
    outptr = output_data[outrow];
    inptr0 = input_data[inrow];
    inptr1 = input_data[inrow+1];
    above_ptr = input_data[inrow-1];
    below_ptr = input_data[inrow+2];

    
    membersum = GETJSAMPLE(*inptr0) + GETJSAMPLE(inptr0[1]) +
		GETJSAMPLE(*inptr1) + GETJSAMPLE(inptr1[1]);
    neighsum = GETJSAMPLE(*above_ptr) + GETJSAMPLE(above_ptr[1]) +
	       GETJSAMPLE(*below_ptr) + GETJSAMPLE(below_ptr[1]) +
	       GETJSAMPLE(*inptr0) + GETJSAMPLE(inptr0[2]) +
	       GETJSAMPLE(*inptr1) + GETJSAMPLE(inptr1[2]);
    neighsum += neighsum;
    neighsum += GETJSAMPLE(*above_ptr) + GETJSAMPLE(above_ptr[2]) +
		GETJSAMPLE(*below_ptr) + GETJSAMPLE(below_ptr[2]);
    membersum = membersum * memberscale + neighsum * neighscale;
    *outptr++ = (JSAMPLE) ((membersum + 32768) >> 16);
    inptr0 += 2; inptr1 += 2; above_ptr += 2; below_ptr += 2;

    for (colctr = output_cols - 2; colctr > 0; colctr--) {
      
      membersum = GETJSAMPLE(*inptr0) + GETJSAMPLE(inptr0[1]) +
		  GETJSAMPLE(*inptr1) + GETJSAMPLE(inptr1[1]);
      
      neighsum = GETJSAMPLE(*above_ptr) + GETJSAMPLE(above_ptr[1]) +
		 GETJSAMPLE(*below_ptr) + GETJSAMPLE(below_ptr[1]) +
		 GETJSAMPLE(inptr0[-1]) + GETJSAMPLE(inptr0[2]) +
		 GETJSAMPLE(inptr1[-1]) + GETJSAMPLE(inptr1[2]);
      
      neighsum += neighsum;
      
      neighsum += GETJSAMPLE(above_ptr[-1]) + GETJSAMPLE(above_ptr[2]) +
		  GETJSAMPLE(below_ptr[-1]) + GETJSAMPLE(below_ptr[2]);
      
      membersum = membersum * memberscale + neighsum * neighscale;
      
      *outptr++ = (JSAMPLE) ((membersum + 32768) >> 16);
      inptr0 += 2; inptr1 += 2; above_ptr += 2; below_ptr += 2;
    }

    
    membersum = GETJSAMPLE(*inptr0) + GETJSAMPLE(inptr0[1]) +
		GETJSAMPLE(*inptr1) + GETJSAMPLE(inptr1[1]);
    neighsum = GETJSAMPLE(*above_ptr) + GETJSAMPLE(above_ptr[1]) +
	       GETJSAMPLE(*below_ptr) + GETJSAMPLE(below_ptr[1]) +
	       GETJSAMPLE(inptr0[-1]) + GETJSAMPLE(inptr0[1]) +
	       GETJSAMPLE(inptr1[-1]) + GETJSAMPLE(inptr1[1]);
    neighsum += neighsum;
    neighsum += GETJSAMPLE(above_ptr[-1]) + GETJSAMPLE(above_ptr[1]) +
		GETJSAMPLE(below_ptr[-1]) + GETJSAMPLE(below_ptr[1]);
    membersum = membersum * memberscale + neighsum * neighscale;
    *outptr = (JSAMPLE) ((membersum + 32768) >> 16);

    inrow += 2;
  }
}



METHODDEF(void)
fullsize_smooth_downsample (j_compress_ptr cinfo, jpeg_component_info *compptr,
			    JSAMPARRAY input_data, JSAMPARRAY output_data)
{
  int outrow;
  JDIMENSION colctr;
  JDIMENSION output_cols = compptr->width_in_blocks * DCTSIZE;
  register JSAMPROW inptr, above_ptr, below_ptr, outptr;
  INT32 membersum, neighsum, memberscale, neighscale;
  int colsum, lastcolsum, nextcolsum;

  expand_right_edge(input_data - 1, cinfo->max_v_samp_factor + 2,
		    cinfo->image_width, output_cols);


  memberscale = 65536L - cinfo->smoothing_factor * 512L; 
  neighscale = cinfo->smoothing_factor * 64; 

  for (outrow = 0; outrow < compptr->v_samp_factor; outrow++) {
    outptr = output_data[outrow];
    inptr = input_data[outrow];
    above_ptr = input_data[outrow-1];
    below_ptr = input_data[outrow+1];

    
    colsum = GETJSAMPLE(*above_ptr++) + GETJSAMPLE(*below_ptr++) +
	     GETJSAMPLE(*inptr);
    membersum = GETJSAMPLE(*inptr++);
    nextcolsum = GETJSAMPLE(*above_ptr) + GETJSAMPLE(*below_ptr) +
		 GETJSAMPLE(*inptr);
    neighsum = colsum + (colsum - membersum) + nextcolsum;
    membersum = membersum * memberscale + neighsum * neighscale;
    *outptr++ = (JSAMPLE) ((membersum + 32768) >> 16);
    lastcolsum = colsum; colsum = nextcolsum;

    for (colctr = output_cols - 2; colctr > 0; colctr--) {
      membersum = GETJSAMPLE(*inptr++);
      above_ptr++; below_ptr++;
      nextcolsum = GETJSAMPLE(*above_ptr) + GETJSAMPLE(*below_ptr) +
		   GETJSAMPLE(*inptr);
      neighsum = lastcolsum + (colsum - membersum) + nextcolsum;
      membersum = membersum * memberscale + neighsum * neighscale;
      *outptr++ = (JSAMPLE) ((membersum + 32768) >> 16);
      lastcolsum = colsum; colsum = nextcolsum;
    }

    
    membersum = GETJSAMPLE(*inptr);
    neighsum = lastcolsum + (colsum - membersum) + colsum;
    membersum = membersum * memberscale + neighsum * neighscale;
    *outptr = (JSAMPLE) ((membersum + 32768) >> 16);

  }
}

#endif 



GLOBAL(void)
jinit_downsampler (j_compress_ptr cinfo)
{
  my_downsample_ptr downsample;
  int ci;
  jpeg_component_info * compptr;
  boolean smoothok = TRUE;

  downsample = (my_downsample_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_downsampler));
  cinfo->downsample = (struct jpeg_downsampler *) downsample;
  downsample->pub.start_pass = start_pass_downsample;
  downsample->pub.downsample = sep_downsample;
  downsample->pub.need_context_rows = FALSE;

  if (cinfo->CCIR601_sampling)
    ERREXIT(cinfo, JERR_CCIR601_NOTIMPL);

  
  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {
    if (compptr->h_samp_factor == cinfo->max_h_samp_factor &&
	compptr->v_samp_factor == cinfo->max_v_samp_factor) {
#ifdef INPUT_SMOOTHING_SUPPORTED
      if (cinfo->smoothing_factor) {
	downsample->methods[ci] = fullsize_smooth_downsample;
	downsample->pub.need_context_rows = TRUE;
      } else
#endif
	downsample->methods[ci] = fullsize_downsample;
    } else if (compptr->h_samp_factor * 2 == cinfo->max_h_samp_factor &&
	       compptr->v_samp_factor == cinfo->max_v_samp_factor) {
      smoothok = FALSE;
      downsample->methods[ci] = h2v1_downsample;
    } else if (compptr->h_samp_factor * 2 == cinfo->max_h_samp_factor &&
	       compptr->v_samp_factor * 2 == cinfo->max_v_samp_factor) {
#ifdef INPUT_SMOOTHING_SUPPORTED
      if (cinfo->smoothing_factor) {
	downsample->methods[ci] = h2v2_smooth_downsample;
	downsample->pub.need_context_rows = TRUE;
      } else
#endif
	downsample->methods[ci] = h2v2_downsample;
    } else if ((cinfo->max_h_samp_factor % compptr->h_samp_factor) == 0 &&
	       (cinfo->max_v_samp_factor % compptr->v_samp_factor) == 0) {
      smoothok = FALSE;
      downsample->methods[ci] = int_downsample;
    } else
      ERREXIT(cinfo, JERR_FRACT_SAMPLE_NOTIMPL);
  }

#ifdef INPUT_SMOOTHING_SUPPORTED
  if (cinfo->smoothing_factor && !smoothok)
    TRACEMS(cinfo, 0, JTRC_SMOOTH_NOTIMPL);
#endif
}
