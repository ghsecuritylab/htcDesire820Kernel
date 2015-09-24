/*
 * Copyright (c) 2010 NVIDIA, Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __NVCTRL_H
#define __NVCTRL_H

#include <stdint.h>



#define NV_CTRL_TARGET_TYPE_X_SCREEN       0
#define NV_CTRL_TARGET_TYPE_GPU            1
#define NV_CTRL_TARGET_TYPE_FRAMELOCK      2
#define NV_CTRL_TARGET_TYPE_VCSC           3 
#define NV_CTRL_TARGET_TYPE_GVI            4
#define NV_CTRL_TARGET_TYPE_COOLER         5 
#define NV_CTRL_TARGET_TYPE_THERMAL_SENSOR 6
#define NV_CTRL_TARGET_TYPE_3D_VISION_PRO_TRANSCEIVER 7
#define NV_CTRL_TARGET_TYPE_DISPLAY        8








#define NV_CTRL_FLATPANEL_SCALING                               2  
#define NV_CTRL_FLATPANEL_SCALING_DEFAULT                       0
#define NV_CTRL_FLATPANEL_SCALING_NATIVE                        1
#define NV_CTRL_FLATPANEL_SCALING_SCALED                        2
#define NV_CTRL_FLATPANEL_SCALING_CENTERED                      3
#define NV_CTRL_FLATPANEL_SCALING_ASPECT_SCALED                 4



#define NV_CTRL_FLATPANEL_DITHERING                             3  
#define NV_CTRL_FLATPANEL_DITHERING_DEFAULT                     0
#define NV_CTRL_FLATPANEL_DITHERING_ENABLED                     1
#define NV_CTRL_FLATPANEL_DITHERING_DISABLED                    2


#define NV_CTRL_DITHERING                                       3  
#define NV_CTRL_DITHERING_AUTO                                  0
#define NV_CTRL_DITHERING_ENABLED                               1
#define NV_CTRL_DITHERING_DISABLED                              2



#define NV_CTRL_DIGITAL_VIBRANCE                                4  



#define NV_CTRL_BUS_TYPE                                        5  
#define NV_CTRL_BUS_TYPE_AGP                                    0
#define NV_CTRL_BUS_TYPE_PCI                                    1
#define NV_CTRL_BUS_TYPE_PCI_EXPRESS                            2
#define NV_CTRL_BUS_TYPE_INTEGRATED                             3



#define NV_CTRL_VIDEO_RAM                                       6  



#define NV_CTRL_IRQ                                             7  



#define NV_CTRL_OPERATING_SYSTEM                                8  
#define NV_CTRL_OPERATING_SYSTEM_LINUX                          0
#define NV_CTRL_OPERATING_SYSTEM_FREEBSD                        1
#define NV_CTRL_OPERATING_SYSTEM_SUNOS                          2



#define NV_CTRL_SYNC_TO_VBLANK                                  9  
#define NV_CTRL_SYNC_TO_VBLANK_OFF                              0
#define NV_CTRL_SYNC_TO_VBLANK_ON                               1



#define NV_CTRL_LOG_ANISO                                       10 



#define NV_CTRL_FSAA_MODE                                       11 
#define NV_CTRL_FSAA_MODE_NONE                                  0
#define NV_CTRL_FSAA_MODE_2x                                    1
#define NV_CTRL_FSAA_MODE_2x_5t                                 2
#define NV_CTRL_FSAA_MODE_15x15                                 3
#define NV_CTRL_FSAA_MODE_2x2                                   4
#define NV_CTRL_FSAA_MODE_4x                                    5
#define NV_CTRL_FSAA_MODE_4x_9t                                 6
#define NV_CTRL_FSAA_MODE_8x                                    7
#define NV_CTRL_FSAA_MODE_16x                                   8
#define NV_CTRL_FSAA_MODE_8xS                                   9
#define NV_CTRL_FSAA_MODE_8xQ                                  10
#define NV_CTRL_FSAA_MODE_16xS                                 11
#define NV_CTRL_FSAA_MODE_16xQ                                 12
#define NV_CTRL_FSAA_MODE_32xS                                 13
#define NV_CTRL_FSAA_MODE_32x                                  14
#define NV_CTRL_FSAA_MODE_64xS                                 15
#define NV_CTRL_FSAA_MODE_MAX NV_CTRL_FSAA_MODE_64xS



#define NV_CTRL_TEXTURE_SHARPEN                                 12 
#define NV_CTRL_TEXTURE_SHARPEN_OFF                             0
#define NV_CTRL_TEXTURE_SHARPEN_ON                              1



#define NV_CTRL_UBB                                             13 
#define NV_CTRL_UBB_OFF                                         0
#define NV_CTRL_UBB_ON                                          1



#define NV_CTRL_OVERLAY                                         14 
#define NV_CTRL_OVERLAY_OFF                                     0
#define NV_CTRL_OVERLAY_ON                                      1



#define NV_CTRL_STEREO                                          16 
#define NV_CTRL_STEREO_OFF                                      0
#define NV_CTRL_STEREO_DDC                                      1
#define NV_CTRL_STEREO_BLUELINE                                 2
#define NV_CTRL_STEREO_DIN                                      3
#define NV_CTRL_STEREO_PASSIVE_EYE_PER_DPY                      4
#define NV_CTRL_STEREO_VERTICAL_INTERLACED                      5
#define NV_CTRL_STEREO_COLOR_INTERLACED                         6
#define NV_CTRL_STEREO_HORIZONTAL_INTERLACED                    7
#define NV_CTRL_STEREO_CHECKERBOARD_PATTERN                     8
#define NV_CTRL_STEREO_INVERSE_CHECKERBOARD_PATTERN             9
#define NV_CTRL_STEREO_3D_VISION                                10
#define NV_CTRL_STEREO_3D_VISION_PRO                            11


#define NV_CTRL_EMULATE                                         17 
#define NV_CTRL_EMULATE_NONE                                    0



#define NV_CTRL_TWINVIEW                                        18 
#define NV_CTRL_TWINVIEW_NOT_ENABLED                            0
#define NV_CTRL_TWINVIEW_ENABLED                                1



#define NV_CTRL_CONNECTED_DISPLAYS                              19 



#define NV_CTRL_ENABLED_DISPLAYS                                20 




#define NV_CTRL_FRAMELOCK                                       21 
#define NV_CTRL_FRAMELOCK_NOT_SUPPORTED                         0
#define NV_CTRL_FRAMELOCK_SUPPORTED                             1



#define NV_CTRL_FRAMELOCK_MASTER                                22 

#define NV_CTRL_FRAMELOCK_MASTER_FALSE                          0
#define NV_CTRL_FRAMELOCK_MASTER_TRUE                           1



#define NV_CTRL_FRAMELOCK_POLARITY                              23 
#define NV_CTRL_FRAMELOCK_POLARITY_RISING_EDGE                  0x1
#define NV_CTRL_FRAMELOCK_POLARITY_FALLING_EDGE                 0x2
#define NV_CTRL_FRAMELOCK_POLARITY_BOTH_EDGES                   0x3



#define NV_CTRL_FRAMELOCK_SYNC_DELAY                            24 
#define NV_CTRL_FRAMELOCK_SYNC_DELAY_MAX                        2047 
#define NV_CTRL_FRAMELOCK_SYNC_DELAY_FACTOR                     7.81 



#define NV_CTRL_FRAMELOCK_SYNC_INTERVAL                         25 



#define NV_CTRL_FRAMELOCK_PORT0_STATUS                          26 
#define NV_CTRL_FRAMELOCK_PORT0_STATUS_INPUT                    0
#define NV_CTRL_FRAMELOCK_PORT0_STATUS_OUTPUT                   1



#define NV_CTRL_FRAMELOCK_PORT1_STATUS                          27 
#define NV_CTRL_FRAMELOCK_PORT1_STATUS_INPUT                    0
#define NV_CTRL_FRAMELOCK_PORT1_STATUS_OUTPUT                   1



#define NV_CTRL_FRAMELOCK_HOUSE_STATUS                          28 
#define NV_CTRL_FRAMELOCK_HOUSE_STATUS_NOT_DETECTED             0
#define NV_CTRL_FRAMELOCK_HOUSE_STATUS_DETECTED                 1



#define NV_CTRL_FRAMELOCK_SYNC                                  29 
#define NV_CTRL_FRAMELOCK_SYNC_DISABLE                          0
#define NV_CTRL_FRAMELOCK_SYNC_ENABLE                           1



#define NV_CTRL_FRAMELOCK_SYNC_READY                            30 
#define NV_CTRL_FRAMELOCK_SYNC_READY_FALSE                      0
#define NV_CTRL_FRAMELOCK_SYNC_READY_TRUE                       1



#define NV_CTRL_FRAMELOCK_STEREO_SYNC                           31 
#define NV_CTRL_FRAMELOCK_STEREO_SYNC_FALSE                     0
#define NV_CTRL_FRAMELOCK_STEREO_SYNC_TRUE                      1



#define NV_CTRL_FRAMELOCK_TEST_SIGNAL                           32 
#define NV_CTRL_FRAMELOCK_TEST_SIGNAL_DISABLE                   0
#define NV_CTRL_FRAMELOCK_TEST_SIGNAL_ENABLE                    1



#define NV_CTRL_FRAMELOCK_ETHERNET_DETECTED                     33 
#define NV_CTRL_FRAMELOCK_ETHERNET_DETECTED_NONE                0
#define NV_CTRL_FRAMELOCK_ETHERNET_DETECTED_PORT0               0x1
#define NV_CTRL_FRAMELOCK_ETHERNET_DETECTED_PORT1               0x2



#define NV_CTRL_FRAMELOCK_VIDEO_MODE                            34 
#define NV_CTRL_FRAMELOCK_VIDEO_MODE_NONE                       0
#define NV_CTRL_FRAMELOCK_VIDEO_MODE_TTL                        1
#define NV_CTRL_FRAMELOCK_VIDEO_MODE_NTSCPALSECAM               2
#define NV_CTRL_FRAMELOCK_VIDEO_MODE_HDTV                       3


#define NV_CTRL_FRAMELOCK_VIDEO_MODE_COMPOSITE_AUTO             0
#define NV_CTRL_FRAMELOCK_VIDEO_MODE_TTL                        1
#define NV_CTRL_FRAMELOCK_VIDEO_MODE_COMPOSITE_BI_LEVEL         2
#define NV_CTRL_FRAMELOCK_VIDEO_MODE_COMPOSITE_TRI_LEVEL        3



#define NV_CTRL_FRAMELOCK_SYNC_RATE                             35 





#define NV_CTRL_FORCE_GENERIC_CPU                               37 
#define NV_CTRL_FORCE_GENERIC_CPU_DISABLE                        0
#define NV_CTRL_FORCE_GENERIC_CPU_ENABLE                         1



#define NV_CTRL_OPENGL_AA_LINE_GAMMA                            38 
#define NV_CTRL_OPENGL_AA_LINE_GAMMA_DISABLE                     0
#define NV_CTRL_OPENGL_AA_LINE_GAMMA_ENABLE                      1



#define NV_CTRL_FRAMELOCK_TIMING                                39 
#define NV_CTRL_FRAMELOCK_TIMING_FALSE                           0
#define NV_CTRL_FRAMELOCK_TIMING_TRUE                            1


#define NV_CTRL_FLIPPING_ALLOWED                                40 
#define NV_CTRL_FLIPPING_ALLOWED_FALSE                           0
#define NV_CTRL_FLIPPING_ALLOWED_TRUE                            1


#define NV_CTRL_ARCHITECTURE                                    41  
#define NV_CTRL_ARCHITECTURE_X86                                 0
#define NV_CTRL_ARCHITECTURE_X86_64                              1
#define NV_CTRL_ARCHITECTURE_IA64                                2



#define NV_CTRL_TEXTURE_CLAMPING                                42  
#define NV_CTRL_TEXTURE_CLAMPING_EDGE                            0
#define NV_CTRL_TEXTURE_CLAMPING_SPEC                            1



#define NV_CTRL_CURSOR_SHADOW                                   43  
#define NV_CTRL_CURSOR_SHADOW_DISABLE                            0
#define NV_CTRL_CURSOR_SHADOW_ENABLE                             1

#define NV_CTRL_CURSOR_SHADOW_ALPHA                             44  
#define NV_CTRL_CURSOR_SHADOW_RED                               45  
#define NV_CTRL_CURSOR_SHADOW_GREEN                             46  
#define NV_CTRL_CURSOR_SHADOW_BLUE                              47  

#define NV_CTRL_CURSOR_SHADOW_X_OFFSET                          48  
#define NV_CTRL_CURSOR_SHADOW_Y_OFFSET                          49  




#define NV_CTRL_FSAA_APPLICATION_CONTROLLED                     50  
#define NV_CTRL_FSAA_APPLICATION_CONTROLLED_ENABLED              1
#define NV_CTRL_FSAA_APPLICATION_CONTROLLED_DISABLED             0



#define NV_CTRL_LOG_ANISO_APPLICATION_CONTROLLED                51  
#define NV_CTRL_LOG_ANISO_APPLICATION_CONTROLLED_ENABLED         1
#define NV_CTRL_LOG_ANISO_APPLICATION_CONTROLLED_DISABLED        0



#define NV_CTRL_IMAGE_SHARPENING                                52  



#define NV_CTRL_TV_OVERSCAN                                     53  



#define NV_CTRL_TV_FLICKER_FILTER                               54  



#define NV_CTRL_TV_BRIGHTNESS                                   55  



#define NV_CTRL_TV_HUE                                          56  



#define NV_CTRL_TV_CONTRAST                                     57  



#define NV_CTRL_TV_SATURATION                                   58  



#define NV_CTRL_TV_RESET_SETTINGS                               59  



#define NV_CTRL_GPU_CORE_TEMPERATURE                            60  



#define NV_CTRL_GPU_CORE_THRESHOLD                              61  
#define NV_CTRL_GPU_DEFAULT_CORE_THRESHOLD                      62  
#define NV_CTRL_GPU_MAX_CORE_THRESHOLD                          63  



#define NV_CTRL_AMBIENT_TEMPERATURE                             64  


#define NV_CTRL_PBUFFER_SCANOUT_SUPPORTED                       65  
#define NV_CTRL_PBUFFER_SCANOUT_FALSE                           0
#define NV_CTRL_PBUFFER_SCANOUT_TRUE                            1

#define NV_CTRL_PBUFFER_SCANOUT_XID                             66  




#define NV_CTRL_GVO_SUPPORTED                                   67  
#define NV_CTRL_GVO_SUPPORTED_FALSE                             0
#define NV_CTRL_GVO_SUPPORTED_TRUE                              1



#define NV_CTRL_GVO_SYNC_MODE                                   68  
#define NV_CTRL_GVO_SYNC_MODE_FREE_RUNNING                      0
#define NV_CTRL_GVO_SYNC_MODE_GENLOCK                           1
#define NV_CTRL_GVO_SYNC_MODE_FRAMELOCK                         2



#define NV_CTRL_GVO_SYNC_SOURCE                                 69  
#define NV_CTRL_GVO_SYNC_SOURCE_COMPOSITE                       0
#define NV_CTRL_GVO_SYNC_SOURCE_SDI                             1



#define NV_CTRL_GVIO_REQUESTED_VIDEO_FORMAT                     70  

#define NV_CTRL_GVIO_VIDEO_FORMAT_NONE                          0
#define NV_CTRL_GVIO_VIDEO_FORMAT_487I_59_94_SMPTE259_NTSC      1
#define NV_CTRL_GVIO_VIDEO_FORMAT_576I_50_00_SMPTE259_PAL       2
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_59_94_SMPTE296           3
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_60_00_SMPTE296           4
#define NV_CTRL_GVIO_VIDEO_FORMAT_1035I_59_94_SMPTE260          5
#define NV_CTRL_GVIO_VIDEO_FORMAT_1035I_60_00_SMPTE260          6
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_50_00_SMPTE295          7
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_50_00_SMPTE274          8
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_59_94_SMPTE274          9
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_60_00_SMPTE274          10
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_23_976_SMPTE274         11
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_24_00_SMPTE274          12
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_25_00_SMPTE274          13
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_29_97_SMPTE274          14
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_30_00_SMPTE274          15
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_50_00_SMPTE296           16
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_48_00_SMPTE274          17
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_47_96_SMPTE274          18
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_30_00_SMPTE296           19 
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_29_97_SMPTE296           20  
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_25_00_SMPTE296           21 
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_24_00_SMPTE296           22 
#define NV_CTRL_GVIO_VIDEO_FORMAT_720P_23_98_SMPTE296           23  
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080PSF_25_00_SMPTE274        24
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080PSF_29_97_SMPTE274        25
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080PSF_30_00_SMPTE274        26
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080PSF_24_00_SMPTE274        27
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080PSF_23_98_SMPTE274        28
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_30_00_SMPTE372          29
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_29_97_SMPTE372          30
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_60_00_SMPTE372          31
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_59_94_SMPTE372          32
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_25_00_SMPTE372          33
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_50_00_SMPTE372          34
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_24_00_SMPTE372          35
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_23_98_SMPTE372          36
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_48_00_SMPTE372          37
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_47_96_SMPTE372          38
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_50_00_3G_LEVEL_A_SMPTE274  39
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_59_94_3G_LEVEL_A_SMPTE274  40
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_60_00_3G_LEVEL_A_SMPTE274  41
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_60_00_3G_LEVEL_B_SMPTE274  42
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_60_00_3G_LEVEL_B_SMPTE274  43
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_60_00_3G_LEVEL_B_SMPTE372  44
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_50_00_3G_LEVEL_B_SMPTE274  45
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_50_00_3G_LEVEL_B_SMPTE274  46
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_50_00_3G_LEVEL_B_SMPTE372  47
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_30_00_3G_LEVEL_B_SMPTE274  48
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_30_00_3G_LEVEL_B_SMPTE372  49
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_25_00_3G_LEVEL_B_SMPTE274  50
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_25_00_3G_LEVEL_B_SMPTE372  51
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_24_00_3G_LEVEL_B_SMPTE274  52
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_24_00_3G_LEVEL_B_SMPTE372  53
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_48_00_3G_LEVEL_B_SMPTE274  54
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_48_00_3G_LEVEL_B_SMPTE372  55
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_59_94_3G_LEVEL_B_SMPTE274  56
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_59_94_3G_LEVEL_B_SMPTE274  57
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_59_94_3G_LEVEL_B_SMPTE372  58
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_29_97_3G_LEVEL_B_SMPTE274  59
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_29_97_3G_LEVEL_B_SMPTE372  60
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080P_23_98_3G_LEVEL_B_SMPTE274  61
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048P_23_98_3G_LEVEL_B_SMPTE372  62
#define NV_CTRL_GVIO_VIDEO_FORMAT_1080I_47_96_3G_LEVEL_B_SMPTE274  63
#define NV_CTRL_GVIO_VIDEO_FORMAT_2048I_47_96_3G_LEVEL_B_SMPTE372  64


#define NV_CTRL_GVO_OUTPUT_VIDEO_FORMAT                         70  

#define NV_CTRL_GVO_VIDEO_FORMAT_NONE                           0
#define NV_CTRL_GVO_VIDEO_FORMAT_487I_59_94_SMPTE259_NTSC       1
#define NV_CTRL_GVO_VIDEO_FORMAT_576I_50_00_SMPTE259_PAL        2
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_59_94_SMPTE296            3
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_60_00_SMPTE296            4
#define NV_CTRL_GVO_VIDEO_FORMAT_1035I_59_94_SMPTE260           5
#define NV_CTRL_GVO_VIDEO_FORMAT_1035I_60_00_SMPTE260           6
#define NV_CTRL_GVO_VIDEO_FORMAT_1080I_50_00_SMPTE295           7
#define NV_CTRL_GVO_VIDEO_FORMAT_1080I_50_00_SMPTE274           8
#define NV_CTRL_GVO_VIDEO_FORMAT_1080I_59_94_SMPTE274           9
#define NV_CTRL_GVO_VIDEO_FORMAT_1080I_60_00_SMPTE274           10
#define NV_CTRL_GVO_VIDEO_FORMAT_1080P_23_976_SMPTE274          11
#define NV_CTRL_GVO_VIDEO_FORMAT_1080P_24_00_SMPTE274           12
#define NV_CTRL_GVO_VIDEO_FORMAT_1080P_25_00_SMPTE274           13
#define NV_CTRL_GVO_VIDEO_FORMAT_1080P_29_97_SMPTE274           14
#define NV_CTRL_GVO_VIDEO_FORMAT_1080P_30_00_SMPTE274           15
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_50_00_SMPTE296            16
#define NV_CTRL_GVO_VIDEO_FORMAT_1080I_48_00_SMPTE274           17
#define NV_CTRL_GVO_VIDEO_FORMAT_1080I_47_96_SMPTE274           18
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_30_00_SMPTE296            19 
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_29_97_SMPTE296            20  
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_25_00_SMPTE296            21 
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_24_00_SMPTE296            22 
#define NV_CTRL_GVO_VIDEO_FORMAT_720P_23_98_SMPTE296            23  
#define NV_CTRL_GVO_VIDEO_FORMAT_1080PSF_25_00_SMPTE274         24
#define NV_CTRL_GVO_VIDEO_FORMAT_1080PSF_29_97_SMPTE274         25
#define NV_CTRL_GVO_VIDEO_FORMAT_1080PSF_30_00_SMPTE274         26
#define NV_CTRL_GVO_VIDEO_FORMAT_1080PSF_24_00_SMPTE274         27
#define NV_CTRL_GVO_VIDEO_FORMAT_1080PSF_23_98_SMPTE274         28
#define NV_CTRL_GVO_VIDEO_FORMAT_2048P_30_00_SMPTE372           29
#define NV_CTRL_GVO_VIDEO_FORMAT_2048P_29_97_SMPTE372           30
#define NV_CTRL_GVO_VIDEO_FORMAT_2048I_60_00_SMPTE372           31
#define NV_CTRL_GVO_VIDEO_FORMAT_2048I_59_94_SMPTE372           32
#define NV_CTRL_GVO_VIDEO_FORMAT_2048P_25_00_SMPTE372           33
#define NV_CTRL_GVO_VIDEO_FORMAT_2048I_50_00_SMPTE372           34
#define NV_CTRL_GVO_VIDEO_FORMAT_2048P_24_00_SMPTE372           35
#define NV_CTRL_GVO_VIDEO_FORMAT_2048P_23_98_SMPTE372           36
#define NV_CTRL_GVO_VIDEO_FORMAT_2048I_48_00_SMPTE372           37
#define NV_CTRL_GVO_VIDEO_FORMAT_2048I_47_96_SMPTE372           38


#define NV_CTRL_GVIO_DETECTED_VIDEO_FORMAT                      71  

#define NV_CTRL_GVO_INPUT_VIDEO_FORMAT                          71  


#define NV_CTRL_GVO_DATA_FORMAT                                 72  
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8_TO_YCRCB444              0
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8A8_TO_YCRCBA4444          1
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8Z10_TO_YCRCBZ4444         2
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8_TO_YCRCB422              3
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8A8_TO_YCRCBA4224          4
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8Z10_TO_YCRCBZ4224         5
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8_TO_RGB444                6 
#define NV_CTRL_GVO_DATA_FORMAT_X8X8X8_444_PASSTHRU             6
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8A8_TO_RGBA4444            7 
#define NV_CTRL_GVO_DATA_FORMAT_X8X8X8A8_4444_PASSTHRU          7
#define NV_CTRL_GVO_DATA_FORMAT_R8G8B8Z10_TO_RGBZ4444           8 
#define NV_CTRL_GVO_DATA_FORMAT_X8X8X8Z8_4444_PASSTHRU          8
#define NV_CTRL_GVO_DATA_FORMAT_Y10CR10CB10_TO_YCRCB444         9 
#define NV_CTRL_GVO_DATA_FORMAT_X10X10X10_444_PASSTHRU          9
#define NV_CTRL_GVO_DATA_FORMAT_Y10CR8CB8_TO_YCRCB444           10 
#define NV_CTRL_GVO_DATA_FORMAT_X10X8X8_444_PASSTHRU            10
#define NV_CTRL_GVO_DATA_FORMAT_Y10CR8CB8A10_TO_YCRCBA4444      11 
#define NV_CTRL_GVO_DATA_FORMAT_X10X8X8A10_4444_PASSTHRU        11
#define NV_CTRL_GVO_DATA_FORMAT_Y10CR8CB8Z10_TO_YCRCBZ4444      12 
#define NV_CTRL_GVO_DATA_FORMAT_X10X8X8Z10_4444_PASSTHRU        12
#define NV_CTRL_GVO_DATA_FORMAT_DUAL_R8G8B8_TO_DUAL_YCRCB422    13
#define NV_CTRL_GVO_DATA_FORMAT_DUAL_Y8CR8CB8_TO_DUAL_YCRCB422  14 
#define NV_CTRL_GVO_DATA_FORMAT_DUAL_X8X8X8_TO_DUAL_422_PASSTHRU 14
#define NV_CTRL_GVO_DATA_FORMAT_R10G10B10_TO_YCRCB422           15
#define NV_CTRL_GVO_DATA_FORMAT_R10G10B10_TO_YCRCB444           16
#define NV_CTRL_GVO_DATA_FORMAT_Y12CR12CB12_TO_YCRCB444         17 
#define NV_CTRL_GVO_DATA_FORMAT_X12X12X12_444_PASSTHRU          17
#define NV_CTRL_GVO_DATA_FORMAT_R12G12B12_TO_YCRCB444           18
#define NV_CTRL_GVO_DATA_FORMAT_X8X8X8_422_PASSTHRU             19
#define NV_CTRL_GVO_DATA_FORMAT_X8X8X8A8_4224_PASSTHRU          20
#define NV_CTRL_GVO_DATA_FORMAT_X8X8X8Z8_4224_PASSTHRU          21
#define NV_CTRL_GVO_DATA_FORMAT_X10X10X10_422_PASSTHRU          22
#define NV_CTRL_GVO_DATA_FORMAT_X10X8X8_422_PASSTHRU            23
#define NV_CTRL_GVO_DATA_FORMAT_X10X8X8A10_4224_PASSTHRU        24
#define NV_CTRL_GVO_DATA_FORMAT_X10X8X8Z10_4224_PASSTHRU        25
#define NV_CTRL_GVO_DATA_FORMAT_X12X12X12_422_PASSTHRU          26
#define NV_CTRL_GVO_DATA_FORMAT_R12G12B12_TO_YCRCB422           27


#define NV_CTRL_GVO_DISPLAY_X_SCREEN                            73  
#define NV_CTRL_GVO_DISPLAY_X_SCREEN_ENABLE                     1
#define NV_CTRL_GVO_DISPLAY_X_SCREEN_DISABLE                    0



#define NV_CTRL_GVO_COMPOSITE_SYNC_INPUT_DETECTED               74  
#define NV_CTRL_GVO_COMPOSITE_SYNC_INPUT_DETECTED_FALSE         0
#define NV_CTRL_GVO_COMPOSITE_SYNC_INPUT_DETECTED_TRUE          1



#define NV_CTRL_GVO_COMPOSITE_SYNC_INPUT_DETECT_MODE            75  
#define NV_CTRL_GVO_COMPOSITE_SYNC_INPUT_DETECT_MODE_AUTO       0
#define NV_CTRL_GVO_COMPOSITE_SYNC_INPUT_DETECT_MODE_BI_LEVEL   1
#define NV_CTRL_GVO_COMPOSITE_SYNC_INPUT_DETECT_MODE_TRI_LEVEL  2



#define NV_CTRL_GVO_SDI_SYNC_INPUT_DETECTED                     76  
#define NV_CTRL_GVO_SDI_SYNC_INPUT_DETECTED_NONE                0
#define NV_CTRL_GVO_SDI_SYNC_INPUT_DETECTED_HD                  1
#define NV_CTRL_GVO_SDI_SYNC_INPUT_DETECTED_SD                  2



#define NV_CTRL_GVO_VIDEO_OUTPUTS                               77  
#define NV_CTRL_GVO_VIDEO_OUTPUTS_NONE                          0
#define NV_CTRL_GVO_VIDEO_OUTPUTS_VIDEO1                        1
#define NV_CTRL_GVO_VIDEO_OUTPUTS_VIDEO2                        2
#define NV_CTRL_GVO_VIDEO_OUTPUTS_VIDEO_BOTH                    3



#define NV_CTRL_GVO_FIRMWARE_VERSION                            78  



#define NV_CTRL_GVO_SYNC_DELAY_PIXELS                           79  



#define NV_CTRL_GVO_SYNC_DELAY_LINES                            80  


/*
 * NV_CTRL_GVO_INPUT_VIDEO_FORMAT_REACQUIRE - must be set for a period
 * of about 2 seconds for the new InputVideoFormat to be properly
 * locked to.  In nvidia-settings, we do a reacquire whenever genlock
 * or frame lock mode is entered into, when the user clicks the
 * "detect" button.  This value can be written, but always reads back
 * _FALSE.
 */

#define NV_CTRL_GVO_INPUT_VIDEO_FORMAT_REACQUIRE                81  
#define NV_CTRL_GVO_INPUT_VIDEO_FORMAT_REACQUIRE_FALSE          0
#define NV_CTRL_GVO_INPUT_VIDEO_FORMAT_REACQUIRE_TRUE           1



#define NV_CTRL_GVO_GLX_LOCKED                                  82  
#define NV_CTRL_GVO_GLX_LOCKED_FALSE                            0
#define NV_CTRL_GVO_GLX_LOCKED_TRUE                             1



#define NV_CTRL_GVIO_VIDEO_FORMAT_WIDTH                         83  
#define NV_CTRL_GVIO_VIDEO_FORMAT_HEIGHT                        84  
#define NV_CTRL_GVIO_VIDEO_FORMAT_REFRESH_RATE                  85  

#define NV_CTRL_GVO_VIDEO_FORMAT_WIDTH                          83  
#define NV_CTRL_GVO_VIDEO_FORMAT_HEIGHT                         84  
#define NV_CTRL_GVO_VIDEO_FORMAT_REFRESH_RATE                   85  



#define NV_CTRL_GVO_X_SCREEN_PAN_X                              86  
#define NV_CTRL_GVO_X_SCREEN_PAN_Y                              87  



#define NV_CTRL_GPU_OVERCLOCKING_STATE                          88  
#define NV_CTRL_GPU_OVERCLOCKING_STATE_NONE                     0
#define NV_CTRL_GPU_OVERCLOCKING_STATE_MANUAL                   1



#define NV_CTRL_GPU_2D_CLOCK_FREQS                              89  
#define NV_CTRL_GPU_3D_CLOCK_FREQS                              90  



#define NV_CTRL_GPU_DEFAULT_2D_CLOCK_FREQS                      91  
#define NV_CTRL_GPU_DEFAULT_3D_CLOCK_FREQS                      92  



#define NV_CTRL_GPU_CURRENT_CLOCK_FREQS                         93  



#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS                         94  
#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS_INVALID                  0



#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS_DETECTION               95  
#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS_DETECTION_START          0
#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS_DETECTION_CANCEL         1



#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS_DETECTION_STATE         96  
#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS_DETECTION_STATE_IDLE     0
#define NV_CTRL_GPU_OPTIMAL_CLOCK_FREQS_DETECTION_STATE_BUSY     1



#define NV_CTRL_FLATPANEL_CHIP_LOCATION                         215
#define NV_CTRL_FLATPANEL_CHIP_LOCATION_INTERNAL                  0
#define NV_CTRL_FLATPANEL_CHIP_LOCATION_EXTERNAL                  1


#define NV_CTRL_FLATPANEL_LINK                                  216
#define NV_CTRL_FLATPANEL_LINK_SINGLE                             0
#define NV_CTRL_FLATPANEL_LINK_DUAL                               1
#define NV_CTRL_FLATPANEL_LINK_QUAD                               3


#define NV_CTRL_FLATPANEL_SIGNAL                                217
#define NV_CTRL_FLATPANEL_SIGNAL_LVDS                             0
#define NV_CTRL_FLATPANEL_SIGNAL_TMDS                             1
#define NV_CTRL_FLATPANEL_SIGNAL_DISPLAYPORT                      2



#define NV_CTRL_USE_HOUSE_SYNC                                  218
#define NV_CTRL_USE_HOUSE_SYNC_FALSE                            0
#define NV_CTRL_USE_HOUSE_SYNC_TRUE                             1


#define NV_CTRL_EDID_AVAILABLE                                  219 
#define NV_CTRL_EDID_AVAILABLE_FALSE                            0
#define NV_CTRL_EDID_AVAILABLE_TRUE                             1


#define NV_CTRL_FORCE_STEREO                                    220 
#define NV_CTRL_FORCE_STEREO_FALSE                              0
#define NV_CTRL_FORCE_STEREO_TRUE                               1



#define NV_CTRL_IMAGE_SETTINGS                                  221 
#define NV_CTRL_IMAGE_SETTINGS_HIGH_QUALITY                     0
#define NV_CTRL_IMAGE_SETTINGS_QUALITY                          1
#define NV_CTRL_IMAGE_SETTINGS_PERFORMANCE                      2
#define NV_CTRL_IMAGE_SETTINGS_HIGH_PERFORMANCE                 3



#define NV_CTRL_XINERAMA                                        222 
#define NV_CTRL_XINERAMA_OFF                                    0
#define NV_CTRL_XINERAMA_ON                                     1


#define NV_CTRL_XINERAMA_STEREO                                  223 
#define NV_CTRL_XINERAMA_STEREO_FALSE                            0
#define NV_CTRL_XINERAMA_STEREO_TRUE                             1


#define NV_CTRL_BUS_RATE                                        224  

#define NV_CTRL_GPU_PCIE_MAX_LINK_WIDTH  NV_CTRL_BUS_RATE


#define NV_CTRL_SHOW_SLI_HUD         NV_CTRL_SHOW_SLI_VISUAL_INDICATOR
#define NV_CTRL_SHOW_SLI_HUD_FALSE   NV_CTRL_SHOW_SLI_VISUAL_INDICATOR_FALSE
#define NV_CTRL_SHOW_SLI_HUD_TRUE    NV_CTRL_SHOW_SLI_VISUAL_INDICATOR_TRUE


#define NV_CTRL_SHOW_SLI_VISUAL_INDICATOR                       225  
#define NV_CTRL_SHOW_SLI_VISUAL_INDICATOR_FALSE                   0
#define NV_CTRL_SHOW_SLI_VISUAL_INDICATOR_TRUE                    1


#define NV_CTRL_XV_SYNC_TO_DISPLAY                               226  


#define NV_CTRL_GVIO_REQUESTED_VIDEO_FORMAT2                    227  

#define NV_CTRL_GVO_OUTPUT_VIDEO_FORMAT2                         227  



#define NV_CTRL_GVO_OVERRIDE_HW_CSC                              228  
#define NV_CTRL_GVO_OVERRIDE_HW_CSC_FALSE                        0
#define NV_CTRL_GVO_OVERRIDE_HW_CSC_TRUE                         1



#define NV_CTRL_GVO_CAPABILITIES                                 229  
#define NV_CTRL_GVO_CAPABILITIES_APPLY_CSC_IMMEDIATELY           0x00000001
#define NV_CTRL_GVO_CAPABILITIES_APPLY_CSC_TO_X_SCREEN           0x00000002
#define NV_CTRL_GVO_CAPABILITIES_COMPOSITE_TERMINATION           0x00000004
#define NV_CTRL_GVO_CAPABILITIES_SHARED_SYNC_BNC                 0x00000008
#define NV_CTRL_GVO_CAPABILITIES_MULTIRATE_SYNC                  0x00000010
#define NV_CTRL_GVO_CAPABILITIES_ADVANCE_SYNC_SKEW               0x00000020



#define NV_CTRL_GVO_COMPOSITE_TERMINATION                        230  
#define NV_CTRL_GVO_COMPOSITE_TERMINATION_ENABLE                   1
#define NV_CTRL_GVO_COMPOSITE_TERMINATION_DISABLE                  0


 
#define NV_CTRL_ASSOCIATED_DISPLAY_DEVICES                       231 


#define NV_CTRL_FRAMELOCK_SLAVES                                 232 


#define NV_CTRL_FRAMELOCK_MASTERABLE                             233 


#define NV_CTRL_PROBE_DISPLAYS                                   234 



#define NV_CTRL_REFRESH_RATE                                     235 



#define NV_CTRL_GVO_FLIP_QUEUE_SIZE                              236 



#define NV_CTRL_CURRENT_SCANLINE                                 237 



#define NV_CTRL_INITIAL_PIXMAP_PLACEMENT                         238 
#define NV_CTRL_INITIAL_PIXMAP_PLACEMENT_FORCE_SYSMEM            0
#define NV_CTRL_INITIAL_PIXMAP_PLACEMENT_SYSMEM                  1
#define NV_CTRL_INITIAL_PIXMAP_PLACEMENT_VIDMEM                  2
#define NV_CTRL_INITIAL_PIXMAP_PLACEMENT_RESERVED                3
#define NV_CTRL_INITIAL_PIXMAP_PLACEMENT_GPU_SYSMEM              4



#define NV_CTRL_PCI_BUS                                          239 



#define NV_CTRL_PCI_DEVICE                                       240 



#define NV_CTRL_PCI_FUNCTION                                     241 



#define NV_CTRL_FRAMELOCK_FPGA_REVISION                          242 


#define NV_CTRL_MAX_SCREEN_WIDTH                                 243 
#define NV_CTRL_MAX_SCREEN_HEIGHT                                244 



#define NV_CTRL_MAX_DISPLAYS                                     245 



#define NV_CTRL_DYNAMIC_TWINVIEW                                 246 



#define NV_CTRL_MULTIGPU_DISPLAY_OWNER                           247 



#define NV_CTRL_GPU_SCALING                                      248 

#define NV_CTRL_GPU_SCALING_TARGET_INVALID                       0
#define NV_CTRL_GPU_SCALING_TARGET_FLATPANEL_BEST_FIT            1
#define NV_CTRL_GPU_SCALING_TARGET_FLATPANEL_NATIVE              2

#define NV_CTRL_GPU_SCALING_METHOD_INVALID                       0
#define NV_CTRL_GPU_SCALING_METHOD_STRETCHED                     1
#define NV_CTRL_GPU_SCALING_METHOD_CENTERED                      2
#define NV_CTRL_GPU_SCALING_METHOD_ASPECT_SCALED                 3



#define NV_CTRL_FRONTEND_RESOLUTION                              249 



#define NV_CTRL_BACKEND_RESOLUTION                               250 



#define NV_CTRL_FLATPANEL_NATIVE_RESOLUTION                      251 



#define NV_CTRL_FLATPANEL_BEST_FIT_RESOLUTION                    252 



#define NV_CTRL_GPU_SCALING_ACTIVE                               253 



#define NV_CTRL_DFP_SCALING_ACTIVE                               254 



#define NV_CTRL_FSAA_APPLICATION_ENHANCED                       255  
#define NV_CTRL_FSAA_APPLICATION_ENHANCED_ENABLED                 1
#define NV_CTRL_FSAA_APPLICATION_ENHANCED_DISABLED                0



#define NV_CTRL_FRAMELOCK_SYNC_RATE_4                           256 



#define NV_CTRL_GVO_LOCK_OWNER                                  257 
#define NV_CTRL_GVO_LOCK_OWNER_NONE                               0
#define NV_CTRL_GVO_LOCK_OWNER_GLX                                1
#define NV_CTRL_GVO_LOCK_OWNER_CLONE     2
#define NV_CTRL_GVO_LOCK_OWNER_X_SCREEN                           3



#define NV_CTRL_HWOVERLAY                                       258 
#define NV_CTRL_HWOVERLAY_FALSE                                   0
#define NV_CTRL_HWOVERLAY_TRUE                                    1


#define NV_CTRL_NUM_GPU_ERRORS_RECOVERED                        259 



#define NV_CTRL_REFRESH_RATE_3                                  260 



#define NV_CTRL_ONDEMAND_VBLANK_INTERRUPTS                      261 
#define NV_CTRL_ONDEMAND_VBLANK_INTERRUPTS_OFF                    0
#define NV_CTRL_ONDEMAND_VBLANK_INTERRUPTS_ON                     1



#define NV_CTRL_GPU_POWER_SOURCE                                262 
#define NV_CTRL_GPU_POWER_SOURCE_AC                               0
#define NV_CTRL_GPU_POWER_SOURCE_BATTERY                          1



#define NV_CTRL_GPU_CURRENT_PERFORMANCE_MODE                    263 
#define NV_CTRL_GPU_CURRENT_PERFORMANCE_MODE_DESKTOP              0
#define NV_CTRL_GPU_CURRENT_PERFORMANCE_MODE_MAXPERF              1



#define NV_CTRL_GLYPH_CACHE                                     264 
#define NV_CTRL_GLYPH_CACHE_DISABLED                              0
#define NV_CTRL_GLYPH_CACHE_ENABLED                               1



#define NV_CTRL_GPU_CURRENT_PERFORMANCE_LEVEL                   265 



#define NV_CTRL_GPU_ADAPTIVE_CLOCK_STATE                        266 
#define NV_CTRL_GPU_ADAPTIVE_CLOCK_STATE_DISABLED                 0
#define NV_CTRL_GPU_ADAPTIVE_CLOCK_STATE_ENABLED                  1



#define NV_CTRL_GVO_OUTPUT_VIDEO_LOCKED                         267 
#define NV_CTRL_GVO_OUTPUT_VIDEO_LOCKED_FALSE                     0
#define NV_CTRL_GVO_OUTPUT_VIDEO_LOCKED_TRUE                      1



#define NV_CTRL_GVO_SYNC_LOCK_STATUS                            268 
#define NV_CTRL_GVO_SYNC_LOCK_STATUS_UNLOCKED                     0
#define NV_CTRL_GVO_SYNC_LOCK_STATUS_LOCKED                       1



#define NV_CTRL_GVO_ANC_TIME_CODE_GENERATION                    269 
#define NV_CTRL_GVO_ANC_TIME_CODE_GENERATION_DISABLE              0
#define NV_CTRL_GVO_ANC_TIME_CODE_GENERATION_ENABLE               1



#define NV_CTRL_GVO_COMPOSITE                                   270 
#define NV_CTRL_GVO_COMPOSITE_DISABLE                             0
#define NV_CTRL_GVO_COMPOSITE_ENABLE                              1



#define NV_CTRL_GVO_COMPOSITE_ALPHA_KEY                         271 
#define NV_CTRL_GVO_COMPOSITE_ALPHA_KEY_DISABLE                   0
#define NV_CTRL_GVO_COMPOSITE_ALPHA_KEY_ENABLE                    1



#define NV_CTRL_GVO_COMPOSITE_LUMA_KEY_RANGE                    272 

#define NV_CTRL_GVO_COMPOSITE_MAKE_RANGE(range, enable, min, max) \
    ((((min) & 0x3FF)   <<  0) |  \
     (((max) & 0x3FF)   << 10) |  \
     (((enable) & 0x1)  << 20) |  \
     (((range) & 0x7FF) << 21))

#define NV_CTRL_GVO_COMPOSITE_GET_RANGE(val, range, enable, min, max) \
    (min)    = ((val) >> 0)  & 0x3FF; \
    (max)    = ((val) >> 10) & 0x3FF; \
    (enable) = ((val) >> 20) & 0x1;   \
    (range)  = ((val) >> 21) & 0x7FF;



#define NV_CTRL_GVO_COMPOSITE_CR_KEY_RANGE                      273 



#define NV_CTRL_GVO_COMPOSITE_CB_KEY_RANGE                      274 



#define NV_CTRL_GVO_COMPOSITE_NUM_KEY_RANGES                    275 



#define NV_CTRL_SWITCH_TO_DISPLAYS                              276 



#define NV_CTRL_NOTEBOOK_DISPLAY_CHANGE_LID_EVENT               277 
#define NV_CTRL_NOTEBOOK_DISPLAY_CHANGE_LID_EVENT_CLOSE           0
#define NV_CTRL_NOTEBOOK_DISPLAY_CHANGE_LID_EVENT_OPEN            1


#define NV_CTRL_NOTEBOOK_INTERNAL_LCD                           278 


#define NV_CTRL_DEPTH_30_ALLOWED                                279 



#define NV_CTRL_MODE_SET_EVENT                                  280 



#define NV_CTRL_OPENGL_AA_LINE_GAMMA_VALUE                      281 



#define NV_CTRL_VCSC_HIGH_PERF_MODE                             282 
#define NV_CTRL_VCSC_HIGH_PERF_MODE_DISABLE                       0
#define NV_CTRL_VCSC_HIGH_PERF_MODE_ENABLE                        1


#define NV_CTRL_DISPLAYPORT_LINK_RATE                           291 
#define NV_CTRL_DISPLAYPORT_LINK_RATE_DISABLED                  0x0
#define NV_CTRL_DISPLAYPORT_LINK_RATE_1_62GBPS                  0x6
#define NV_CTRL_DISPLAYPORT_LINK_RATE_2_70GBPS                  0xA


#define NV_CTRL_STEREO_EYES_EXCHANGE                            292  
#define NV_CTRL_STEREO_EYES_EXCHANGE_OFF                          0
#define NV_CTRL_STEREO_EYES_EXCHANGE_ON                           1


#define NV_CTRL_NO_SCANOUT                                      293 
#define NV_CTRL_NO_SCANOUT_DISABLED                             0
#define NV_CTRL_NO_SCANOUT_ENABLED                              1


#define NV_CTRL_GVO_CSC_CHANGED_EVENT                           294 


#define NV_CTRL_FRAMELOCK_SLAVEABLE                             295 


#define NV_CTRL_GVO_SYNC_TO_DISPLAY                             296 
#define NV_CTRL_GVO_SYNC_TO_DISPLAY_DISABLE                     0
#define NV_CTRL_GVO_SYNC_TO_DISPLAY_ENABLE                      1


#define NV_CTRL_X_SERVER_UNIQUE_ID                              297 


#define NV_CTRL_PIXMAP_CACHE                                    298 
#define NV_CTRL_PIXMAP_CACHE_DISABLE                              0
#define NV_CTRL_PIXMAP_CACHE_ENABLE                               1


#define NV_CTRL_PIXMAP_CACHE_ROUNDING_SIZE_KB                   299 


#define NV_CTRL_IS_GVO_DISPLAY                                  300 
#define NV_CTRL_IS_GVO_DISPLAY_FALSE                              0
#define NV_CTRL_IS_GVO_DISPLAY_TRUE                               1


#define NV_CTRL_PCI_ID                                          301 


#define NV_CTRL_GVO_FULL_RANGE_COLOR                            302 
#define NV_CTRL_GVO_FULL_RANGE_COLOR_DISABLED                     0
#define NV_CTRL_GVO_FULL_RANGE_COLOR_ENABLED                      1


#define NV_CTRL_SLI_MOSAIC_MODE_AVAILABLE                       303 
#define NV_CTRL_SLI_MOSAIC_MODE_AVAILABLE_FALSE                   0
#define NV_CTRL_SLI_MOSAIC_MODE_AVAILABLE_TRUE                    1


#define NV_CTRL_GVO_ENABLE_RGB_DATA                             304 
#define NV_CTRL_GVO_ENABLE_RGB_DATA_DISABLE                       0
#define NV_CTRL_GVO_ENABLE_RGB_DATA_ENABLE                        1


#define NV_CTRL_IMAGE_SHARPENING_DEFAULT                        305 


#define NV_CTRL_PCI_DOMAIN                                      306 


#define NV_CTRL_GVI_NUM_JACKS                                   307 


#define NV_CTRL_GVI_MAX_LINKS_PER_STREAM                        308 


#define NV_CTRL_GVI_DETECTED_CHANNEL_BITS_PER_COMPONENT         309 
#define NV_CTRL_GVI_BITS_PER_COMPONENT_UNKNOWN                    0
#define NV_CTRL_GVI_BITS_PER_COMPONENT_8                          1
#define NV_CTRL_GVI_BITS_PER_COMPONENT_10                         2
#define NV_CTRL_GVI_BITS_PER_COMPONENT_12                         3


#define NV_CTRL_GVI_REQUESTED_STREAM_BITS_PER_COMPONENT         310 


#define NV_CTRL_GVI_DETECTED_CHANNEL_COMPONENT_SAMPLING         311 
#define NV_CTRL_GVI_COMPONENT_SAMPLING_UNKNOWN                    0
#define NV_CTRL_GVI_COMPONENT_SAMPLING_4444                       1
#define NV_CTRL_GVI_COMPONENT_SAMPLING_4224                       2
#define NV_CTRL_GVI_COMPONENT_SAMPLING_444                        3
#define NV_CTRL_GVI_COMPONENT_SAMPLING_422                        4
#define NV_CTRL_GVI_COMPONENT_SAMPLING_420                        5


#define NV_CTRL_GVI_REQUESTED_STREAM_COMPONENT_SAMPLING         312 


#define NV_CTRL_GVI_REQUESTED_STREAM_CHROMA_EXPAND              313 
#define NV_CTRL_GVI_CHROMA_EXPAND_FALSE                           0
#define NV_CTRL_GVI_CHROMA_EXPAND_TRUE                            1


#define NV_CTRL_GVI_DETECTED_CHANNEL_COLOR_SPACE                314 
#define NV_CTRL_GVI_COLOR_SPACE_UNKNOWN                           0
#define NV_CTRL_GVI_COLOR_SPACE_GBR                               1
#define NV_CTRL_GVI_COLOR_SPACE_GBRA                              2
#define NV_CTRL_GVI_COLOR_SPACE_GBRD                              3
#define NV_CTRL_GVI_COLOR_SPACE_YCBCR                             4
#define NV_CTRL_GVI_COLOR_SPACE_YCBCRA                            5
#define NV_CTRL_GVI_COLOR_SPACE_YCBCRD                            6


#define NV_CTRL_GVI_DETECTED_CHANNEL_LINK_ID                    315 
#define NV_CTRL_GVI_LINK_ID_UNKNOWN                          0xFFFF


#define NV_CTRL_GVI_DETECTED_CHANNEL_SMPTE352_IDENTIFIER        316 


#define NV_CTRL_GVI_GLOBAL_IDENTIFIER                           317 

#define NV_CTRL_FRAMELOCK_SYNC_DELAY_RESOLUTION                 318 


#define NV_CTRL_GPU_COOLER_MANUAL_CONTROL                       319 
#define NV_CTRL_GPU_COOLER_MANUAL_CONTROL_FALSE                   0
#define NV_CTRL_GPU_COOLER_MANUAL_CONTROL_TRUE                    1


#define NV_CTRL_THERMAL_COOLER_LEVEL                            320 


#define NV_CTRL_THERMAL_COOLER_LEVEL_SET_DEFAULT                321 


#define NV_CTRL_THERMAL_COOLER_CONTROL_TYPE                     322 
#define NV_CTRL_THERMAL_COOLER_CONTROL_TYPE_NONE                  0
#define NV_CTRL_THERMAL_COOLER_CONTROL_TYPE_TOGGLE                1 
#define NV_CTRL_THERMAL_COOLER_CONTROL_TYPE_VARIABLE              2


#define NV_CTRL_THERMAL_COOLER_TARGET                           323 
#define NV_CTRL_THERMAL_COOLER_TARGET_NONE                        0
#define NV_CTRL_THERMAL_COOLER_TARGET_GPU                         1
#define NV_CTRL_THERMAL_COOLER_TARGET_MEMORY                      2
#define NV_CTRL_THERMAL_COOLER_TARGET_POWER_SUPPLY                4
#define NV_CTRL_THERMAL_COOLER_TARGET_GPU_RELATED   \
        (NV_CTRL_THERMAL_COOLER_TARGET_GPU |        \
         NV_CTRL_THERMAL_COOLER_TARGET_MEMORY |     \
         NV_CTRL_THERMAL_COOLER_TARGET_POWER_SUPPLY) 

#define NV_CTRL_GPU_ECC_SUPPORTED                               324 
#define NV_CTRL_GPU_ECC_SUPPORTED_FALSE                           0
#define NV_CTRL_GPU_ECC_SUPPORTED_TRUE                            1

#define NV_CTRL_GPU_ECC_STATUS                                  325 
#define NV_CTRL_GPU_ECC_STATUS_DISABLED                           0
#define NV_CTRL_GPU_ECC_STATUS_ENABLED                            1

#define NV_CTRL_GPU_ECC_CONFIGURATION_SUPPORTED                 326 
#define NV_CTRL_GPU_ECC_CONFIGURATION_SUPPORTED_FALSE             0
#define NV_CTRL_GPU_ECC_CONFIGURATION_SUPPORTED_TRUE              1

#define NV_CTRL_GPU_ECC_CONFIGURATION                           327 
#define NV_CTRL_GPU_ECC_CONFIGURATION_DISABLED                    0
#define NV_CTRL_GPU_ECC_CONFIGURATION_ENABLED                     1

#define NV_CTRL_GPU_ECC_DEFAULT_CONFIGURATION                   328 
#define NV_CTRL_GPU_ECC_DEFAULT_CONFIGURATION_DISABLED            0
#define NV_CTRL_GPU_ECC_DEFAULT_CONFIGURATION_ENABLED             1

#define NV_CTRL_GPU_ECC_SINGLE_BIT_ERRORS                       329 

#define NV_CTRL_GPU_ECC_DOUBLE_BIT_ERRORS                       330 

#define NV_CTRL_GPU_ECC_AGGREGATE_SINGLE_BIT_ERRORS             331 

#define NV_CTRL_GPU_ECC_AGGREGATE_DOUBLE_BIT_ERRORS             332 

#define NV_CTRL_GPU_ECC_RESET_ERROR_STATUS                      333 
#define NV_CTRL_GPU_ECC_RESET_ERROR_STATUS_VOLATILE             0x00000001
#define NV_CTRL_GPU_ECC_RESET_ERROR_STATUS_AGGREGATE            0x00000002

#define NV_CTRL_GPU_POWER_MIZER_MODE                            334 
#define NV_CTRL_GPU_POWER_MIZER_MODE_ADAPTIVE                     0
#define NV_CTRL_GPU_POWER_MIZER_MODE_PREFER_MAXIMUM_PERFORMANCE   1


#define NV_CTRL_GVI_SYNC_OUTPUT_FORMAT                          335 


#define NV_CTRL_GVI_MAX_CHANNELS_PER_JACK                       336 


#define NV_CTRL_GVI_MAX_STREAMS                                 337 

#define NV_CTRL_GVI_NUM_CAPTURE_SURFACES                        338 

#define NV_CTRL_OVERSCAN_COMPENSATION                           339 

#define NV_CTRL_GPU_PCIE_GENERATION                             341 
#define NV_CTRL_GPU_PCIE_GENERATION1                            0x00000001
#define NV_CTRL_GPU_PCIE_GENERATION2                            0x00000002
#define NV_CTRL_GPU_PCIE_GENERATION3                            0x00000003

#define NV_CTRL_GVI_BOUND_GPU                                   342 


#define NV_CTRL_GVIO_REQUESTED_VIDEO_FORMAT3                    343 


#define NV_CTRL_ACCELERATE_TRAPEZOIDS                           344 
#define NV_CTRL_ACCELERATE_TRAPEZOIDS_DISABLE                   0
#define NV_CTRL_ACCELERATE_TRAPEZOIDS_ENABLE                    1


#define NV_CTRL_GPU_CORES                                       345 


#define NV_CTRL_GPU_MEMORY_BUS_WIDTH                            346 


#define NV_CTRL_GVI_TEST_MODE                                   347 
#define NV_CTRL_GVI_TEST_MODE_DISABLE                             0
#define NV_CTRL_GVI_TEST_MODE_ENABLE                              1

#define NV_CTRL_COLOR_SPACE                                     348 
#define NV_CTRL_COLOR_SPACE_RGB                                   0
#define NV_CTRL_COLOR_SPACE_YCbCr422                              1
#define NV_CTRL_COLOR_SPACE_YCbCr444                              2

#define NV_CTRL_COLOR_RANGE                                     349 
#define NV_CTRL_COLOR_RANGE_FULL                                  0
#define NV_CTRL_COLOR_RANGE_LIMITED                               1

#define NV_CTRL_GPU_SCALING_DEFAULT_TARGET                      350 
#define NV_CTRL_GPU_SCALING_DEFAULT_METHOD                      351 

#define NV_CTRL_DITHERING_MODE                                  352 
#define NV_CTRL_DITHERING_MODE_AUTO                               0
#define NV_CTRL_DITHERING_MODE_DYNAMIC_2X2                        1
#define NV_CTRL_DITHERING_MODE_STATIC_2X2                         2
#define NV_CTRL_DITHERING_MODE_TEMPORAL                           3

#define NV_CTRL_CURRENT_DITHERING                               353 
#define NV_CTRL_CURRENT_DITHERING_DISABLED                        0
#define NV_CTRL_CURRENT_DITHERING_ENABLED                         1

#define NV_CTRL_CURRENT_DITHERING_MODE                          354 
#define NV_CTRL_CURRENT_DITHERING_MODE_NONE                       0
#define NV_CTRL_CURRENT_DITHERING_MODE_DYNAMIC_2X2                1
#define NV_CTRL_CURRENT_DITHERING_MODE_STATIC_2X2                 2
#define NV_CTRL_CURRENT_DITHERING_MODE_TEMPORAL                   3

#define NV_CTRL_THERMAL_SENSOR_READING                          355 

#define NV_CTRL_THERMAL_SENSOR_PROVIDER                         356 
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_NONE                      0
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_GPU_INTERNAL              1
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_ADM1032                   2
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_ADT7461                   3
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_MAX6649                   4
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_MAX1617                   5
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_LM99                      6
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_LM89                      7
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_LM64                      8
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_G781                      9
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_ADT7473                  10
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_SBMAX6649                11
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_VBIOSEVT                 12
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_OS                       13
#define NV_CTRL_THERMAL_SENSOR_PROVIDER_UNKNOWN          0xFFFFFFFF

#define NV_CTRL_THERMAL_SENSOR_TARGET                           357 
#define NV_CTRL_THERMAL_SENSOR_TARGET_NONE                        0
#define NV_CTRL_THERMAL_SENSOR_TARGET_GPU                         1
#define NV_CTRL_THERMAL_SENSOR_TARGET_MEMORY                      2
#define NV_CTRL_THERMAL_SENSOR_TARGET_POWER_SUPPLY                4
#define NV_CTRL_THERMAL_SENSOR_TARGET_BOARD                       8
#define NV_CTRL_THERMAL_SENSOR_TARGET_UNKNOWN            0xFFFFFFFF

#define NV_CTRL_SHOW_MULTIGPU_VISUAL_INDICATOR                  358  
#define NV_CTRL_SHOW_MULTIGPU_VISUAL_INDICATOR_FALSE              0
#define NV_CTRL_SHOW_MULTIGPU_VISUAL_INDICATOR_TRUE               1

#define NV_CTRL_GPU_CURRENT_PROCESSOR_CLOCK_FREQS               359 


#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS                         360  
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_NONE              0x00000000
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_INTERLACED        0x00000001
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_PROGRESSIVE       0x00000002
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_PSF               0x00000004
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_3G_LEVEL_A        0x00000008
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_3G_LEVEL_B        0x00000010
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_3G          \
    ((NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_3G_LEVEL_A) | \
     (NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_3G_LEVEL_B))
#define NV_CTRL_GVIO_VIDEO_FORMAT_FLAGS_3G_1080P_NO_12BPC 0x00000020


#define NV_CTRL_GPU_PCIE_MAX_LINK_SPEED                         361 

#define NV_CTRL_3D_VISION_PRO_RESET_TRANSCEIVER_TO_FACTORY_SETTINGS 363 

#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_CHANNEL                   364 

#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_MODE                      365 
#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_MODE_INVALID              0
#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_MODE_LOW_RANGE            1
#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_MODE_MEDIUM_RANGE         2
#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_MODE_HIGH_RANGE           3
#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_MODE_COUNT                4


#define NV_CTRL_SYNCHRONOUS_PALETTE_UPDATES                     367  
#define NV_CTRL_SYNCHRONOUS_PALETTE_UPDATES_DISABLE             0
#define NV_CTRL_SYNCHRONOUS_PALETTE_UPDATES_ENABLE              1

#define NV_CTRL_DITHERING_DEPTH                                 368 
#define NV_CTRL_DITHERING_DEPTH_AUTO                            0
#define NV_CTRL_DITHERING_DEPTH_6_BITS                          1
#define NV_CTRL_DITHERING_DEPTH_8_BITS                          2

#define NV_CTRL_CURRENT_DITHERING_DEPTH                         369 
#define NV_CTRL_CURRENT_DITHERING_DEPTH_NONE                    0
#define NV_CTRL_CURRENT_DITHERING_DEPTH_6_BITS                  1
#define NV_CTRL_CURRENT_DITHERING_DEPTH_8_BITS                  2

#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_CHANNEL_FREQUENCY     370 

#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_CHANNEL_QUALITY       371 

#define NV_CTRL_3D_VISION_PRO_TRANSCEIVER_CHANNEL_COUNT         372 

#define NV_CTRL_3D_VISION_PRO_PAIR_GLASSES                      373 
#define NV_CTRL_3D_VISION_PRO_PAIR_GLASSES_STOP                 0
#define NV_CTRL_3D_VISION_PRO_PAIR_GLASSES_BEACON               0xFFFFFFFF

#define NV_CTRL_3D_VISION_PRO_UNPAIR_GLASSES                    374 

#define NV_CTRL_3D_VISION_PRO_DISCOVER_GLASSES                  375 

#define NV_CTRL_3D_VISION_PRO_IDENTIFY_GLASSES                  376 

#define NV_CTRL_3D_VISION_PRO_GLASSES_SYNC_CYCLE                378 

#define NV_CTRL_3D_VISION_PRO_GLASSES_MISSED_SYNC_CYCLES        379 

#define NV_CTRL_3D_VISION_PRO_GLASSES_BATTERY_LEVEL             380 



#define NV_CTRL_GVO_ANC_PARITY_COMPUTATION                      381 
#define NV_CTRL_GVO_ANC_PARITY_COMPUTATION_AUTO                   0
#define NV_CTRL_GVO_ANC_PARITY_COMPUTATION_ON                     1
#define NV_CTRL_GVO_ANC_PARITY_COMPUTATION_OFF                    2

#define NV_CTRL_3D_VISION_PRO_GLASSES_PAIR_EVENT                382 

#define NV_CTRL_3D_VISION_PRO_GLASSES_UNPAIR_EVENT              383 

#define NV_CTRL_GPU_PCIE_CURRENT_LINK_WIDTH                     384 

#define NV_CTRL_GPU_PCIE_CURRENT_LINK_SPEED                     385 

#define NV_CTRL_GVO_AUDIO_BLANKING                              386 
#define NV_CTRL_GVO_AUDIO_BLANKING_DISABLE                        0
#define NV_CTRL_GVO_AUDIO_BLANKING_ENABLE                         1

#define NV_CTRL_CURRENT_METAMODE_ID                             387 

#define NV_CTRL_DISPLAY_ENABLED                                 388 
#define NV_CTRL_DISPLAY_ENABLED_TRUE                              1
#define NV_CTRL_DISPLAY_ENABLED_FALSE                             0


#define NV_CTRL_LAST_ATTRIBUTE NV_CTRL_DISPLAY_ENABLED





#define NV_CTRL_STRING_PRODUCT_NAME                             0  



#define NV_CTRL_STRING_VBIOS_VERSION                            1  



#define NV_CTRL_STRING_NVIDIA_DRIVER_VERSION                    3  



#define NV_CTRL_STRING_DISPLAY_DEVICE_NAME                      4  



#define NV_CTRL_STRING_TV_ENCODER_NAME                          5  



#define NV_CTRL_STRING_GVIO_FIRMWARE_VERSION                    8  

#define NV_CTRL_STRING_GVO_FIRMWARE_VERSION                     8  



#define NV_CTRL_STRING_CURRENT_MODELINE                         9   



#define NV_CTRL_STRING_ADD_MODELINE                            10   



#define NV_CTRL_STRING_DELETE_MODELINE                         11   



#define NV_CTRL_STRING_CURRENT_METAMODE                        12   
#define NV_CTRL_STRING_CURRENT_METAMODE_VERSION_1 \
    NV_CTRL_STRING_CURRENT_METAMODE




#define NV_CTRL_STRING_ADD_METAMODE                            13   



#define NV_CTRL_STRING_DELETE_METAMODE                         14   



#define NV_CTRL_STRING_VCSC_PRODUCT_NAME                       15   



#define NV_CTRL_STRING_VCSC_PRODUCT_ID                         16   



#define NV_CTRL_STRING_VCSC_SERIAL_NUMBER                      17   



#define NV_CTRL_STRING_VCSC_BUILD_DATE                         18   



#define NV_CTRL_STRING_VCSC_FIRMWARE_VERSION                   19   



#define NV_CTRL_STRING_VCSC_FIRMWARE_REVISION                  20   



#define NV_CTRL_STRING_VCSC_HARDWARE_VERSION                   21   



#define NV_CTRL_STRING_VCSC_HARDWARE_REVISION                  22   



#define NV_CTRL_STRING_MOVE_METAMODE                           23   



#define NV_CTRL_STRING_VALID_HORIZ_SYNC_RANGES                 24   



#define NV_CTRL_STRING_VALID_VERT_REFRESH_RANGES               25   



#define NV_CTRL_STRING_XINERAMA_SCREEN_INFO                    26   



#define NV_CTRL_STRING_NVIDIA_XINERAMA_INFO_ORDER              27   

#define NV_CTRL_STRING_TWINVIEW_XINERAMA_INFO_ORDER \
    NV_CTRL_STRING_NVIDIA_XINERAMA_INFO_ORDER 


#define NV_CTRL_STRING_SLI_MODE                                28   



#define NV_CTRL_STRING_PERFORMANCE_MODES                      29   



#define NV_CTRL_STRING_VCSC_FAN_STATUS                         30   



#define NV_CTRL_STRING_VCSC_TEMPERATURES                       31   




#define NV_CTRL_STRING_VCSC_PSU_INFO                           32   



#define NV_CTRL_STRING_GVIO_VIDEO_FORMAT_NAME                  33  

#define NV_CTRL_STRING_GVO_VIDEO_FORMAT_NAME                   33  



#define NV_CTRL_STRING_GPU_CURRENT_CLOCK_FREQS                 34  

#define NV_CTRL_STRING_3D_VISION_PRO_TRANSCEIVER_HARDWARE_REVISION  35 

#define NV_CTRL_STRING_3D_VISION_PRO_TRANSCEIVER_FIRMWARE_VERSION_A 36 

#define NV_CTRL_STRING_3D_VISION_PRO_TRANSCEIVER_FIRMWARE_DATE_A    37 

#define NV_CTRL_STRING_3D_VISION_PRO_TRANSCEIVER_FIRMWARE_VERSION_B 38 

#define NV_CTRL_STRING_3D_VISION_PRO_TRANSCEIVER_FIRMWARE_DATE_B    39 

#define NV_CTRL_STRING_3D_VISION_PRO_TRANSCEIVER_ADDRESS            40 

#define NV_CTRL_STRING_3D_VISION_PRO_GLASSES_FIRMWARE_VERSION_A     41 

#define NV_CTRL_STRING_3D_VISION_PRO_GLASSES_FIRMWARE_DATE_A        42 

#define NV_CTRL_STRING_3D_VISION_PRO_GLASSES_ADDRESS                43 

#define NV_CTRL_STRING_3D_VISION_PRO_GLASSES_NAME                   44 

#define NV_CTRL_STRING_CURRENT_METAMODE_VERSION_2                   45 

#define NV_CTRL_STRING_DISPLAY_NAME_TYPE_BASENAME                   46 

#define NV_CTRL_STRING_DISPLAY_NAME_TYPE_ID                         47 

#define NV_CTRL_STRING_DISPLAY_NAME_DP_GUID                         48 

#define NV_CTRL_STRING_DISPLAY_NAME_EDID_HASH                       49 

#define NV_CTRL_STRING_DISPLAY_NAME_TARGET_INDEX                    50 

#define NV_CTRL_STRING_DISPLAY_NAME_RANDR                           51 

#define NV_CTRL_STRING_LAST_ATTRIBUTE \
    NV_CTRL_STRING_DISPLAY_NAME_RANDR






#define NV_CTRL_BINARY_DATA_EDID                                0  



#define NV_CTRL_BINARY_DATA_MODELINES                           1   



#define NV_CTRL_BINARY_DATA_METAMODES                           2   
#define NV_CTRL_BINARY_DATA_METAMODES_VERSION_1 \
    NV_CTRL_BINARY_DATA_METAMODES



#define NV_CTRL_BINARY_DATA_XSCREENS_USING_GPU                  3   



#define NV_CTRL_BINARY_DATA_GPUS_USED_BY_XSCREEN                4   



#define NV_CTRL_BINARY_DATA_GPUS_USING_FRAMELOCK                5   



#define NV_CTRL_BINARY_DATA_DISPLAY_VIEWPORT                    6   



#define NV_CTRL_BINARY_DATA_FRAMELOCKS_USED_BY_GPU              7   



#define NV_CTRL_BINARY_DATA_GPUS_USING_VCSC                    8   



#define NV_CTRL_BINARY_DATA_VCSCS_USED_BY_GPU                  9   



#define NV_CTRL_BINARY_DATA_COOLERS_USED_BY_GPU                10  



#define NV_CTRL_BINARY_DATA_GPUS_USED_BY_LOGICAL_XSCREEN     11   


#define NV_CTRL_BINARY_DATA_THERMAL_SENSORS_USED_BY_GPU      12  

#define NV_CTRL_BINARY_DATA_GLASSES_PAIRED_TO_3D_VISION_PRO_TRANSCEIVER 13 


#define NV_CTRL_BINARY_DATA_DISPLAY_TARGETS                  14  


#define NV_CTRL_BINARY_DATA_DISPLAYS_CONNECTED_TO_GPU        15  


#define NV_CTRL_BINARY_DATA_METAMODES_VERSION_2              16  


#define NV_CTRL_BINARY_DATA_DISPLAYS_ENABLED_ON_XSCREEN      17  


#define NV_CTRL_BINARY_DATA_LAST_ATTRIBUTE \
        NV_CTRL_BINARY_DATA_DISPLAYS_ENABLED_ON_XSCREEN






#define NV_CTRL_STRING_OPERATION_ADD_METAMODE                  0



#define NV_CTRL_STRING_OPERATION_GTF_MODELINE                  1



#define NV_CTRL_STRING_OPERATION_CVT_MODELINE                  2



#define NV_CTRL_STRING_OPERATION_BUILD_MODEPOOL                3 



#define NV_CTRL_STRING_OPERATION_GVI_CONFIGURE_STREAMS         4 


#define NV_CTRL_STRING_OPERATION_LAST_ATTRIBUTE \
        NV_CTRL_STRING_OPERATION_GVI_CONFIGURE_STREAMS





/*
 * CTRLAttributeValidValuesRec -
 *
 * structure and related defines used by
 * XNVCTRLQueryValidAttributeValues() to describe the valid values of
 * a particular attribute.  The type field will be one of:
 *
 * ATTRIBUTE_TYPE_INTEGER : the attribute is an integer value; there
 * is no fixed range of valid values.
 *
 * ATTRIBUTE_TYPE_BITMASK : the attribute is an integer value,
 * interpretted as a bitmask.
 *
 * ATTRIBUTE_TYPE_BOOL : the attribute is a boolean, valid values are
 * either 1 (on/true) or 0 (off/false).
 *
 * ATTRIBUTE_TYPE_RANGE : the attribute can have any integer value
 * between NVCTRLAttributeValidValues.u.range.min and
 * NVCTRLAttributeValidValues.u.range.max (inclusive).
 *
 * ATTRIBUTE_TYPE_INT_BITS : the attribute can only have certain
 * integer values, indicated by which bits in
 * NVCTRLAttributeValidValues.u.bits.ints are on (for example: if bit
 * 0 is on, then 0 is a valid value; if bit 5 is on, then 5 is a valid
 * value, etc).  This is useful for attributes like NV_CTRL_FSAA_MODE,
 * which can only have certain values, depending on GPU.
 *
 * ATTRIBUTE_TYPE_64BIT_INTEGER : the attribute is a 64 bit integer value;
 * there is no fixed range of valid values.
 *
 * ATTRIBUTE_TYPE_STRING : the attribute is a string value; there is no fixed
 * range of valid values.
 *
 * ATTRIBUTE_TYPE_BINARY_DATA : the attribute is binary data; there is
 * no fixed range of valid values.
 *
 * ATTRIBUTE_TYPE_STRING_OPERATION : the attribute is a string; there is
 * no fixed range of valid values.
 *
 *
 * The permissions field of NVCTRLAttributeValidValuesRec is a bitmask
 * that may contain:
 *
 * ATTRIBUTE_TYPE_READ      - Attribute may be read (queried.)
 * ATTRIBUTE_TYPE_WRITE     - Attribute may be written to (set.)
 * ATTRIBUTE_TYPE_DISPLAY   - Attribute is valid for display target types
 *                            (requires a display_mask if queried via
 *                            a GPU or X screen.)
 * ATTRIBUTE_TYPE_GPU       - Attribute is valid for GPU target types.
 * ATTRIBUTE_TYPE_FRAMELOCK - Attribute is valid for Frame Lock target types.
 * ATTRIBUTE_TYPE_X_SCREEN  - Attribute is valid for X Screen target types.
 * ATTRIBUTE_TYPE_XINERAMA  - Attribute will be made consistent for all
 *                            X Screens when the Xinerama extension is enabled.
 * ATTRIBUTE_TYPE_VCSC      - Attribute is valid for Visual Computing System
 *                            target types.
 * ATTRIBUTE_TYPE_GVI       - Attribute is valid for Graphics Video In target
 *                            types.
 * ATTRIBUTE_TYPE_COOLER    - Attribute is valid for Cooler target types.
 * ATTRIBUTE_TYPE_3D_VISION_PRO_TRANSCEIVER - Attribute is valid for 3D Vision
 *                                            Pro Transceiver target types.
 *
 * See 'Key to Integer Attribute "Permissions"' at the top of this
 * file for a description of what these permission bits mean.
 */

#define ATTRIBUTE_TYPE_UNKNOWN           0
#define ATTRIBUTE_TYPE_INTEGER           1
#define ATTRIBUTE_TYPE_BITMASK           2
#define ATTRIBUTE_TYPE_BOOL              3
#define ATTRIBUTE_TYPE_RANGE             4
#define ATTRIBUTE_TYPE_INT_BITS          5
#define ATTRIBUTE_TYPE_64BIT_INTEGER     6
#define ATTRIBUTE_TYPE_STRING            7
#define ATTRIBUTE_TYPE_BINARY_DATA       8
#define ATTRIBUTE_TYPE_STRING_OPERATION  9

#define ATTRIBUTE_TYPE_READ       0x001
#define ATTRIBUTE_TYPE_WRITE      0x002
#define ATTRIBUTE_TYPE_DISPLAY    0x004
#define ATTRIBUTE_TYPE_GPU        0x008
#define ATTRIBUTE_TYPE_FRAMELOCK  0x010
#define ATTRIBUTE_TYPE_X_SCREEN   0x020
#define ATTRIBUTE_TYPE_XINERAMA   0x040
#define ATTRIBUTE_TYPE_VCSC       0x080
#define ATTRIBUTE_TYPE_GVI        0x100
#define ATTRIBUTE_TYPE_COOLER     0x200
#define ATTRIBUTE_TYPE_THERMAL_SENSOR 0x400
#define ATTRIBUTE_TYPE_3D_VISION_PRO_TRANSCEIVER 0x800

#define ATTRIBUTE_TYPE_ALL_TARGETS                \
    ((ATTRIBUTE_TYPE_DISPLAY)                   | \
     (ATTRIBUTE_TYPE_GPU)                       | \
     (ATTRIBUTE_TYPE_FRAMELOCK)                 | \
     (ATTRIBUTE_TYPE_X_SCREEN)                  | \
     (ATTRIBUTE_TYPE_VCSC)                      | \
     (ATTRIBUTE_TYPE_GVI)                       | \
     (ATTRIBUTE_TYPE_COOLER)                    | \
     (ATTRIBUTE_TYPE_THERMAL_SENSOR)            | \
     (ATTRIBUTE_TYPE_3D_VISION_PRO_TRANSCEIVER))

typedef struct _NVCTRLAttributeValidValues {
    int type;
    union {
        struct {
            int64_t min;
            int64_t max;
        } range;
        struct {
            unsigned int ints;
        } bits;
    } u;
    unsigned int permissions;
} NVCTRLAttributeValidValuesRec;

typedef struct _NVCTRLAttributePermissions {
    int type;
    unsigned int permissions;
} NVCTRLAttributePermissionsRec;




#define ATTRIBUTE_CHANGED_EVENT                     0
#define TARGET_ATTRIBUTE_CHANGED_EVENT              1
#define TARGET_ATTRIBUTE_AVAILABILITY_CHANGED_EVENT 2
#define TARGET_STRING_ATTRIBUTE_CHANGED_EVENT       3
#define TARGET_BINARY_ATTRIBUTE_CHANGED_EVENT       4


#endif 