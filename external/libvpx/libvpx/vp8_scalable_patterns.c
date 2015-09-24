/*
 *  Copyright (c) 2012 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#define VPX_CODEC_DISABLE_COMPAT 1
#include "vpx/vpx_encoder.h"
#include "vpx/vp8cx.h"
#define interface (vpx_codec_vp8_cx())
#define fourcc    0x30385056

#define IVF_FILE_HDR_SZ  (32)
#define IVF_FRAME_HDR_SZ (12)

static void mem_put_le16(char *mem, unsigned int val) {
    mem[0] = val;
    mem[1] = val>>8;
}

static void mem_put_le32(char *mem, unsigned int val) {
    mem[0] = val;
    mem[1] = val>>8;
    mem[2] = val>>16;
    mem[3] = val>>24;
}

static void die(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vprintf(fmt, ap);
    if(fmt[strlen(fmt)-1] != '\n')
        printf("\n");
    exit(EXIT_FAILURE);
}

static void die_codec(vpx_codec_ctx_t *ctx, const char *s) {
    const char *detail = vpx_codec_error_detail(ctx);

    printf("%s: %s\n", s, vpx_codec_error(ctx));
    if(detail)
        printf("    %s\n",detail);
    exit(EXIT_FAILURE);
}

static int read_frame(FILE *f, vpx_image_t *img) {
    size_t nbytes, to_read;
    int    res = 1;

    to_read = img->w*img->h*3/2;
    nbytes = fread(img->planes[0], 1, to_read, f);
    if(nbytes != to_read) {
        res = 0;
        if(nbytes > 0)
            printf("Warning: Read partial frame. Check your width & height!\n");
    }
    return res;
}

static void write_ivf_file_header(FILE *outfile,
                                  const vpx_codec_enc_cfg_t *cfg,
                                  int frame_cnt) {
    char header[32];

    if(cfg->g_pass != VPX_RC_ONE_PASS && cfg->g_pass != VPX_RC_LAST_PASS)
        return;
    header[0] = 'D';
    header[1] = 'K';
    header[2] = 'I';
    header[3] = 'F';
    mem_put_le16(header+4,  0);                   
    mem_put_le16(header+6,  32);                  
    mem_put_le32(header+8,  fourcc);              
    mem_put_le16(header+12, cfg->g_w);            
    mem_put_le16(header+14, cfg->g_h);            
    mem_put_le32(header+16, cfg->g_timebase.den); 
    mem_put_le32(header+20, cfg->g_timebase.num); 
    mem_put_le32(header+24, frame_cnt);           
    mem_put_le32(header+28, 0);                   

    (void) fwrite(header, 1, 32, outfile);
}


static void write_ivf_frame_header(FILE *outfile,
                                   const vpx_codec_cx_pkt_t *pkt)
{
    char             header[12];
    vpx_codec_pts_t  pts;

    if(pkt->kind != VPX_CODEC_CX_FRAME_PKT)
        return;

    pts = pkt->data.frame.pts;
    mem_put_le32(header, pkt->data.frame.sz);
    mem_put_le32(header+4, pts&0xFFFFFFFF);
    mem_put_le32(header+8, pts >> 32);

    (void) fwrite(header, 1, 12, outfile);
}

static int mode_to_num_layers[12] = {1, 2, 2, 3, 3, 3, 3, 5, 2, 3, 3, 3};

int main(int argc, char **argv) {
    FILE                *infile, *outfile[VPX_TS_MAX_LAYERS];
    vpx_codec_ctx_t      codec;
    vpx_codec_enc_cfg_t  cfg;
    int                  frame_cnt = 0;
    vpx_image_t          raw;
    vpx_codec_err_t      res;
    unsigned int         width;
    unsigned int         height;
    int                  frame_avail;
    int                  got_data;
    int                  flags = 0;
    int                  i;
    int                  pts = 0;              
    int                  frame_duration = 1;   

    int                  layering_mode = 0;
    int                  frames_in_layer[VPX_TS_MAX_LAYERS] = {0};
    int                  layer_flags[VPX_TS_MAX_PERIODICITY] = {0};
    int                  flag_periodicity;
    int                  max_intra_size_pct;

    
    if (argc < 9)
        die("Usage: %s <infile> <outfile> <width> <height> <rate_num> "
            " <rate_den> <mode> <Rate_0> ... <Rate_nlayers-1>\n", argv[0]);

    width  = strtol (argv[3], NULL, 0);
    height = strtol (argv[4], NULL, 0);
    if (width < 16 || width%2 || height <16 || height%2)
        die ("Invalid resolution: %d x %d", width, height);

    if (!sscanf(argv[7], "%d", &layering_mode))
        die ("Invalid mode %s", argv[7]);
    if (layering_mode<0 || layering_mode>11)
        die ("Invalid mode (0..11) %s", argv[7]);

    if (argc != 8+mode_to_num_layers[layering_mode])
        die ("Invalid number of arguments");

    if (!vpx_img_alloc (&raw, VPX_IMG_FMT_I420, width, height, 32))
        die ("Failed to allocate image", width, height);

    printf("Using %s\n",vpx_codec_iface_name(interface));

    
    res = vpx_codec_enc_config_default(interface, &cfg, 0);
    if(res) {
        printf("Failed to get config: %s\n", vpx_codec_err_to_string(res));
        return EXIT_FAILURE;
    }

    
    cfg.g_w = width;
    cfg.g_h = height;

    
    if (!sscanf (argv[5], "%d", &cfg.g_timebase.num ))
        die ("Invalid timebase numerator %s", argv[5]);
    if (!sscanf (argv[6], "%d", &cfg.g_timebase.den ))
        die ("Invalid timebase denominator %s", argv[6]);

    for (i=8; i<8+mode_to_num_layers[layering_mode]; i++)
        if (!sscanf(argv[i], "%ud", &cfg.ts_target_bitrate[i-8]))
            die ("Invalid data rate %s", argv[i]);

    
    cfg.rc_dropframe_thresh = 0;
    cfg.rc_end_usage        = VPX_CBR;
    cfg.rc_resize_allowed   = 0;
    cfg.rc_min_quantizer    = 2;
    cfg.rc_max_quantizer    = 56;
    cfg.rc_undershoot_pct   = 100;
    cfg.rc_overshoot_pct    = 15;
    cfg.rc_buf_initial_sz   = 500;
    cfg.rc_buf_optimal_sz   = 600;
    cfg.rc_buf_sz           = 1000;

    
    cfg.g_error_resilient = 1;
    cfg.g_lag_in_frames   = 0;
    cfg.kf_mode           = VPX_KF_DISABLED;

    
    cfg.kf_min_dist = cfg.kf_max_dist = 3000;

    
    cfg.rc_target_bitrate = cfg.ts_target_bitrate[0];

    
    switch (layering_mode)
    {
    case 0:
    {
        
       int ids[1] = {0};
       cfg.ts_number_layers     = 1;
       cfg.ts_periodicity       = 1;
       cfg.ts_rate_decimator[0] = 1;
       memcpy(cfg.ts_layer_id, ids, sizeof(ids));

       flag_periodicity = cfg.ts_periodicity;

       
       layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                        VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
       break;
    }
    case 1:
    {
        
        int ids[2] = {0,1};
        cfg.ts_number_layers     = 2;
        cfg.ts_periodicity       = 2;
        cfg.ts_rate_decimator[0] = 2;
        cfg.ts_rate_decimator[1] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = cfg.ts_periodicity;
#if 1
        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF;
        layer_flags[1] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST |
                         VP8_EFLAG_NO_REF_ARF;
#else
        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF;
        layer_flags[1] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_LAST |
                         VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_REF_LAST;
#endif
        break;
    }

    case 2:
    {
        
        int ids[3] = {0,1,1};
        cfg.ts_number_layers     = 2;
        cfg.ts_periodicity       = 3;
        cfg.ts_rate_decimator[0] = 3;
        cfg.ts_rate_decimator[1] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = cfg.ts_periodicity;

        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[1] =
        layer_flags[2] = VP8_EFLAG_NO_REF_GF  |
                         VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_ARF |
                                                VP8_EFLAG_NO_UPD_LAST;
        break;
    }

    case 3:
    {
        
        int ids[6] = {0,2,2,1,2,2};
        cfg.ts_number_layers     = 3;
        cfg.ts_periodicity       = 6;
        cfg.ts_rate_decimator[0] = 6;
        cfg.ts_rate_decimator[1] = 3;
        cfg.ts_rate_decimator[2] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = cfg.ts_periodicity;

        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[3] = VP8_EFLAG_NO_REF_ARF | VP8_EFLAG_NO_UPD_ARF |
                                                VP8_EFLAG_NO_UPD_LAST;
        layer_flags[1] =
        layer_flags[2] =
        layer_flags[4] =
        layer_flags[5] = VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_LAST;
        break;
    }

    case 4:
    {
        
        int ids[4] = {0,2,1,2};
        cfg.ts_number_layers     = 3;
        cfg.ts_periodicity       = 4;
        cfg.ts_rate_decimator[0] = 4;
        cfg.ts_rate_decimator[1] = 2;
        cfg.ts_rate_decimator[2] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = cfg.ts_periodicity;

        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[2] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_UPD_LAST;
        layer_flags[1] =
        layer_flags[3] = VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF |
                         VP8_EFLAG_NO_UPD_ARF;
        break;
    }

    case 5:
    {
        
        int ids[4] = {0,2,1,2};
        cfg.ts_number_layers     = 3;
        cfg.ts_periodicity       = 4;
        cfg.ts_rate_decimator[0] = 4;
        cfg.ts_rate_decimator[1] = 2;
        cfg.ts_rate_decimator[2] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = cfg.ts_periodicity;

        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[2] = VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[1] =
        layer_flags[3] = VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF |
                         VP8_EFLAG_NO_UPD_ARF;
        break;
    }

    case 6:
    {
        
        int ids[4] = {0,2,1,2};
        cfg.ts_number_layers     = 3;
        cfg.ts_periodicity       = 4;
        cfg.ts_rate_decimator[0] = 4;
        cfg.ts_rate_decimator[1] = 2;
        cfg.ts_rate_decimator[2] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = cfg.ts_periodicity;

        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[2] = VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[1] =
        layer_flags[3] = VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF;
        break;
    }

    case 7:
    {
        

        
        int ids[16] = {0,4,3,4,2,4,3,4,1,4,3,4,2,4,3,4};
        cfg.ts_number_layers     = 5;
        cfg.ts_periodicity       = 16;
        cfg.ts_rate_decimator[0] = 16;
        cfg.ts_rate_decimator[1] = 8;
        cfg.ts_rate_decimator[2] = 4;
        cfg.ts_rate_decimator[3] = 2;
        cfg.ts_rate_decimator[4] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = cfg.ts_periodicity;

        layer_flags[0]  = VPX_EFLAG_FORCE_KF;
        layer_flags[1]  =
        layer_flags[3]  =
        layer_flags[5]  =
        layer_flags[7]  =
        layer_flags[9]  =
        layer_flags[11] =
        layer_flags[13] =
        layer_flags[15] = VP8_EFLAG_NO_UPD_LAST |
                          VP8_EFLAG_NO_UPD_GF   |
                          VP8_EFLAG_NO_UPD_ARF;
        layer_flags[2]  =
        layer_flags[6]  =
        layer_flags[10] =
        layer_flags[14] = VP8_EFLAG_NO_UPD_ARF | VP8_EFLAG_NO_UPD_GF;
        layer_flags[4]  =
        layer_flags[12] = VP8_EFLAG_NO_REF_LAST |
                          VP8_EFLAG_NO_UPD_ARF;
        layer_flags[8]  = VP8_EFLAG_NO_REF_LAST | VP8_EFLAG_NO_REF_GF;
        break;
    }

    case 8:
    {
        
        int ids[2] = {0,1};
        cfg.ts_number_layers     = 2;
        cfg.ts_periodicity       = 2;
        cfg.ts_rate_decimator[0] = 2;
        cfg.ts_rate_decimator[1] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = 8;

        
        
        

        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_REF_GF |
                         VP8_EFLAG_NO_UPD_ARF;

        
        layer_flags[1] = VP8_EFLAG_NO_REF_GF |
                         VP8_EFLAG_NO_UPD_LAST |
                         VP8_EFLAG_NO_UPD_ARF;

        
        layer_flags[2] = VP8_EFLAG_NO_REF_GF  |
                         VP8_EFLAG_NO_UPD_GF  |
                         VP8_EFLAG_NO_UPD_ARF;

        
        layer_flags[3] = VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_UPD_LAST |
                         VP8_EFLAG_NO_UPD_ENTROPY;

        
        layer_flags[4] = layer_flags[2];

        
        layer_flags[5] = layer_flags[3];

        
        layer_flags[6] = layer_flags[4];

        
        layer_flags[7] = layer_flags[5];
        break;
    }

    case 9:
    {
        
        

        int ids[4] = {0,2,1,2};
        cfg.ts_number_layers     = 3;
        cfg.ts_periodicity       = 4;
        cfg.ts_rate_decimator[0] = 4;
        cfg.ts_rate_decimator[1] = 2;
        cfg.ts_rate_decimator[2] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = 8;

        
        layer_flags[0] = VPX_EFLAG_FORCE_KF  |
                         VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[1] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF;
        layer_flags[2] = VP8_EFLAG_NO_REF_GF   | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[3] =
        layer_flags[5] = VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF;
        layer_flags[4] = VP8_EFLAG_NO_REF_GF | VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_GF | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[6] = VP8_EFLAG_NO_REF_ARF |
                         VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_ARF;
        layer_flags[7] = VP8_EFLAG_NO_UPD_LAST | VP8_EFLAG_NO_UPD_GF |
                         VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_UPD_ENTROPY;
        break;
    }
    case 10:
    {
        
        
        

        int ids[4] = {0,2,1,2};
        cfg.ts_number_layers     = 3;
        cfg.ts_periodicity       = 4;
        cfg.ts_rate_decimator[0] = 4;
        cfg.ts_rate_decimator[1] = 2;
        cfg.ts_rate_decimator[2] = 1;
        memcpy(cfg.ts_layer_id, ids, sizeof(ids));

        flag_periodicity = 8;

        

        
        layer_flags[0] =  VPX_EFLAG_FORCE_KF  |
                          VP8_EFLAG_NO_UPD_ARF |
                          VP8_EFLAG_NO_REF_GF;

        
        layer_flags[1] = VP8_EFLAG_NO_REF_GF |
                         VP8_EFLAG_NO_UPD_GF |
                         VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_UPD_LAST |
                         VP8_EFLAG_NO_UPD_ENTROPY;

        
        layer_flags[2] = VP8_EFLAG_NO_REF_GF |
                         VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_UPD_LAST;

        
        layer_flags[3] = VP8_EFLAG_NO_UPD_GF |
                         VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_UPD_LAST |
                         VP8_EFLAG_NO_UPD_ENTROPY;

        
        layer_flags[4] = VP8_EFLAG_NO_UPD_GF |
                         VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_REF_GF;

        
        layer_flags[5] = layer_flags[3];

        
        layer_flags[6] = VP8_EFLAG_NO_UPD_ARF |
                         VP8_EFLAG_NO_UPD_LAST;

        
        layer_flags[7] = layer_flags[3];
        break;
    }
    case 11:
    default:
    {
       
       

       int ids[4] = {0,2,1,2};
       cfg.ts_number_layers     = 3;
       cfg.ts_periodicity       = 4;
       cfg.ts_rate_decimator[0] = 4;
       cfg.ts_rate_decimator[1] = 2;
       cfg.ts_rate_decimator[2] = 1;
       memcpy(cfg.ts_layer_id, ids, sizeof(ids));

       flag_periodicity = 8;

       

       
       layer_flags[0] = VP8_EFLAG_NO_UPD_GF |
                        VP8_EFLAG_NO_UPD_ARF |
                        VP8_EFLAG_NO_REF_GF;
       layer_flags[4] = layer_flags[0];

       
       layer_flags[2] = VP8_EFLAG_NO_UPD_ARF |
                        VP8_EFLAG_NO_UPD_LAST;
       layer_flags[6] = layer_flags[2];

       
       layer_flags[1] = VP8_EFLAG_NO_UPD_GF |
                        VP8_EFLAG_NO_UPD_ARF |
                        VP8_EFLAG_NO_UPD_LAST |
                        VP8_EFLAG_NO_UPD_ENTROPY;
       layer_flags[3] = layer_flags[1];
       layer_flags[5] = layer_flags[1];
       layer_flags[7] = layer_flags[1];
       break;
    }
    }

    
    if(!(infile = fopen(argv[1], "rb")))
        die("Failed to open %s for reading", argv[1]);

    
    for (i=0; i<cfg.ts_number_layers; i++)
    {
        char file_name[512];
        sprintf (file_name, "%s_%d.ivf", argv[2], i);
        if (!(outfile[i] = fopen(file_name, "wb")))
            die("Failed to open %s for writing", file_name);
        write_ivf_file_header(outfile[i], &cfg, 0);
    }

    
    if (vpx_codec_enc_init (&codec, interface, &cfg, 0))
        die_codec (&codec, "Failed to initialize encoder");

    
    vpx_codec_control (&codec, VP8E_SET_CPUUSED,                -6);
    vpx_codec_control (&codec, VP8E_SET_STATIC_THRESHOLD,      1);
    vpx_codec_control (&codec, VP8E_SET_NOISE_SENSITIVITY,       1);
    vpx_codec_control(&codec, VP8E_SET_TOKEN_PARTITIONS,       1);

    max_intra_size_pct = (int) (((double)cfg.rc_buf_optimal_sz * 0.5)
                         * ((double) cfg.g_timebase.den / cfg.g_timebase.num)
                         / 10.0);
    

    vpx_codec_control(&codec, VP8E_SET_MAX_INTRA_BITRATE_PCT,
                      max_intra_size_pct);

    frame_avail = 1;
    while (frame_avail || got_data) {
        vpx_codec_iter_t iter = NULL;
        const vpx_codec_cx_pkt_t *pkt;

        flags = layer_flags[frame_cnt % flag_periodicity];

        frame_avail = read_frame(infile, &raw);
        if (vpx_codec_encode(&codec, frame_avail? &raw : NULL, pts,
                            1, flags, VPX_DL_REALTIME))
            die_codec(&codec, "Failed to encode frame");

        
        if (layering_mode != 7)
            layer_flags[0] &= ~VPX_EFLAG_FORCE_KF;

        got_data = 0;
        while ( (pkt = vpx_codec_get_cx_data(&codec, &iter)) ) {
            got_data = 1;
            switch (pkt->kind) {
            case VPX_CODEC_CX_FRAME_PKT:
                for (i=cfg.ts_layer_id[frame_cnt % cfg.ts_periodicity];
                                              i<cfg.ts_number_layers; i++)
                {
                    write_ivf_frame_header(outfile[i], pkt);
                    (void) fwrite(pkt->data.frame.buf, 1, pkt->data.frame.sz,
                                  outfile[i]);
                    frames_in_layer[i]++;
                }
                break;
            default:
                break;
            }
        }
        frame_cnt++;
        pts += frame_duration;
    }
    fclose (infile);

    printf ("Processed %d frames.\n",frame_cnt-1);
    if (vpx_codec_destroy(&codec))
            die_codec (&codec, "Failed to destroy codec");

    
    for (i=0; i<cfg.ts_number_layers; i++)
    {
        if (!fseek(outfile[i], 0, SEEK_SET))
            write_ivf_file_header (outfile[i], &cfg, frames_in_layer[i]);
        fclose (outfile[i]);
    }

    return EXIT_SUCCESS;
}
