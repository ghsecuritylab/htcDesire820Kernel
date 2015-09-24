/* png.h - header file for PNG reference library
 *
 * libpng version 1.2.45 - July 7, 2011
 * Copyright (c) 1998-2011 Glenn Randers-Pehrson
 * (Version 0.96 Copyright (c) 1996, 1997 Andreas Dilger)
 * (Version 0.88 Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.)
 *
 * This code is released under the libpng license (See LICENSE, below)
 *
 * Authors and maintainers:
 *  libpng versions 0.71, May 1995, through 0.88, January 1996: Guy Schalnat
 *  libpng versions 0.89c, June 1996, through 0.96, May 1997: Andreas Dilger
 *  libpng versions 0.97, January 1998, through 1.2.45 - July 7, 2011: Glenn
 *  See also "Contributing Authors", below.
 *
 * Note about libpng version numbers:
 *
 *    Due to various miscommunications, unforeseen code incompatibilities
 *    and occasional factors outside the authors' control, version numbering
 *    on the library has not always been consistent and straightforward.
 *    The following table summarizes matters since version 0.89c, which was
 *    the first widely used release:
 *
 *    source                 png.h  png.h  shared-lib
 *    version                string   int  version
 *    -------                ------ -----  ----------
 *    0.89c "1.0 beta 3"     0.89      89  1.0.89
 *    0.90  "1.0 beta 4"     0.90      90  0.90  [should have been 2.0.90]
 *    0.95  "1.0 beta 5"     0.95      95  0.95  [should have been 2.0.95]
 *    0.96  "1.0 beta 6"     0.96      96  0.96  [should have been 2.0.96]
 *    0.97b "1.00.97 beta 7" 1.00.97   97  1.0.1 [should have been 2.0.97]
 *    0.97c                  0.97      97  2.0.97
 *    0.98                   0.98      98  2.0.98
 *    0.99                   0.99      98  2.0.99
 *    0.99a-m                0.99      99  2.0.99
 *    1.00                   1.00     100  2.1.0 [100 should be 10000]
 *    1.0.0      (from here on, the   100  2.1.0 [100 should be 10000]
 *    1.0.1       png.h string is   10001  2.1.0
 *    1.0.1a-e    identical to the  10002  from here on, the shared library
 *    1.0.2       source version)   10002  is 2.V where V is the source code
 *    1.0.2a-b                      10003  version, except as noted.
 *    1.0.3                         10003
 *    1.0.3a-d                      10004
 *    1.0.4                         10004
 *    1.0.4a-f                      10005
 *    1.0.5 (+ 2 patches)           10005
 *    1.0.5a-d                      10006
 *    1.0.5e-r                      10100 (not source compatible)
 *    1.0.5s-v                      10006 (not binary compatible)
 *    1.0.6 (+ 3 patches)           10006 (still binary incompatible)
 *    1.0.6d-f                      10007 (still binary incompatible)
 *    1.0.6g                        10007
 *    1.0.6h                        10007  10.6h (testing xy.z so-numbering)
 *    1.0.6i                        10007  10.6i
 *    1.0.6j                        10007  2.1.0.6j (incompatible with 1.0.0)
 *    1.0.7beta11-14        DLLNUM  10007  2.1.0.7beta11-14 (binary compatible)
 *    1.0.7beta15-18           1    10007  2.1.0.7beta15-18 (binary compatible)
 *    1.0.7rc1-2               1    10007  2.1.0.7rc1-2 (binary compatible)
 *    1.0.7                    1    10007  (still compatible)
 *    1.0.8beta1-4             1    10008  2.1.0.8beta1-4
 *    1.0.8rc1                 1    10008  2.1.0.8rc1
 *    1.0.8                    1    10008  2.1.0.8
 *    1.0.9beta1-6             1    10009  2.1.0.9beta1-6
 *    1.0.9rc1                 1    10009  2.1.0.9rc1
 *    1.0.9beta7-10            1    10009  2.1.0.9beta7-10
 *    1.0.9rc2                 1    10009  2.1.0.9rc2
 *    1.0.9                    1    10009  2.1.0.9
 *    1.0.10beta1              1    10010  2.1.0.10beta1
 *    1.0.10rc1                1    10010  2.1.0.10rc1
 *    1.0.10                   1    10010  2.1.0.10
 *    1.0.11beta1-3            1    10011  2.1.0.11beta1-3
 *    1.0.11rc1                1    10011  2.1.0.11rc1
 *    1.0.11                   1    10011  2.1.0.11
 *    1.0.12beta1-2            2    10012  2.1.0.12beta1-2
 *    1.0.12rc1                2    10012  2.1.0.12rc1
 *    1.0.12                   2    10012  2.1.0.12
 *    1.1.0a-f                 -    10100  2.1.1.0a-f (branch abandoned)
 *    1.2.0beta1-2             2    10200  2.1.2.0beta1-2
 *    1.2.0beta3-5             3    10200  3.1.2.0beta3-5
 *    1.2.0rc1                 3    10200  3.1.2.0rc1
 *    1.2.0                    3    10200  3.1.2.0
 *    1.2.1beta1-4             3    10201  3.1.2.1beta1-4
 *    1.2.1rc1-2               3    10201  3.1.2.1rc1-2
 *    1.2.1                    3    10201  3.1.2.1
 *    1.2.2beta1-6            12    10202  12.so.0.1.2.2beta1-6
 *    1.0.13beta1             10    10013  10.so.0.1.0.13beta1
 *    1.0.13rc1               10    10013  10.so.0.1.0.13rc1
 *    1.2.2rc1                12    10202  12.so.0.1.2.2rc1
 *    1.0.13                  10    10013  10.so.0.1.0.13
 *    1.2.2                   12    10202  12.so.0.1.2.2
 *    1.2.3rc1-6              12    10203  12.so.0.1.2.3rc1-6
 *    1.2.3                   12    10203  12.so.0.1.2.3
 *    1.2.4beta1-3            13    10204  12.so.0.1.2.4beta1-3
 *    1.0.14rc1               13    10014  10.so.0.1.0.14rc1
 *    1.2.4rc1                13    10204  12.so.0.1.2.4rc1
 *    1.0.14                  10    10014  10.so.0.1.0.14
 *    1.2.4                   13    10204  12.so.0.1.2.4
 *    1.2.5beta1-2            13    10205  12.so.0.1.2.5beta1-2
 *    1.0.15rc1-3             10    10015  10.so.0.1.0.15rc1-3
 *    1.2.5rc1-3              13    10205  12.so.0.1.2.5rc1-3
 *    1.0.15                  10    10015  10.so.0.1.0.15
 *    1.2.5                   13    10205  12.so.0.1.2.5
 *    1.2.6beta1-4            13    10206  12.so.0.1.2.6beta1-4
 *    1.0.16                  10    10016  10.so.0.1.0.16
 *    1.2.6                   13    10206  12.so.0.1.2.6
 *    1.2.7beta1-2            13    10207  12.so.0.1.2.7beta1-2
 *    1.0.17rc1               10    10017  10.so.0.1.0.17rc1
 *    1.2.7rc1                13    10207  12.so.0.1.2.7rc1
 *    1.0.17                  10    10017  10.so.0.1.0.17
 *    1.2.7                   13    10207  12.so.0.1.2.7
 *    1.2.8beta1-5            13    10208  12.so.0.1.2.8beta1-5
 *    1.0.18rc1-5             10    10018  10.so.0.1.0.18rc1-5
 *    1.2.8rc1-5              13    10208  12.so.0.1.2.8rc1-5
 *    1.0.18                  10    10018  10.so.0.1.0.18
 *    1.2.8                   13    10208  12.so.0.1.2.8
 *    1.2.9beta1-3            13    10209  12.so.0.1.2.9beta1-3
 *    1.2.9beta4-11           13    10209  12.so.0.9[.0]
 *    1.2.9rc1                13    10209  12.so.0.9[.0]
 *    1.2.9                   13    10209  12.so.0.9[.0]
 *    1.2.10beta1-8           13    10210  12.so.0.10[.0]
 *    1.2.10rc1-3             13    10210  12.so.0.10[.0]
 *    1.2.10                  13    10210  12.so.0.10[.0]
 *    1.2.11beta1-4           13    10211  12.so.0.11[.0]
 *    1.0.19rc1-5             10    10019  10.so.0.19[.0]
 *    1.2.11rc1-5             13    10211  12.so.0.11[.0]
 *    1.0.19                  10    10019  10.so.0.19[.0]
 *    1.2.11                  13    10211  12.so.0.11[.0]
 *    1.0.20                  10    10020  10.so.0.20[.0]
 *    1.2.12                  13    10212  12.so.0.12[.0]
 *    1.2.13beta1             13    10213  12.so.0.13[.0]
 *    1.0.21                  10    10021  10.so.0.21[.0]
 *    1.2.13                  13    10213  12.so.0.13[.0]
 *    1.2.14beta1-2           13    10214  12.so.0.14[.0]
 *    1.0.22rc1               10    10022  10.so.0.22[.0]
 *    1.2.14rc1               13    10214  12.so.0.14[.0]
 *    1.0.22                  10    10022  10.so.0.22[.0]
 *    1.2.14                  13    10214  12.so.0.14[.0]
 *    1.2.15beta1-6           13    10215  12.so.0.15[.0]
 *    1.0.23rc1-5             10    10023  10.so.0.23[.0]
 *    1.2.15rc1-5             13    10215  12.so.0.15[.0]
 *    1.0.23                  10    10023  10.so.0.23[.0]
 *    1.2.15                  13    10215  12.so.0.15[.0]
 *    1.2.16beta1-2           13    10216  12.so.0.16[.0]
 *    1.2.16rc1               13    10216  12.so.0.16[.0]
 *    1.0.24                  10    10024  10.so.0.24[.0]
 *    1.2.16                  13    10216  12.so.0.16[.0]
 *    1.2.17beta1-2           13    10217  12.so.0.17[.0]
 *    1.0.25rc1               10    10025  10.so.0.25[.0]
 *    1.2.17rc1-3             13    10217  12.so.0.17[.0]
 *    1.0.25                  10    10025  10.so.0.25[.0]
 *    1.2.17                  13    10217  12.so.0.17[.0]
 *    1.0.26                  10    10026  10.so.0.26[.0]
 *    1.2.18                  13    10218  12.so.0.18[.0]
 *    1.2.19beta1-31          13    10219  12.so.0.19[.0]
 *    1.0.27rc1-6             10    10027  10.so.0.27[.0]
 *    1.2.19rc1-6             13    10219  12.so.0.19[.0]
 *    1.0.27                  10    10027  10.so.0.27[.0]
 *    1.2.19                  13    10219  12.so.0.19[.0]
 *    1.2.20beta01-04         13    10220  12.so.0.20[.0]
 *    1.0.28rc1-6             10    10028  10.so.0.28[.0]
 *    1.2.20rc1-6             13    10220  12.so.0.20[.0]
 *    1.0.28                  10    10028  10.so.0.28[.0]
 *    1.2.20                  13    10220  12.so.0.20[.0]
 *    1.2.21beta1-2           13    10221  12.so.0.21[.0]
 *    1.2.21rc1-3             13    10221  12.so.0.21[.0]
 *    1.0.29                  10    10029  10.so.0.29[.0]
 *    1.2.21                  13    10221  12.so.0.21[.0]
 *    1.2.22beta1-4           13    10222  12.so.0.22[.0]
 *    1.0.30rc1               10    10030  10.so.0.30[.0]
 *    1.2.22rc1               13    10222  12.so.0.22[.0]
 *    1.0.30                  10    10030  10.so.0.30[.0]
 *    1.2.22                  13    10222  12.so.0.22[.0]
 *    1.2.23beta01-05         13    10223  12.so.0.23[.0]
 *    1.2.23rc01              13    10223  12.so.0.23[.0]
 *    1.2.23                  13    10223  12.so.0.23[.0]
 *    1.2.24beta01-02         13    10224  12.so.0.24[.0]
 *    1.2.24rc01              13    10224  12.so.0.24[.0]
 *    1.2.24                  13    10224  12.so.0.24[.0]
 *    1.2.25beta01-06         13    10225  12.so.0.25[.0]
 *    1.2.25rc01-02           13    10225  12.so.0.25[.0]
 *    1.0.31                  10    10031  10.so.0.31[.0]
 *    1.2.25                  13    10225  12.so.0.25[.0]
 *    1.2.26beta01-06         13    10226  12.so.0.26[.0]
 *    1.2.26rc01              13    10226  12.so.0.26[.0]
 *    1.2.26                  13    10226  12.so.0.26[.0]
 *    1.0.32                  10    10032  10.so.0.32[.0]
 *    1.2.27beta01-06         13    10227  12.so.0.27[.0]
 *    1.2.27rc01              13    10227  12.so.0.27[.0]
 *    1.0.33                  10    10033  10.so.0.33[.0]
 *    1.2.27                  13    10227  12.so.0.27[.0]
 *    1.0.34                  10    10034  10.so.0.34[.0]
 *    1.2.28                  13    10228  12.so.0.28[.0]
 *    1.2.29beta01-03         13    10229  12.so.0.29[.0]
 *    1.2.29rc01              13    10229  12.so.0.29[.0]
 *    1.0.35                  10    10035  10.so.0.35[.0]
 *    1.2.29                  13    10229  12.so.0.29[.0]
 *    1.0.37                  10    10037  10.so.0.37[.0]
 *    1.2.30beta01-04         13    10230  12.so.0.30[.0]
 *    1.0.38rc01-08           10    10038  10.so.0.38[.0]
 *    1.2.30rc01-08           13    10230  12.so.0.30[.0]
 *    1.0.38                  10    10038  10.so.0.38[.0]
 *    1.2.30                  13    10230  12.so.0.30[.0]
 *    1.0.39rc01-03           10    10039  10.so.0.39[.0]
 *    1.2.31rc01-03           13    10231  12.so.0.31[.0]
 *    1.0.39                  10    10039  10.so.0.39[.0]
 *    1.2.31                  13    10231  12.so.0.31[.0]
 *    1.2.32beta01-02         13    10232  12.so.0.32[.0]
 *    1.0.40rc01              10    10040  10.so.0.40[.0]
 *    1.2.32rc01              13    10232  12.so.0.32[.0]
 *    1.0.40                  10    10040  10.so.0.40[.0]
 *    1.2.32                  13    10232  12.so.0.32[.0]
 *    1.2.33beta01-02         13    10233  12.so.0.33[.0]
 *    1.2.33rc01-02           13    10233  12.so.0.33[.0]
 *    1.0.41rc01              10    10041  10.so.0.41[.0]
 *    1.2.33                  13    10233  12.so.0.33[.0]
 *    1.0.41                  10    10041  10.so.0.41[.0]
 *    1.2.34beta01-07         13    10234  12.so.0.34[.0]
 *    1.0.42rc01              10    10042  10.so.0.42[.0]
 *    1.2.34rc01              13    10234  12.so.0.34[.0]
 *    1.0.42                  10    10042  10.so.0.42[.0]
 *    1.2.34                  13    10234  12.so.0.34[.0]
 *    1.2.35beta01-03         13    10235  12.so.0.35[.0]
 *    1.0.43rc01-02           10    10043  10.so.0.43[.0]
 *    1.2.35rc01-02           13    10235  12.so.0.35[.0]
 *    1.0.43                  10    10043  10.so.0.43[.0]
 *    1.2.35                  13    10235  12.so.0.35[.0]
 *    1.2.36beta01-05         13    10236  12.so.0.36[.0]
 *    1.2.36rc01              13    10236  12.so.0.36[.0]
 *    1.0.44                  10    10044  10.so.0.44[.0]
 *    1.2.36                  13    10236  12.so.0.36[.0]
 *    1.2.37beta01-03         13    10237  12.so.0.37[.0]
 *    1.2.37rc01              13    10237  12.so.0.37[.0]
 *    1.2.37                  13    10237  12.so.0.37[.0]
 *    1.0.45                  10    10045  12.so.0.45[.0]
 *    1.0.46                  10    10046  10.so.0.46[.0]
 *    1.2.38beta01            13    10238  12.so.0.38[.0]
 *    1.2.38rc01-03           13    10238  12.so.0.38[.0]
 *    1.0.47                  10    10047  10.so.0.47[.0]
 *    1.2.38                  13    10238  12.so.0.38[.0]
 *    1.2.39beta01-05         13    10239  12.so.0.39[.0]
 *    1.2.39rc01              13    10239  12.so.0.39[.0]
 *    1.0.48                  10    10048  10.so.0.48[.0]
 *    1.2.39                  13    10239  12.so.0.39[.0]
 *    1.2.40beta01            13    10240  12.so.0.40[.0]
 *    1.2.40rc01              13    10240  12.so.0.40[.0]
 *    1.0.49                  10    10049  10.so.0.49[.0]
 *    1.2.40                  13    10240  12.so.0.40[.0]
 *    1.2.41beta01-18         13    10241  12.so.0.41[.0]
 *    1.0.51rc01              10    10051  10.so.0.51[.0]
 *    1.2.41rc01-03           13    10241  12.so.0.41[.0]
 *    1.0.51                  10    10051  10.so.0.51[.0]
 *    1.2.41                  13    10241  12.so.0.41[.0]
 *    1.2.42beta01-02         13    10242  12.so.0.42[.0]
 *    1.2.42rc01-05           13    10242  12.so.0.42[.0]
 *    1.0.52                  10    10052  10.so.0.52[.0]
 *    1.2.42                  13    10242  12.so.0.42[.0]
 *    1.2.43beta01-05         13    10243  12.so.0.43[.0]
 *    1.0.53rc01-02           10    10053  10.so.0.53[.0]
 *    1.2.43rc01-02           13    10243  12.so.0.43[.0]
 *    1.0.53                  10    10053  10.so.0.53[.0]
 *    1.2.43                  13    10243  12.so.0.43[.0]
 *    1.2.44beta01-03         13    10244  12.so.0.44[.0]
 *    1.2.44rc01-03           13    10244  12.so.0.44[.0]
 *    1.2.44                  13    10244  12.so.0.44[.0]
 *    1.2.45beta01-03         13    10245  12.so.0.45[.0]
 *    1.0.55rc01              13    10055  10.so.0.55[.0]
 *    1.2.45rc01              13    10245  12.so.0.45[.0]
 *    1.0.55                  13    10055  10.so.0.55[.0]
 *    1.2.45                  13    10245  12.so.0.45[.0]
 *
 *    Henceforth the source version will match the shared-library major
 *    and minor numbers; the shared-library major version number will be
 *    used for changes in backward compatibility, as it is intended.  The
 *    PNG_LIBPNG_VER macro, which is not used within libpng but is available
 *    for applications, is an unsigned integer of the form xyyzz corresponding
 *    to the source version x.y.z (leading zeros in y and z).  Beta versions
 *    were given the previous public release number plus a letter, until
 *    version 1.0.6j; from then on they were given the upcoming public
 *    release number plus "betaNN" or "rcNN".
 *
 *    Binary incompatibility exists only when applications make direct access
 *    to the info_ptr or png_ptr members through png.h, and the compiled
 *    application is loaded with a different version of the library.
 *
 *    DLLNUM will change each time there are forward or backward changes
 *    in binary compatibility (e.g., when a new feature is added).
 *
 * See libpng.txt or libpng.3 for more information.  The PNG specification
 * is available as a W3C Recommendation and as an ISO Specification,
 * <http://www.w3.org/TR/2003/REC-PNG-20031110/
 */

/*
 * COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:
 *
 * If you modify libpng you may insert additional notices immediately following
 * this sentence.
 *
 * This code is released under the libpng license.
 *
 * libpng versions 1.2.6, August 15, 2004, through 1.2.45, July 7, 2011, are
 * Copyright (c) 2004, 2006-2010 Glenn Randers-Pehrson, and are
 * distributed according to the same disclaimer and license as libpng-1.2.5
 * with the following individual added to the list of Contributing Authors:
 *
 *    Cosmin Truta
 *
 * libpng versions 1.0.7, July 1, 2000, through 1.2.5, October 3, 2002, are
 * Copyright (c) 2000-2002 Glenn Randers-Pehrson, and are
 * distributed according to the same disclaimer and license as libpng-1.0.6
 * with the following individuals added to the list of Contributing Authors:
 *
 *    Simon-Pierre Cadieux
 *    Eric S. Raymond
 *    Gilles Vollant
 *
 * and with the following additions to the disclaimer:
 *
 *    There is no warranty against interference with your enjoyment of the
 *    library or against infringement.  There is no warranty that our
 *    efforts or the library will fulfill any of your particular purposes
 *    or needs.  This library is provided with all faults, and the entire
 *    risk of satisfactory quality, performance, accuracy, and effort is with
 *    the user.
 *
 * libpng versions 0.97, January 1998, through 1.0.6, March 20, 2000, are
 * Copyright (c) 1998, 1999, 2000 Glenn Randers-Pehrson, and are
 * distributed according to the same disclaimer and license as libpng-0.96,
 * with the following individuals added to the list of Contributing Authors:
 *
 *    Tom Lane
 *    Glenn Randers-Pehrson
 *    Willem van Schaik
 *
 * libpng versions 0.89, June 1996, through 0.96, May 1997, are
 * Copyright (c) 1996, 1997 Andreas Dilger
 * Distributed according to the same disclaimer and license as libpng-0.88,
 * with the following individuals added to the list of Contributing Authors:
 *
 *    John Bowler
 *    Kevin Bracey
 *    Sam Bushell
 *    Magnus Holmgren
 *    Greg Roelofs
 *    Tom Tanner
 *
 * libpng versions 0.5, May 1995, through 0.88, January 1996, are
 * Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.
 *
 * For the purposes of this copyright and license, "Contributing Authors"
 * is defined as the following set of individuals:
 *
 *    Andreas Dilger
 *    Dave Martindale
 *    Guy Eric Schalnat
 *    Paul Schmidt
 *    Tim Wegner
 *
 * The PNG Reference Library is supplied "AS IS".  The Contributing Authors
 * and Group 42, Inc. disclaim all warranties, expressed or implied,
 * including, without limitation, the warranties of merchantability and of
 * fitness for any purpose.  The Contributing Authors and Group 42, Inc.
 * assume no liability for direct, indirect, incidental, special, exemplary,
 * or consequential damages, which may result from the use of the PNG
 * Reference Library, even if advised of the possibility of such damage.
 *
 * Permission is hereby granted to use, copy, modify, and distribute this
 * source code, or portions hereof, for any purpose, without fee, subject
 * to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented.
 *
 * 2. Altered versions must be plainly marked as such and
 * must not be misrepresented as being the original source.
 *
 * 3. This Copyright notice may not be removed or altered from
 *    any source or altered source distribution.
 *
 * The Contributing Authors and Group 42, Inc. specifically permit, without
 * fee, and encourage the use of this source code as a component to
 * supporting the PNG file format in commercial products.  If you use this
 * source code in a product, acknowledgment is not required but would be
 * appreciated.
 */

/*
 * A "png_get_copyright" function is available, for convenient use in "about"
 * boxes and the like:
 *
 * printf("%s",png_get_copyright(NULL));
 *
 * Also, the PNG logo (in PNG format, of course) is supplied in the
 * files "pngbar.png" and "pngbar.jpg (88x31) and "pngnow.png" (98x31).
 */




#ifndef PNG_H
#define PNG_H


#define PNG_LIBPNG_VER_STRING "1.2.45"
#define PNG_HEADER_VERSION_STRING \
   " libpng version 1.2.45 - July 7, 2011\n"

#define PNG_LIBPNG_VER_SONUM   0
#define PNG_LIBPNG_VER_DLLNUM  13

#define PNG_LIBPNG_VER_MAJOR   1
#define PNG_LIBPNG_VER_MINOR   2
#define PNG_LIBPNG_VER_RELEASE 45

#define PNG_LIBPNG_VER_BUILD  0

#define PNG_LIBPNG_BUILD_ALPHA    1
#define PNG_LIBPNG_BUILD_BETA     2
#define PNG_LIBPNG_BUILD_RC       3
#define PNG_LIBPNG_BUILD_STABLE   4
#define PNG_LIBPNG_BUILD_RELEASE_STATUS_MASK 7

#define PNG_LIBPNG_BUILD_PATCH    8 
#define PNG_LIBPNG_BUILD_PRIVATE 16 
#define PNG_LIBPNG_BUILD_SPECIAL 32 

#define PNG_LIBPNG_BUILD_BASE_TYPE PNG_LIBPNG_BUILD_STABLE

#define PNG_LIBPNG_VER 10245 

#ifndef PNG_VERSION_INFO_ONLY
#include "zlib.h"
#endif

#include "pngconf.h"


#ifdef PNG_USER_PRIVATEBUILD
#  define PNG_LIBPNG_BUILD_TYPE \
          (PNG_LIBPNG_BUILD_BASE_TYPE | PNG_LIBPNG_BUILD_PRIVATE)
#else
#  ifdef PNG_LIBPNG_SPECIALBUILD
#    define PNG_LIBPNG_BUILD_TYPE \
            (PNG_LIBPNG_BUILD_BASE_TYPE | PNG_LIBPNG_BUILD_SPECIAL)
#  else
#    define PNG_LIBPNG_BUILD_TYPE (PNG_LIBPNG_BUILD_BASE_TYPE)
#  endif
#endif

#ifndef PNG_VERSION_INFO_ONLY

#ifdef __cplusplus
extern "C" {
#endif 


#ifndef PNG_NO_TYPECAST_NULL
#define int_p_NULL                (int *)NULL
#define png_bytep_NULL            (png_bytep)NULL
#define png_bytepp_NULL           (png_bytepp)NULL
#define png_doublep_NULL          (png_doublep)NULL
#define png_error_ptr_NULL        (png_error_ptr)NULL
#define png_flush_ptr_NULL        (png_flush_ptr)NULL
#define png_free_ptr_NULL         (png_free_ptr)NULL
#define png_infopp_NULL           (png_infopp)NULL
#define png_malloc_ptr_NULL       (png_malloc_ptr)NULL
#define png_read_status_ptr_NULL  (png_read_status_ptr)NULL
#define png_rw_ptr_NULL           (png_rw_ptr)NULL
#define png_structp_NULL          (png_structp)NULL
#define png_uint_16p_NULL         (png_uint_16p)NULL
#define png_voidp_NULL            (png_voidp)NULL
#define png_write_status_ptr_NULL (png_write_status_ptr)NULL
#else
#define int_p_NULL                NULL
#define png_bytep_NULL            NULL
#define png_bytepp_NULL           NULL
#define png_doublep_NULL          NULL
#define png_error_ptr_NULL        NULL
#define png_flush_ptr_NULL        NULL
#define png_free_ptr_NULL         NULL
#define png_infopp_NULL           NULL
#define png_malloc_ptr_NULL       NULL
#define png_read_status_ptr_NULL  NULL
#define png_rw_ptr_NULL           NULL
#define png_structp_NULL          NULL
#define png_uint_16p_NULL         NULL
#define png_voidp_NULL            NULL
#define png_write_status_ptr_NULL NULL
#endif

#if !defined(PNG_NO_EXTERN) || defined(PNG_ALWAYS_EXTERN)
#ifdef PNG_USE_GLOBAL_ARRAYS
PNG_EXPORT_VAR (PNG_CONST char) png_libpng_ver[18];
  
#else
#define png_libpng_ver png_get_header_ver(NULL)
#endif

#ifdef PNG_USE_GLOBAL_ARRAYS
PNG_EXPORT_VAR (PNG_CONST int FARDATA) png_pass_start[7];
PNG_EXPORT_VAR (PNG_CONST int FARDATA) png_pass_inc[7];
PNG_EXPORT_VAR (PNG_CONST int FARDATA) png_pass_ystart[7];
PNG_EXPORT_VAR (PNG_CONST int FARDATA) png_pass_yinc[7];
PNG_EXPORT_VAR (PNG_CONST int FARDATA) png_pass_mask[7];
PNG_EXPORT_VAR (PNG_CONST int FARDATA) png_pass_dsp_mask[7];
#endif

#endif 

typedef struct png_color_struct
{
   png_byte red;
   png_byte green;
   png_byte blue;
} png_color;
typedef png_color FAR * png_colorp;
typedef png_color FAR * FAR * png_colorpp;

typedef struct png_color_16_struct
{
   png_byte index;    
   png_uint_16 red;   
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 gray;  
} png_color_16;
typedef png_color_16 FAR * png_color_16p;
typedef png_color_16 FAR * FAR * png_color_16pp;

typedef struct png_color_8_struct
{
   png_byte red;   
   png_byte green;
   png_byte blue;
   png_byte gray;  
   png_byte alpha; 
} png_color_8;
typedef png_color_8 FAR * png_color_8p;
typedef png_color_8 FAR * FAR * png_color_8pp;

typedef struct png_sPLT_entry_struct
{
   png_uint_16 red;
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 alpha;
   png_uint_16 frequency;
} png_sPLT_entry;
typedef png_sPLT_entry FAR * png_sPLT_entryp;
typedef png_sPLT_entry FAR * FAR * png_sPLT_entrypp;


typedef struct png_sPLT_struct
{
   png_charp name;           
   png_byte depth;           
   png_sPLT_entryp entries;  
   png_int_32 nentries;      
} png_sPLT_t;
typedef png_sPLT_t FAR * png_sPLT_tp;
typedef png_sPLT_t FAR * FAR * png_sPLT_tpp;

#ifdef PNG_TEXT_SUPPORTED
typedef struct png_text_struct
{
   int  compression;       
   png_charp key;          
   png_charp text;         
   png_size_t text_length; 
#ifdef PNG_iTXt_SUPPORTED
   png_size_t itxt_length; 
   png_charp lang;         
   png_charp lang_key;     
#endif
} png_text;
typedef png_text FAR * png_textp;
typedef png_text FAR * FAR * png_textpp;
#endif

#define PNG_TEXT_COMPRESSION_NONE_WR -3
#define PNG_TEXT_COMPRESSION_zTXt_WR -2
#define PNG_TEXT_COMPRESSION_NONE    -1
#define PNG_TEXT_COMPRESSION_zTXt     0
#define PNG_ITXT_COMPRESSION_NONE     1
#define PNG_ITXT_COMPRESSION_zTXt     2
#define PNG_TEXT_COMPRESSION_LAST     3  

typedef struct png_time_struct
{
   png_uint_16 year; 
   png_byte month;   
   png_byte day;     
   png_byte hour;    
   png_byte minute;  
   png_byte second;  
} png_time;
typedef png_time FAR * png_timep;
typedef png_time FAR * FAR * png_timepp;

#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED) || \
 defined(PNG_HANDLE_AS_UNKNOWN_SUPPORTED)
#define PNG_CHUNK_NAME_LENGTH 5
typedef struct png_unknown_chunk_t
{
    png_byte name[PNG_CHUNK_NAME_LENGTH];
    png_byte *data;
    png_size_t size;

    
    png_byte location; 
}
png_unknown_chunk;
typedef png_unknown_chunk FAR * png_unknown_chunkp;
typedef png_unknown_chunk FAR * FAR * png_unknown_chunkpp;
#endif

typedef struct png_info_struct
{
   
   png_uint_32 width PNG_DEPSTRUCT;       
   png_uint_32 height PNG_DEPSTRUCT;      
   png_uint_32 valid PNG_DEPSTRUCT;       
   png_uint_32 rowbytes PNG_DEPSTRUCT;    
   png_colorp palette PNG_DEPSTRUCT;      
   png_uint_16 num_palette PNG_DEPSTRUCT; 
   png_uint_16 num_trans PNG_DEPSTRUCT;   
   png_byte bit_depth PNG_DEPSTRUCT;      
   png_byte color_type PNG_DEPSTRUCT;     
   
   png_byte compression_type PNG_DEPSTRUCT; 
   png_byte filter_type PNG_DEPSTRUCT;    
   png_byte interlace_type PNG_DEPSTRUCT; 

   
   png_byte channels PNG_DEPSTRUCT;       
   png_byte pixel_depth PNG_DEPSTRUCT;    
   png_byte spare_byte PNG_DEPSTRUCT;     
   png_byte signature[8] PNG_DEPSTRUCT;   

   /* The rest of the data is optional.  If you are reading, check the
    * valid field to see if the information in these are valid.  If you
    * are writing, set the valid field to those chunks you want written,
    * and initialize the appropriate fields below.
    */

#if defined(PNG_gAMA_SUPPORTED) && defined(PNG_FLOATING_POINT_SUPPORTED)
   float gamma PNG_DEPSTRUCT; 
#endif

#ifdef PNG_sRGB_SUPPORTED
    
    
   png_byte srgb_intent PNG_DEPSTRUCT; 
#endif

#ifdef PNG_TEXT_SUPPORTED
   int num_text PNG_DEPSTRUCT; 
   int max_text PNG_DEPSTRUCT; 
   png_textp text PNG_DEPSTRUCT; 
#endif 

#ifdef PNG_tIME_SUPPORTED
   png_time mod_time PNG_DEPSTRUCT;
#endif

#ifdef PNG_sBIT_SUPPORTED
   png_color_8 sig_bit PNG_DEPSTRUCT; 
#endif

#if defined(PNG_tRNS_SUPPORTED) || defined(PNG_READ_EXPAND_SUPPORTED) || \
defined(PNG_READ_BACKGROUND_SUPPORTED)
   png_bytep trans PNG_DEPSTRUCT; 
   png_color_16 trans_values PNG_DEPSTRUCT; 
#endif

#if defined(PNG_bKGD_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   png_color_16 background PNG_DEPSTRUCT;
#endif

#ifdef PNG_oFFs_SUPPORTED
   png_int_32 x_offset PNG_DEPSTRUCT; 
   png_int_32 y_offset PNG_DEPSTRUCT; 
   png_byte offset_unit_type PNG_DEPSTRUCT; 
#endif

#ifdef PNG_pHYs_SUPPORTED
   png_uint_32 x_pixels_per_unit PNG_DEPSTRUCT; 
   png_uint_32 y_pixels_per_unit PNG_DEPSTRUCT; 
   png_byte phys_unit_type PNG_DEPSTRUCT; 
#endif

#ifdef PNG_hIST_SUPPORTED
   png_uint_16p hist PNG_DEPSTRUCT;
#endif

#ifdef PNG_cHRM_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
   float x_white PNG_DEPSTRUCT;
   float y_white PNG_DEPSTRUCT;
   float x_red PNG_DEPSTRUCT;
   float y_red PNG_DEPSTRUCT;
   float x_green PNG_DEPSTRUCT;
   float y_green PNG_DEPSTRUCT;
   float x_blue PNG_DEPSTRUCT;
   float y_blue PNG_DEPSTRUCT;
#endif
#endif

#ifdef PNG_pCAL_SUPPORTED
   png_charp pcal_purpose PNG_DEPSTRUCT;  
   png_int_32 pcal_X0 PNG_DEPSTRUCT;      
   png_int_32 pcal_X1 PNG_DEPSTRUCT;      
   png_charp pcal_units PNG_DEPSTRUCT;    
   png_charpp pcal_params PNG_DEPSTRUCT;  
   png_byte pcal_type PNG_DEPSTRUCT;      
   png_byte pcal_nparams PNG_DEPSTRUCT;   
#endif

#ifdef PNG_FREE_ME_SUPPORTED
   png_uint_32 free_me PNG_DEPSTRUCT;     
#endif

#if defined(PNG_UNKNOWN_CHUNKS_SUPPORTED) || \
 defined(PNG_HANDLE_AS_UNKNOWN_SUPPORTED)
   
   png_unknown_chunkp unknown_chunks PNG_DEPSTRUCT;
   png_size_t unknown_chunks_num PNG_DEPSTRUCT;
#endif

#ifdef PNG_iCCP_SUPPORTED
   
   png_charp iccp_name PNG_DEPSTRUCT;     
   png_charp iccp_profile PNG_DEPSTRUCT;  
                            
   png_uint_32 iccp_proflen PNG_DEPSTRUCT;  
   png_byte iccp_compression PNG_DEPSTRUCT; 
#endif

#ifdef PNG_sPLT_SUPPORTED
   
   png_sPLT_tp splt_palettes PNG_DEPSTRUCT;
   png_uint_32 splt_palettes_num PNG_DEPSTRUCT;
#endif

#ifdef PNG_sCAL_SUPPORTED
   png_byte scal_unit PNG_DEPSTRUCT;         
#ifdef PNG_FLOATING_POINT_SUPPORTED
   double scal_pixel_width PNG_DEPSTRUCT;    
   double scal_pixel_height PNG_DEPSTRUCT;   
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
   png_charp scal_s_width PNG_DEPSTRUCT;     
   png_charp scal_s_height PNG_DEPSTRUCT;    
#endif
#endif

#ifdef PNG_INFO_IMAGE_SUPPORTED
   
   
   png_bytepp row_pointers PNG_DEPSTRUCT;        
#endif

#if defined(PNG_FIXED_POINT_SUPPORTED) && defined(PNG_gAMA_SUPPORTED)
   png_fixed_point int_gamma PNG_DEPSTRUCT; 
#endif

#if defined(PNG_cHRM_SUPPORTED) && defined(PNG_FIXED_POINT_SUPPORTED)
   png_fixed_point int_x_white PNG_DEPSTRUCT;
   png_fixed_point int_y_white PNG_DEPSTRUCT;
   png_fixed_point int_x_red PNG_DEPSTRUCT;
   png_fixed_point int_y_red PNG_DEPSTRUCT;
   png_fixed_point int_x_green PNG_DEPSTRUCT;
   png_fixed_point int_y_green PNG_DEPSTRUCT;
   png_fixed_point int_x_blue PNG_DEPSTRUCT;
   png_fixed_point int_y_blue PNG_DEPSTRUCT;
#endif

} png_info;

typedef png_info FAR * png_infop;
typedef png_info FAR * FAR * png_infopp;

#define PNG_UINT_31_MAX ((png_uint_32)0x7fffffffL)
#define PNG_UINT_32_MAX ((png_uint_32)(-1))
#define PNG_SIZE_MAX ((png_size_t)(-1))
#if defined(PNG_1_0_X) || defined (PNG_1_2_X)
#define PNG_MAX_UINT PNG_UINT_31_MAX
#endif

#define PNG_COLOR_MASK_PALETTE    1
#define PNG_COLOR_MASK_COLOR      2
#define PNG_COLOR_MASK_ALPHA      4

#define PNG_COLOR_TYPE_GRAY 0
#define PNG_COLOR_TYPE_PALETTE  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)
#define PNG_COLOR_TYPE_RGB        (PNG_COLOR_MASK_COLOR)
#define PNG_COLOR_TYPE_RGB_ALPHA  (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_ALPHA)
#define PNG_COLOR_TYPE_GRAY_ALPHA (PNG_COLOR_MASK_ALPHA)
#define PNG_COLOR_TYPE_RGBA  PNG_COLOR_TYPE_RGB_ALPHA
#define PNG_COLOR_TYPE_GA  PNG_COLOR_TYPE_GRAY_ALPHA

#define PNG_COMPRESSION_TYPE_BASE 0 
#define PNG_COMPRESSION_TYPE_DEFAULT PNG_COMPRESSION_TYPE_BASE

#define PNG_FILTER_TYPE_BASE      0 
#define PNG_INTRAPIXEL_DIFFERENCING 64 
#define PNG_FILTER_TYPE_DEFAULT   PNG_FILTER_TYPE_BASE

#define PNG_INTERLACE_NONE        0 
#define PNG_INTERLACE_ADAM7       1 
#define PNG_INTERLACE_LAST        2 

#define PNG_OFFSET_PIXEL          0 
#define PNG_OFFSET_MICROMETER     1 
#define PNG_OFFSET_LAST           2 

#define PNG_EQUATION_LINEAR       0 
#define PNG_EQUATION_BASE_E       1 
#define PNG_EQUATION_ARBITRARY    2 
#define PNG_EQUATION_HYPERBOLIC   3 
#define PNG_EQUATION_LAST         4 

#define PNG_SCALE_UNKNOWN         0 
#define PNG_SCALE_METER           1 
#define PNG_SCALE_RADIAN          2 
#define PNG_SCALE_LAST            3 

#define PNG_RESOLUTION_UNKNOWN    0 
#define PNG_RESOLUTION_METER      1 
#define PNG_RESOLUTION_LAST       2 

#define PNG_sRGB_INTENT_PERCEPTUAL 0
#define PNG_sRGB_INTENT_RELATIVE   1
#define PNG_sRGB_INTENT_SATURATION 2
#define PNG_sRGB_INTENT_ABSOLUTE   3
#define PNG_sRGB_INTENT_LAST       4 

#define PNG_KEYWORD_MAX_LENGTH     79

#define PNG_MAX_PALETTE_LENGTH    256

/* These determine if an ancillary chunk's data has been successfully read
 * from the PNG header, or if the application has filled in the corresponding
 * data in the info_struct to be written into the output file.  The values
 * of the PNG_INFO_<chunk> defines should NOT be changed.
 */
#define PNG_INFO_gAMA 0x0001
#define PNG_INFO_sBIT 0x0002
#define PNG_INFO_cHRM 0x0004
#define PNG_INFO_PLTE 0x0008
#define PNG_INFO_tRNS 0x0010
#define PNG_INFO_bKGD 0x0020
#define PNG_INFO_hIST 0x0040
#define PNG_INFO_pHYs 0x0080
#define PNG_INFO_oFFs 0x0100
#define PNG_INFO_tIME 0x0200
#define PNG_INFO_pCAL 0x0400
#define PNG_INFO_sRGB 0x0800   
#define PNG_INFO_iCCP 0x1000   
#define PNG_INFO_sPLT 0x2000   
#define PNG_INFO_sCAL 0x4000   
#define PNG_INFO_IDAT 0x8000L  

typedef struct png_row_info_struct
{
   png_uint_32 width; 
   png_uint_32 rowbytes; 
   png_byte color_type; 
   png_byte bit_depth; 
   png_byte channels; 
   png_byte pixel_depth; 
} png_row_info;

typedef png_row_info FAR * png_row_infop;
typedef png_row_info FAR * FAR * png_row_infopp;

typedef struct png_struct_def png_struct;
typedef png_struct FAR * png_structp;

typedef void (PNGAPI *png_error_ptr) PNGARG((png_structp, png_const_charp));
typedef void (PNGAPI *png_rw_ptr) PNGARG((png_structp, png_bytep, png_size_t));
typedef void (PNGAPI *png_flush_ptr) PNGARG((png_structp));
typedef void (PNGAPI *png_read_status_ptr) PNGARG((png_structp, png_uint_32,
   int));
typedef void (PNGAPI *png_write_status_ptr) PNGARG((png_structp, png_uint_32,
   int));

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
typedef void (PNGAPI *png_progressive_info_ptr) PNGARG((png_structp, png_infop));
typedef void (PNGAPI *png_progressive_end_ptr) PNGARG((png_structp, png_infop));
typedef void (PNGAPI *png_progressive_row_ptr) PNGARG((png_structp, png_bytep,
   png_uint_32, int));
#endif

#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
typedef void (PNGAPI *png_user_transform_ptr) PNGARG((png_structp,
    png_row_infop, png_bytep));
#endif

#ifdef PNG_USER_CHUNKS_SUPPORTED
typedef int (PNGAPI *png_user_chunk_ptr) PNGARG((png_structp, png_unknown_chunkp));
#endif
#ifdef PNG_UNKNOWN_CHUNKS_SUPPORTED
typedef void (PNGAPI *png_unknown_chunk_ptr) PNGARG((png_structp));
#endif

#define PNG_TRANSFORM_IDENTITY       0x0000    
#define PNG_TRANSFORM_STRIP_16       0x0001    
#define PNG_TRANSFORM_STRIP_ALPHA    0x0002    
#define PNG_TRANSFORM_PACKING        0x0004    
#define PNG_TRANSFORM_PACKSWAP       0x0008    
#define PNG_TRANSFORM_EXPAND         0x0010    
#define PNG_TRANSFORM_INVERT_MONO    0x0020    
#define PNG_TRANSFORM_SHIFT          0x0040    
#define PNG_TRANSFORM_BGR            0x0080    
#define PNG_TRANSFORM_SWAP_ALPHA     0x0100    
#define PNG_TRANSFORM_SWAP_ENDIAN    0x0200    
#define PNG_TRANSFORM_INVERT_ALPHA   0x0400    
#define PNG_TRANSFORM_STRIP_FILLER   0x0800    
#define PNG_TRANSFORM_STRIP_FILLER_BEFORE 0x0800  
#define PNG_TRANSFORM_STRIP_FILLER_AFTER  0x1000  
#define PNG_TRANSFORM_GRAY_TO_RGB   0x2000      

#define PNG_FLAG_MNG_EMPTY_PLTE     0x01
#define PNG_FLAG_MNG_FILTER_64      0x04
#define PNG_ALL_MNG_FEATURES        0x05

typedef png_voidp (*png_malloc_ptr) PNGARG((png_structp, png_size_t));
typedef void (*png_free_ptr) PNGARG((png_structp, png_voidp));


struct png_struct_def
{
#ifdef PNG_SETJMP_SUPPORTED
   jmp_buf jmpbuf;            
#endif
   png_error_ptr error_fn PNG_DEPSTRUCT;    
   png_error_ptr warning_fn PNG_DEPSTRUCT;  
   png_voidp error_ptr PNG_DEPSTRUCT;       
   png_rw_ptr write_data_fn PNG_DEPSTRUCT;  
   png_rw_ptr read_data_fn PNG_DEPSTRUCT;   
   png_voidp io_ptr PNG_DEPSTRUCT;          

#ifdef PNG_READ_USER_TRANSFORM_SUPPORTED
   png_user_transform_ptr read_user_transform_fn PNG_DEPSTRUCT; 
#endif

#ifdef PNG_WRITE_USER_TRANSFORM_SUPPORTED
   png_user_transform_ptr write_user_transform_fn PNG_DEPSTRUCT; 
#endif

#ifdef PNG_USER_TRANSFORM_PTR_SUPPORTED
#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED)
   png_voidp user_transform_ptr PNG_DEPSTRUCT; 
   png_byte user_transform_depth PNG_DEPSTRUCT;    
   png_byte user_transform_channels PNG_DEPSTRUCT; 
#endif
#endif

   png_uint_32 mode PNG_DEPSTRUCT;          
   png_uint_32 flags PNG_DEPSTRUCT;         
   png_uint_32 transformations PNG_DEPSTRUCT; 

   z_stream zstream PNG_DEPSTRUCT;          
   png_bytep zbuf PNG_DEPSTRUCT;            
   png_size_t zbuf_size PNG_DEPSTRUCT;      
   int zlib_level PNG_DEPSTRUCT;            
   int zlib_method PNG_DEPSTRUCT;           
   int zlib_window_bits PNG_DEPSTRUCT;      
   int zlib_mem_level PNG_DEPSTRUCT;        
   int zlib_strategy PNG_DEPSTRUCT;         

   png_uint_32 width PNG_DEPSTRUCT;         
   png_uint_32 height PNG_DEPSTRUCT;        
   png_uint_32 num_rows PNG_DEPSTRUCT;      
   png_uint_32 usr_width PNG_DEPSTRUCT;     
   png_uint_32 rowbytes PNG_DEPSTRUCT;      
#if 0 
   png_size_t irowbytes PNG_DEPSTRUCT;
#endif
#ifdef PNG_USER_LIMITS_SUPPORTED
   png_uint_32 user_chunk_cache_max PNG_DEPSTRUCT;
#endif
   png_uint_32 iwidth PNG_DEPSTRUCT;        
   png_uint_32 row_number PNG_DEPSTRUCT;    
   png_bytep prev_row PNG_DEPSTRUCT;        
   png_bytep row_buf PNG_DEPSTRUCT;         
#ifndef PNG_NO_WRITE_FILTER
   png_bytep sub_row PNG_DEPSTRUCT;         
   png_bytep up_row PNG_DEPSTRUCT;          
   png_bytep avg_row PNG_DEPSTRUCT;         
   png_bytep paeth_row PNG_DEPSTRUCT;       
#endif
   png_row_info row_info PNG_DEPSTRUCT;     

   png_uint_32 idat_size PNG_DEPSTRUCT;     
   png_uint_32 crc PNG_DEPSTRUCT;           
   png_colorp palette PNG_DEPSTRUCT;        
   png_uint_16 num_palette PNG_DEPSTRUCT;   
   png_uint_16 num_trans PNG_DEPSTRUCT;     
   png_byte chunk_name[5] PNG_DEPSTRUCT;    
   png_byte compression PNG_DEPSTRUCT;      
   png_byte filter PNG_DEPSTRUCT;           
   png_byte interlaced PNG_DEPSTRUCT;       
   png_byte pass PNG_DEPSTRUCT;             
   png_byte do_filter PNG_DEPSTRUCT;        
   png_byte color_type PNG_DEPSTRUCT;       
   png_byte bit_depth PNG_DEPSTRUCT;        
   png_byte usr_bit_depth PNG_DEPSTRUCT;    
   png_byte pixel_depth PNG_DEPSTRUCT;      
   png_byte channels PNG_DEPSTRUCT;         
   png_byte usr_channels PNG_DEPSTRUCT;     
   png_byte sig_bytes PNG_DEPSTRUCT;        /* magic bytes read/written from start of file */

#if defined(PNG_READ_FILLER_SUPPORTED) || defined(PNG_WRITE_FILLER_SUPPORTED)
#ifdef PNG_LEGACY_SUPPORTED
   png_byte filler PNG_DEPSTRUCT;           
#else
   png_uint_16 filler PNG_DEPSTRUCT;           
#endif
#endif

#ifdef PNG_bKGD_SUPPORTED
   png_byte background_gamma_type PNG_DEPSTRUCT;
#  ifdef PNG_FLOATING_POINT_SUPPORTED
   float background_gamma PNG_DEPSTRUCT;
#  endif
   png_color_16 background PNG_DEPSTRUCT;   
#ifdef PNG_READ_GAMMA_SUPPORTED
   png_color_16 background_1 PNG_DEPSTRUCT; 
#endif
#endif 

#ifdef PNG_WRITE_FLUSH_SUPPORTED
   png_flush_ptr output_flush_fn PNG_DEPSTRUCT; 
   png_uint_32 flush_dist PNG_DEPSTRUCT;    
   png_uint_32 flush_rows PNG_DEPSTRUCT;    /* number of rows written since last flush */
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   int gamma_shift PNG_DEPSTRUCT;      
#ifdef PNG_FLOATING_POINT_SUPPORTED
   float gamma PNG_DEPSTRUCT;          
   float screen_gamma PNG_DEPSTRUCT;   
#endif
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   png_bytep gamma_table PNG_DEPSTRUCT;     
   png_bytep gamma_from_1 PNG_DEPSTRUCT;    
   png_bytep gamma_to_1 PNG_DEPSTRUCT;      
   png_uint_16pp gamma_16_table PNG_DEPSTRUCT; 
   png_uint_16pp gamma_16_from_1 PNG_DEPSTRUCT; 
   png_uint_16pp gamma_16_to_1 PNG_DEPSTRUCT; 
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_sBIT_SUPPORTED)
   png_color_8 sig_bit PNG_DEPSTRUCT;       
#endif

#if defined(PNG_READ_SHIFT_SUPPORTED) || defined(PNG_WRITE_SHIFT_SUPPORTED)
   png_color_8 shift PNG_DEPSTRUCT;         
#endif

#if defined(PNG_tRNS_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED) \
 || defined(PNG_READ_EXPAND_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   png_bytep trans PNG_DEPSTRUCT;           
   png_color_16 trans_values PNG_DEPSTRUCT; 
#endif

   png_read_status_ptr read_row_fn PNG_DEPSTRUCT;   
   png_write_status_ptr write_row_fn PNG_DEPSTRUCT; 
#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
   png_progressive_info_ptr info_fn PNG_DEPSTRUCT; 
   png_progressive_row_ptr row_fn PNG_DEPSTRUCT;   
   png_progressive_end_ptr end_fn PNG_DEPSTRUCT;   
   png_bytep save_buffer_ptr PNG_DEPSTRUCT;        
   png_bytep save_buffer PNG_DEPSTRUCT;            
   png_bytep current_buffer_ptr PNG_DEPSTRUCT;     
   png_bytep current_buffer PNG_DEPSTRUCT;         
   png_uint_32 push_length PNG_DEPSTRUCT;          
   png_uint_32 skip_length PNG_DEPSTRUCT;          
   png_size_t save_buffer_size PNG_DEPSTRUCT;      
   png_size_t save_buffer_max PNG_DEPSTRUCT;       
   png_size_t buffer_size PNG_DEPSTRUCT;           
   png_size_t current_buffer_size PNG_DEPSTRUCT;   
   int process_mode PNG_DEPSTRUCT;                 
   int cur_palette PNG_DEPSTRUCT;                  

#  ifdef PNG_TEXT_SUPPORTED
     png_size_t current_text_size PNG_DEPSTRUCT;   
     png_size_t current_text_left PNG_DEPSTRUCT;   
     png_charp current_text PNG_DEPSTRUCT;         
     png_charp current_text_ptr PNG_DEPSTRUCT;     
#  endif 
#endif 

#if defined(__TURBOC__) && !defined(_Windows) && !defined(__FLAT__)
   png_bytepp offset_table_ptr PNG_DEPSTRUCT;
   png_bytep offset_table PNG_DEPSTRUCT;
   png_uint_16 offset_table_number PNG_DEPSTRUCT;
   png_uint_16 offset_table_count PNG_DEPSTRUCT;
   png_uint_16 offset_table_count_free PNG_DEPSTRUCT;
#endif

#ifdef PNG_READ_DITHER_SUPPORTED
   png_bytep palette_lookup PNG_DEPSTRUCT;         
   png_bytep dither_index PNG_DEPSTRUCT;           
#endif

#if defined(PNG_READ_DITHER_SUPPORTED) || defined(PNG_hIST_SUPPORTED)
   png_uint_16p hist PNG_DEPSTRUCT;                
#endif

#ifdef PNG_WRITE_WEIGHTED_FILTER_SUPPORTED
   png_byte heuristic_method PNG_DEPSTRUCT;        
   png_byte num_prev_filters PNG_DEPSTRUCT;        
   png_bytep prev_filters PNG_DEPSTRUCT;           
   png_uint_16p filter_weights PNG_DEPSTRUCT;      
   png_uint_16p inv_filter_weights PNG_DEPSTRUCT;  
   png_uint_16p filter_costs PNG_DEPSTRUCT;        
   png_uint_16p inv_filter_costs PNG_DEPSTRUCT;    
#endif

#ifdef PNG_TIME_RFC1123_SUPPORTED
   png_charp time_buffer PNG_DEPSTRUCT;            
#endif


#ifdef PNG_FREE_ME_SUPPORTED
   png_uint_32 free_me PNG_DEPSTRUCT;   
#endif

#ifdef PNG_USER_CHUNKS_SUPPORTED
   png_voidp user_chunk_ptr PNG_DEPSTRUCT;
   png_user_chunk_ptr read_user_chunk_fn PNG_DEPSTRUCT; 
#endif

#ifdef PNG_HANDLE_AS_UNKNOWN_SUPPORTED
   int num_chunk_list PNG_DEPSTRUCT;
   png_bytep chunk_list PNG_DEPSTRUCT;
#endif

#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
   png_byte rgb_to_gray_status PNG_DEPSTRUCT;
   
   png_uint_16 rgb_to_gray_red_coeff PNG_DEPSTRUCT;
   png_uint_16 rgb_to_gray_green_coeff PNG_DEPSTRUCT;
   png_uint_16 rgb_to_gray_blue_coeff PNG_DEPSTRUCT;
#endif

#if defined(PNG_MNG_FEATURES_SUPPORTED) || \
    defined(PNG_READ_EMPTY_PLTE_SUPPORTED) || \
    defined(PNG_WRITE_EMPTY_PLTE_SUPPORTED)
#ifdef PNG_1_0_X
   png_byte mng_features_permitted PNG_DEPSTRUCT;
#else
   png_uint_32 mng_features_permitted PNG_DEPSTRUCT;
#endif 
#endif

#if defined(PNG_READ_GAMMA_SUPPORTED) || defined(PNG_READ_BACKGROUND_SUPPORTED)
   png_fixed_point int_gamma PNG_DEPSTRUCT;
#endif

#ifdef PNG_MNG_FEATURES_SUPPORTED
   png_byte filter_type PNG_DEPSTRUCT;
#endif

#ifdef PNG_1_0_X
   png_uint_32 row_buf_size PNG_DEPSTRUCT;
#endif

#ifdef PNG_ASSEMBLER_CODE_SUPPORTED
#  ifndef PNG_1_0_X
#    ifdef PNG_MMX_CODE_SUPPORTED
   png_byte     mmx_bitdepth_threshold PNG_DEPSTRUCT;
   png_uint_32  mmx_rowbytes_threshold PNG_DEPSTRUCT;
#    endif
   png_uint_32  asm_flags PNG_DEPSTRUCT;
#  endif
#endif

#ifdef PNG_USER_MEM_SUPPORTED
   png_voidp mem_ptr PNG_DEPSTRUCT;            
   png_malloc_ptr malloc_fn PNG_DEPSTRUCT;     
   png_free_ptr free_fn PNG_DEPSTRUCT;         
#endif

   png_bytep big_row_buf PNG_DEPSTRUCT;        

#ifdef PNG_READ_DITHER_SUPPORTED
   png_bytep dither_sort PNG_DEPSTRUCT;        
   png_bytep index_to_palette PNG_DEPSTRUCT;   
                                 
   png_bytep palette_to_index PNG_DEPSTRUCT;   
                                 
#endif

   png_byte compression_type PNG_DEPSTRUCT;

#ifdef PNG_USER_LIMITS_SUPPORTED
   png_uint_32 user_width_max PNG_DEPSTRUCT;
   png_uint_32 user_height_max PNG_DEPSTRUCT;
#endif

#ifdef PNG_UNKNOWN_CHUNKS_SUPPORTED
   
   png_unknown_chunk unknown_chunk PNG_DEPSTRUCT;
#endif

  png_uint_32 old_big_row_buf_size PNG_DEPSTRUCT;
  png_uint_32 old_prev_row_size PNG_DEPSTRUCT;

  png_charp chunkdata PNG_DEPSTRUCT;  


};


typedef png_structp version_1_2_45;

typedef png_struct FAR * FAR * png_structpp;


extern PNG_EXPORT(png_uint_32,png_access_version_number) PNGARG((void));

extern PNG_EXPORT(void,png_set_sig_bytes) PNGARG((png_structp png_ptr,
   int num_bytes));

extern PNG_EXPORT(int,png_sig_cmp) PNGARG((png_bytep sig, png_size_t start,
   png_size_t num_to_check));

extern PNG_EXPORT(int,png_check_sig) PNGARG((png_bytep sig, int num)) PNG_DEPRECATED;

extern PNG_EXPORT(png_structp,png_create_read_struct)
   PNGARG((png_const_charp user_png_ver, png_voidp error_ptr,
   png_error_ptr error_fn, png_error_ptr warn_fn)) PNG_ALLOCATED;

extern PNG_EXPORT(png_structp,png_create_write_struct)
   PNGARG((png_const_charp user_png_ver, png_voidp error_ptr,
   png_error_ptr error_fn, png_error_ptr warn_fn)) PNG_ALLOCATED;

#ifdef PNG_WRITE_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_compression_buffer_size)
   PNGARG((png_structp png_ptr));
#endif

#ifdef PNG_WRITE_SUPPORTED
extern PNG_EXPORT(void,png_set_compression_buffer_size)
   PNGARG((png_structp png_ptr, png_uint_32 size));
#endif

extern PNG_EXPORT(int,png_reset_zstream) PNGARG((png_structp png_ptr));

#ifdef PNG_USER_MEM_SUPPORTED
extern PNG_EXPORT(png_structp,png_create_read_struct_2)
   PNGARG((png_const_charp user_png_ver, png_voidp error_ptr,
   png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
   png_malloc_ptr malloc_fn, png_free_ptr free_fn)) PNG_ALLOCATED;
extern PNG_EXPORT(png_structp,png_create_write_struct_2)
   PNGARG((png_const_charp user_png_ver, png_voidp error_ptr,
   png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
   png_malloc_ptr malloc_fn, png_free_ptr free_fn)) PNG_ALLOCATED;
#endif

extern PNG_EXPORT(void,png_write_chunk) PNGARG((png_structp png_ptr,
   png_bytep chunk_name, png_bytep data, png_size_t length));

extern PNG_EXPORT(void,png_write_chunk_start) PNGARG((png_structp png_ptr,
   png_bytep chunk_name, png_uint_32 length));

extern PNG_EXPORT(void,png_write_chunk_data) PNGARG((png_structp png_ptr,
   png_bytep data, png_size_t length));

extern PNG_EXPORT(void,png_write_chunk_end) PNGARG((png_structp png_ptr));

extern PNG_EXPORT(png_infop,png_create_info_struct)
   PNGARG((png_structp png_ptr)) PNG_ALLOCATED;

#if defined(PNG_1_0_X) || defined (PNG_1_2_X)
extern PNG_EXPORT(void,png_info_init) PNGARG((png_infop info_ptr))
    PNG_DEPRECATED;
#undef png_info_init
#define png_info_init(info_ptr) png_info_init_3(&info_ptr,\
    png_sizeof(png_info));
#endif

extern PNG_EXPORT(void,png_info_init_3) PNGARG((png_infopp info_ptr,
    png_size_t png_info_struct_size));

extern PNG_EXPORT(void,png_write_info_before_PLTE) PNGARG((png_structp png_ptr,
   png_infop info_ptr));
extern PNG_EXPORT(void,png_write_info) PNGARG((png_structp png_ptr,
   png_infop info_ptr));

#ifdef PNG_SEQUENTIAL_READ_SUPPORTED
extern PNG_EXPORT(void,png_read_info) PNGARG((png_structp png_ptr,
   png_infop info_ptr));
#endif

#ifdef PNG_TIME_RFC1123_SUPPORTED
extern PNG_EXPORT(png_charp,png_convert_to_rfc1123)
   PNGARG((png_structp png_ptr, png_timep ptime));
#endif

#ifdef PNG_CONVERT_tIME_SUPPORTED
extern PNG_EXPORT(void,png_convert_from_struct_tm) PNGARG((png_timep ptime,
   struct tm FAR * ttime));

extern PNG_EXPORT(void,png_convert_from_time_t) PNGARG((png_timep ptime,
   time_t ttime));
#endif 

#ifdef PNG_READ_EXPAND_SUPPORTED
extern PNG_EXPORT(void,png_set_expand) PNGARG((png_structp png_ptr));
#ifndef PNG_1_0_X
extern PNG_EXPORT(void,png_set_expand_gray_1_2_4_to_8) PNGARG((png_structp
  png_ptr));
#endif
extern PNG_EXPORT(void,png_set_palette_to_rgb) PNGARG((png_structp png_ptr));
extern PNG_EXPORT(void,png_set_tRNS_to_alpha) PNGARG((png_structp png_ptr));
#if defined(PNG_1_0_X) || defined (PNG_1_2_X)
extern PNG_EXPORT(void,png_set_gray_1_2_4_to_8) PNGARG((png_structp
    png_ptr)) PNG_DEPRECATED;
#endif
#endif

#if defined(PNG_READ_BGR_SUPPORTED) || defined(PNG_WRITE_BGR_SUPPORTED)
extern PNG_EXPORT(void,png_set_bgr) PNGARG((png_structp png_ptr));
#endif

#ifdef PNG_READ_GRAY_TO_RGB_SUPPORTED
extern PNG_EXPORT(void,png_set_gray_to_rgb) PNGARG((png_structp png_ptr));
#endif

#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_rgb_to_gray) PNGARG((png_structp png_ptr,
   int error_action, double red, double green ));
#endif
extern PNG_EXPORT(void,png_set_rgb_to_gray_fixed) PNGARG((png_structp png_ptr,
   int error_action, png_fixed_point red, png_fixed_point green ));
extern PNG_EXPORT(png_byte,png_get_rgb_to_gray_status) PNGARG((png_structp
   png_ptr));
#endif

extern PNG_EXPORT(void,png_build_grayscale_palette) PNGARG((int bit_depth,
   png_colorp palette));

#ifdef PNG_READ_STRIP_ALPHA_SUPPORTED
extern PNG_EXPORT(void,png_set_strip_alpha) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_SWAP_ALPHA_SUPPORTED) || \
    defined(PNG_WRITE_SWAP_ALPHA_SUPPORTED)
extern PNG_EXPORT(void,png_set_swap_alpha) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_INVERT_ALPHA_SUPPORTED) || \
    defined(PNG_WRITE_INVERT_ALPHA_SUPPORTED)
extern PNG_EXPORT(void,png_set_invert_alpha) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_FILLER_SUPPORTED) || defined(PNG_WRITE_FILLER_SUPPORTED)
extern PNG_EXPORT(void,png_set_filler) PNGARG((png_structp png_ptr,
   png_uint_32 filler, int flags));
#define PNG_FILLER_BEFORE 0
#define PNG_FILLER_AFTER 1
#ifndef PNG_1_0_X
extern PNG_EXPORT(void,png_set_add_alpha) PNGARG((png_structp png_ptr,
   png_uint_32 filler, int flags));
#endif
#endif 

#if defined(PNG_READ_SWAP_SUPPORTED) || defined(PNG_WRITE_SWAP_SUPPORTED)
extern PNG_EXPORT(void,png_set_swap) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_PACK_SUPPORTED) || defined(PNG_WRITE_PACK_SUPPORTED)
extern PNG_EXPORT(void,png_set_packing) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_PACKSWAP_SUPPORTED) || defined(PNG_WRITE_PACKSWAP_SUPPORTED)
extern PNG_EXPORT(void,png_set_packswap) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_SHIFT_SUPPORTED) || defined(PNG_WRITE_SHIFT_SUPPORTED)
extern PNG_EXPORT(void,png_set_shift) PNGARG((png_structp png_ptr,
   png_color_8p true_bits));
#endif

#if defined(PNG_READ_INTERLACING_SUPPORTED) || \
    defined(PNG_WRITE_INTERLACING_SUPPORTED)
extern PNG_EXPORT(int,png_set_interlace_handling) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_INVERT_SUPPORTED) || defined(PNG_WRITE_INVERT_SUPPORTED)
extern PNG_EXPORT(void,png_set_invert_mono) PNGARG((png_structp png_ptr));
#endif

#ifdef PNG_READ_BACKGROUND_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_background) PNGARG((png_structp png_ptr,
   png_color_16p background_color, int background_gamma_code,
   int need_expand, double background_gamma));
#endif
#define PNG_BACKGROUND_GAMMA_UNKNOWN 0
#define PNG_BACKGROUND_GAMMA_SCREEN  1
#define PNG_BACKGROUND_GAMMA_FILE    2
#define PNG_BACKGROUND_GAMMA_UNIQUE  3
#endif

#ifdef PNG_READ_16_TO_8_SUPPORTED
extern PNG_EXPORT(void,png_set_strip_16) PNGARG((png_structp png_ptr));
#endif

#ifdef PNG_READ_DITHER_SUPPORTED
extern PNG_EXPORT(void,png_set_dither) PNGARG((png_structp png_ptr,
   png_colorp palette, int num_palette, int maximum_colors,
   png_uint_16p histogram, int full_dither));
#endif

#ifdef PNG_READ_GAMMA_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_gamma) PNGARG((png_structp png_ptr,
   double screen_gamma, double default_file_gamma));
#endif
#endif

#if defined(PNG_1_0_X) || defined (PNG_1_2_X)
#if defined(PNG_READ_EMPTY_PLTE_SUPPORTED) || \
    defined(PNG_WRITE_EMPTY_PLTE_SUPPORTED)
extern PNG_EXPORT(void,png_permit_empty_plte) PNGARG((png_structp png_ptr,
   int empty_plte_permitted)) PNG_DEPRECATED;
#endif
#endif

#ifdef PNG_WRITE_FLUSH_SUPPORTED
extern PNG_EXPORT(void,png_set_flush) PNGARG((png_structp png_ptr, int nrows));
extern PNG_EXPORT(void,png_write_flush) PNGARG((png_structp png_ptr));
#endif

extern PNG_EXPORT(void,png_start_read_image) PNGARG((png_structp png_ptr));

extern PNG_EXPORT(void,png_read_update_info) PNGARG((png_structp png_ptr,
   png_infop info_ptr));

#ifndef PNG_NO_SEQUENTIAL_READ_SUPPORTED
extern PNG_EXPORT(void,png_read_rows) PNGARG((png_structp png_ptr,
   png_bytepp row, png_bytepp display_row, png_uint_32 num_rows));
#endif

#ifndef PNG_NO_SEQUENTIAL_READ_SUPPORTED
extern PNG_EXPORT(void,png_read_row) PNGARG((png_structp png_ptr,
   png_bytep row,
   png_bytep display_row));
#endif

#ifndef PNG_NO_SEQUENTIAL_READ_SUPPORTED
extern PNG_EXPORT(void,png_read_image) PNGARG((png_structp png_ptr,
   png_bytepp image));
#endif

extern PNG_EXPORT(void,png_write_row) PNGARG((png_structp png_ptr,
   png_bytep row));

extern PNG_EXPORT(void,png_write_rows) PNGARG((png_structp png_ptr,
   png_bytepp row, png_uint_32 num_rows));

extern PNG_EXPORT(void,png_write_image) PNGARG((png_structp png_ptr,
   png_bytepp image));

extern PNG_EXPORT(void,png_write_end) PNGARG((png_structp png_ptr,
   png_infop info_ptr));

#ifndef PNG_NO_SEQUENTIAL_READ_SUPPORTED
extern PNG_EXPORT(void,png_read_end) PNGARG((png_structp png_ptr,
   png_infop info_ptr));
#endif

extern PNG_EXPORT(void,png_destroy_info_struct) PNGARG((png_structp png_ptr,
   png_infopp info_ptr_ptr));

extern PNG_EXPORT(void,png_destroy_read_struct) PNGARG((png_structpp
   png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr));

extern void png_read_destroy PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_infop end_info_ptr)) PNG_DEPRECATED;

extern PNG_EXPORT(void,png_destroy_write_struct)
   PNGARG((png_structpp png_ptr_ptr, png_infopp info_ptr_ptr));

extern void png_write_destroy PNGARG((png_structp png_ptr)) PNG_DEPRECATED;

extern PNG_EXPORT(void,png_set_crc_action) PNGARG((png_structp png_ptr,
   int crit_action, int ancil_action));

#define PNG_CRC_DEFAULT       0  
#define PNG_CRC_ERROR_QUIT    1  
#define PNG_CRC_WARN_DISCARD  2  
#define PNG_CRC_WARN_USE      3  
#define PNG_CRC_QUIET_USE     4  
#define PNG_CRC_NO_CHANGE     5  


extern PNG_EXPORT(void,png_set_filter) PNGARG((png_structp png_ptr, int method,
   int filters));

#define PNG_NO_FILTERS     0x00
#define PNG_FILTER_NONE    0x08
#define PNG_FILTER_SUB     0x10
#define PNG_FILTER_UP      0x20
#define PNG_FILTER_AVG     0x40
#define PNG_FILTER_PAETH   0x80
#define PNG_ALL_FILTERS (PNG_FILTER_NONE | PNG_FILTER_SUB | PNG_FILTER_UP | \
                         PNG_FILTER_AVG | PNG_FILTER_PAETH)

#define PNG_FILTER_VALUE_NONE  0
#define PNG_FILTER_VALUE_SUB   1
#define PNG_FILTER_VALUE_UP    2
#define PNG_FILTER_VALUE_AVG   3
#define PNG_FILTER_VALUE_PAETH 4
#define PNG_FILTER_VALUE_LAST  5

#if defined(PNG_WRITE_WEIGHTED_FILTER_SUPPORTED) 
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_filter_heuristics) PNGARG((png_structp png_ptr,
   int heuristic_method, int num_weights, png_doublep filter_weights,
   png_doublep filter_costs));
#endif
#endif 

#define PNG_FILTER_HEURISTIC_DEFAULT    0  
#define PNG_FILTER_HEURISTIC_UNWEIGHTED 1  
#define PNG_FILTER_HEURISTIC_WEIGHTED   2  
#define PNG_FILTER_HEURISTIC_LAST       3  

extern PNG_EXPORT(void,png_set_compression_level) PNGARG((png_structp png_ptr,
   int level));

extern PNG_EXPORT(void,png_set_compression_mem_level)
   PNGARG((png_structp png_ptr, int mem_level));

extern PNG_EXPORT(void,png_set_compression_strategy)
   PNGARG((png_structp png_ptr, int strategy));

extern PNG_EXPORT(void,png_set_compression_window_bits)
   PNGARG((png_structp png_ptr, int window_bits));

extern PNG_EXPORT(void,png_set_compression_method) PNGARG((png_structp png_ptr,
   int method));


#ifdef PNG_STDIO_SUPPORTED
extern PNG_EXPORT(void,png_init_io) PNGARG((png_structp png_ptr, png_FILE_p fp));
#endif


extern PNG_EXPORT(void,png_set_error_fn) PNGARG((png_structp png_ptr,
   png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn));

extern PNG_EXPORT(png_voidp,png_get_error_ptr) PNGARG((png_structp png_ptr));

extern PNG_EXPORT(void,png_set_write_fn) PNGARG((png_structp png_ptr,
   png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn));

extern PNG_EXPORT(void,png_set_read_fn) PNGARG((png_structp png_ptr,
   png_voidp io_ptr, png_rw_ptr read_data_fn));

extern PNG_EXPORT(png_voidp,png_get_io_ptr) PNGARG((png_structp png_ptr));

extern PNG_EXPORT(void,png_set_read_status_fn) PNGARG((png_structp png_ptr,
   png_read_status_ptr read_row_fn));

extern PNG_EXPORT(void,png_set_write_status_fn) PNGARG((png_structp png_ptr,
   png_write_status_ptr write_row_fn));

#ifdef PNG_USER_MEM_SUPPORTED
extern PNG_EXPORT(void,png_set_mem_fn) PNGARG((png_structp png_ptr,
   png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn));
extern PNG_EXPORT(png_voidp,png_get_mem_ptr) PNGARG((png_structp png_ptr));
#endif

#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
extern PNG_EXPORT(void,png_set_read_user_transform_fn) PNGARG((png_structp
   png_ptr, png_user_transform_ptr read_user_transform_fn));
#endif

#if defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
extern PNG_EXPORT(void,png_set_write_user_transform_fn) PNGARG((png_structp
   png_ptr, png_user_transform_ptr write_user_transform_fn));
#endif

#if defined(PNG_READ_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_WRITE_USER_TRANSFORM_SUPPORTED) || \
    defined(PNG_LEGACY_SUPPORTED)
extern PNG_EXPORT(void,png_set_user_transform_info) PNGARG((png_structp
   png_ptr, png_voidp user_transform_ptr, int user_transform_depth,
   int user_transform_channels));
extern PNG_EXPORT(png_voidp,png_get_user_transform_ptr)
   PNGARG((png_structp png_ptr));
#endif

#ifdef PNG_USER_CHUNKS_SUPPORTED
extern PNG_EXPORT(void,png_set_read_user_chunk_fn) PNGARG((png_structp png_ptr,
   png_voidp user_chunk_ptr, png_user_chunk_ptr read_user_chunk_fn));
extern PNG_EXPORT(png_voidp,png_get_user_chunk_ptr) PNGARG((png_structp
   png_ptr));
#endif

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
extern PNG_EXPORT(void,png_set_progressive_read_fn) PNGARG((png_structp png_ptr,
   png_voidp progressive_ptr,
   png_progressive_info_ptr info_fn, png_progressive_row_ptr row_fn,
   png_progressive_end_ptr end_fn));

extern PNG_EXPORT(png_voidp,png_get_progressive_ptr)
   PNGARG((png_structp png_ptr));

extern PNG_EXPORT(void,png_process_data) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_bytep buffer, png_size_t buffer_size));

extern PNG_EXPORT(void,png_progressive_combine_row) PNGARG((png_structp png_ptr,
   png_bytep old_row, png_bytep new_row));
#endif 

extern PNG_EXPORT(png_voidp,png_malloc) PNGARG((png_structp png_ptr,
   png_uint_32 size)) PNG_ALLOCATED;

#ifdef PNG_1_0_X
#  define png_malloc_warn png_malloc
#else
extern PNG_EXPORT(png_voidp,png_malloc_warn) PNGARG((png_structp png_ptr,
   png_uint_32 size)) PNG_ALLOCATED;
#endif

extern PNG_EXPORT(void,png_free) PNGARG((png_structp png_ptr, png_voidp ptr));

#ifdef PNG_1_0_X
extern PNG_EXPORT(voidpf,png_zalloc) PNGARG((voidpf png_ptr, uInt items,
   uInt size));

extern PNG_EXPORT(void,png_zfree) PNGARG((voidpf png_ptr, voidpf ptr));
#endif

extern PNG_EXPORT(void,png_free_data) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 free_me, int num));
#ifdef PNG_FREE_ME_SUPPORTED
extern PNG_EXPORT(void,png_data_freer) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int freer, png_uint_32 mask));
#endif
#define PNG_DESTROY_WILL_FREE_DATA 1
#define PNG_SET_WILL_FREE_DATA 1
#define PNG_USER_WILL_FREE_DATA 2
#define PNG_FREE_HIST 0x0008
#define PNG_FREE_ICCP 0x0010
#define PNG_FREE_SPLT 0x0020
#define PNG_FREE_ROWS 0x0040
#define PNG_FREE_PCAL 0x0080
#define PNG_FREE_SCAL 0x0100
#define PNG_FREE_UNKN 0x0200
#define PNG_FREE_LIST 0x0400
#define PNG_FREE_PLTE 0x1000
#define PNG_FREE_TRNS 0x2000
#define PNG_FREE_TEXT 0x4000
#define PNG_FREE_ALL  0x7fff
#define PNG_FREE_MUL  0x4220 

#ifdef PNG_USER_MEM_SUPPORTED
extern PNG_EXPORT(png_voidp,png_malloc_default) PNGARG((png_structp png_ptr,
   png_uint_32 size)) PNG_ALLOCATED;
extern PNG_EXPORT(void,png_free_default) PNGARG((png_structp png_ptr,
   png_voidp ptr));
#endif

extern PNG_EXPORT(png_voidp,png_memcpy_check) PNGARG((png_structp png_ptr,
   png_voidp s1, png_voidp s2, png_uint_32 size)) PNG_DEPRECATED;

extern PNG_EXPORT(png_voidp,png_memset_check) PNGARG((png_structp png_ptr,
   png_voidp s1, int value, png_uint_32 size)) PNG_DEPRECATED;

#if defined(USE_FAR_KEYWORD)  
extern void *png_far_to_near PNGARG((png_structp png_ptr,png_voidp ptr,
   int check));
#endif 

#ifndef PNG_NO_ERROR_TEXT
extern PNG_EXPORT(void,png_error) PNGARG((png_structp png_ptr,
   png_const_charp error_message)) PNG_NORETURN;

extern PNG_EXPORT(void,png_chunk_error) PNGARG((png_structp png_ptr,
   png_const_charp error_message)) PNG_NORETURN;
#else
extern PNG_EXPORT(void,png_err) PNGARG((png_structp png_ptr)) PNG_NORETURN;
#endif

#ifndef PNG_NO_WARNINGS
extern PNG_EXPORT(void,png_warning) PNGARG((png_structp png_ptr,
   png_const_charp warning_message));

#ifdef PNG_READ_SUPPORTED
extern PNG_EXPORT(void,png_chunk_warning) PNGARG((png_structp png_ptr,
   png_const_charp warning_message));
#endif 
#endif 

extern PNG_EXPORT(png_uint_32,png_get_valid) PNGARG((png_structp png_ptr,
png_infop info_ptr, png_uint_32 flag));

extern PNG_EXPORT(png_uint_32,png_get_rowbytes) PNGARG((png_structp png_ptr,
png_infop info_ptr));

#ifdef PNG_INFO_IMAGE_SUPPORTED
extern PNG_EXPORT(png_bytepp,png_get_rows) PNGARG((png_structp png_ptr,
png_infop info_ptr));
extern PNG_EXPORT(void,png_set_rows) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_bytepp row_pointers));
#endif

extern PNG_EXPORT(png_byte,png_get_channels) PNGARG((png_structp png_ptr,
png_infop info_ptr));

#ifdef PNG_EASY_ACCESS_SUPPORTED
extern PNG_EXPORT(png_uint_32, png_get_image_width) PNGARG((png_structp
png_ptr, png_infop info_ptr));

extern PNG_EXPORT(png_uint_32, png_get_image_height) PNGARG((png_structp
png_ptr, png_infop info_ptr));

extern PNG_EXPORT(png_byte, png_get_bit_depth) PNGARG((png_structp
png_ptr, png_infop info_ptr));

extern PNG_EXPORT(png_byte, png_get_color_type) PNGARG((png_structp
png_ptr, png_infop info_ptr));

extern PNG_EXPORT(png_byte, png_get_filter_type) PNGARG((png_structp
png_ptr, png_infop info_ptr));

extern PNG_EXPORT(png_byte, png_get_interlace_type) PNGARG((png_structp
png_ptr, png_infop info_ptr));

extern PNG_EXPORT(png_byte, png_get_compression_type) PNGARG((png_structp
png_ptr, png_infop info_ptr));

extern PNG_EXPORT(png_uint_32, png_get_pixels_per_meter) PNGARG((png_structp
png_ptr, png_infop info_ptr));
extern PNG_EXPORT(png_uint_32, png_get_x_pixels_per_meter) PNGARG((png_structp
png_ptr, png_infop info_ptr));
extern PNG_EXPORT(png_uint_32, png_get_y_pixels_per_meter) PNGARG((png_structp
png_ptr, png_infop info_ptr));

#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(float, png_get_pixel_aspect_ratio) PNGARG((png_structp
png_ptr, png_infop info_ptr));
#endif

extern PNG_EXPORT(png_int_32, png_get_x_offset_pixels) PNGARG((png_structp
png_ptr, png_infop info_ptr));
extern PNG_EXPORT(png_int_32, png_get_y_offset_pixels) PNGARG((png_structp
png_ptr, png_infop info_ptr));
extern PNG_EXPORT(png_int_32, png_get_x_offset_microns) PNGARG((png_structp
png_ptr, png_infop info_ptr));
extern PNG_EXPORT(png_int_32, png_get_y_offset_microns) PNGARG((png_structp
png_ptr, png_infop info_ptr));

#endif 

extern PNG_EXPORT(png_bytep,png_get_signature) PNGARG((png_structp png_ptr,
png_infop info_ptr));

#ifdef PNG_bKGD_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_bKGD) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_color_16p *background));
#endif

#ifdef PNG_bKGD_SUPPORTED
extern PNG_EXPORT(void,png_set_bKGD) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_color_16p background));
#endif

#ifdef PNG_cHRM_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_cHRM) PNGARG((png_structp png_ptr,
   png_infop info_ptr, double *white_x, double *white_y, double *red_x,
   double *red_y, double *green_x, double *green_y, double *blue_x,
   double *blue_y));
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_cHRM_fixed) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_fixed_point *int_white_x, png_fixed_point
   *int_white_y, png_fixed_point *int_red_x, png_fixed_point *int_red_y,
   png_fixed_point *int_green_x, png_fixed_point *int_green_y, png_fixed_point
   *int_blue_x, png_fixed_point *int_blue_y));
#endif
#endif

#ifdef PNG_cHRM_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_cHRM) PNGARG((png_structp png_ptr,
   png_infop info_ptr, double white_x, double white_y, double red_x,
   double red_y, double green_x, double green_y, double blue_x, double blue_y));
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_cHRM_fixed) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_fixed_point int_white_x, png_fixed_point int_white_y,
   png_fixed_point int_red_x, png_fixed_point int_red_y, png_fixed_point
   int_green_x, png_fixed_point int_green_y, png_fixed_point int_blue_x,
   png_fixed_point int_blue_y));
#endif
#endif

#ifdef PNG_gAMA_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_gAMA) PNGARG((png_structp png_ptr,
   png_infop info_ptr, double *file_gamma));
#endif
extern PNG_EXPORT(png_uint_32,png_get_gAMA_fixed) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_fixed_point *int_file_gamma));
#endif

#ifdef PNG_gAMA_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_gAMA) PNGARG((png_structp png_ptr,
   png_infop info_ptr, double file_gamma));
#endif
extern PNG_EXPORT(void,png_set_gAMA_fixed) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_fixed_point int_file_gamma));
#endif

#ifdef PNG_hIST_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_hIST) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_16p *hist));
#endif

#ifdef PNG_hIST_SUPPORTED
extern PNG_EXPORT(void,png_set_hIST) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_16p hist));
#endif

extern PNG_EXPORT(png_uint_32,png_get_IHDR) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 *width, png_uint_32 *height,
   int *bit_depth, int *color_type, int *interlace_method,
   int *compression_method, int *filter_method));

extern PNG_EXPORT(void,png_set_IHDR) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth,
   int color_type, int interlace_method, int compression_method,
   int filter_method));

#ifdef PNG_oFFs_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_oFFs) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_int_32 *offset_x, png_int_32 *offset_y,
   int *unit_type));
#endif

#ifdef PNG_oFFs_SUPPORTED
extern PNG_EXPORT(void,png_set_oFFs) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_int_32 offset_x, png_int_32 offset_y,
   int unit_type));
#endif

#ifdef PNG_pCAL_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_pCAL) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_charp *purpose, png_int_32 *X0, png_int_32 *X1,
   int *type, int *nparams, png_charp *units, png_charpp *params));
#endif

#ifdef PNG_pCAL_SUPPORTED
extern PNG_EXPORT(void,png_set_pCAL) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_charp purpose, png_int_32 X0, png_int_32 X1,
   int type, int nparams, png_charp units, png_charpp params));
#endif

#ifdef PNG_pHYs_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_pHYs) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 *res_x, png_uint_32 *res_y, int *unit_type));
#endif

#ifdef PNG_pHYs_SUPPORTED
extern PNG_EXPORT(void,png_set_pHYs) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 res_x, png_uint_32 res_y, int unit_type));
#endif

extern PNG_EXPORT(png_uint_32,png_get_PLTE) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_colorp *palette, int *num_palette));

extern PNG_EXPORT(void,png_set_PLTE) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_colorp palette, int num_palette));

#ifdef PNG_sBIT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_sBIT) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_color_8p *sig_bit));
#endif

#ifdef PNG_sBIT_SUPPORTED
extern PNG_EXPORT(void,png_set_sBIT) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_color_8p sig_bit));
#endif

#ifdef PNG_sRGB_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_sRGB) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int *intent));
#endif

#ifdef PNG_sRGB_SUPPORTED
extern PNG_EXPORT(void,png_set_sRGB) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int intent));
extern PNG_EXPORT(void,png_set_sRGB_gAMA_and_cHRM) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int intent));
#endif

#ifdef PNG_iCCP_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_iCCP) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_charpp name, int *compression_type,
   png_charpp profile, png_uint_32 *proflen));
   
#endif

#ifdef PNG_iCCP_SUPPORTED
extern PNG_EXPORT(void,png_set_iCCP) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_charp name, int compression_type,
   png_charp profile, png_uint_32 proflen));
   
#endif

#ifdef PNG_sPLT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_sPLT) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_sPLT_tpp entries));
#endif

#ifdef PNG_sPLT_SUPPORTED
extern PNG_EXPORT(void,png_set_sPLT) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_sPLT_tp entries, int nentries));
#endif

#ifdef PNG_TEXT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_text) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_textp *text_ptr, int *num_text));
#endif


#ifdef PNG_TEXT_SUPPORTED
extern PNG_EXPORT(void,png_set_text) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_textp text_ptr, int num_text));
#endif

#ifdef PNG_tIME_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_tIME) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_timep *mod_time));
#endif

#ifdef PNG_tIME_SUPPORTED
extern PNG_EXPORT(void,png_set_tIME) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_timep mod_time));
#endif

#ifdef PNG_tRNS_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_tRNS) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_bytep *trans, int *num_trans,
   png_color_16p *trans_values));
#endif

#ifdef PNG_tRNS_SUPPORTED
extern PNG_EXPORT(void,png_set_tRNS) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_bytep trans, int num_trans,
   png_color_16p trans_values));
#endif

#ifdef PNG_tRNS_SUPPORTED
#endif

#ifdef PNG_sCAL_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_sCAL) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int *unit, double *width, double *height));
#else
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_get_sCAL_s) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int *unit, png_charpp swidth, png_charpp sheight));
#endif
#endif
#endif 

#ifdef PNG_sCAL_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_sCAL) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int unit, double width, double height));
#else
#ifdef PNG_FIXED_POINT_SUPPORTED
extern PNG_EXPORT(void,png_set_sCAL_s) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int unit, png_charp swidth, png_charp sheight));
#endif
#endif
#endif 

#ifdef PNG_HANDLE_AS_UNKNOWN_SUPPORTED
extern PNG_EXPORT(void, png_set_keep_unknown_chunks) PNGARG((png_structp
   png_ptr, int keep, png_bytep chunk_list, int num_chunks));
PNG_EXPORT(int,png_handle_as_unknown) PNGARG((png_structp png_ptr, png_bytep
   chunk_name));
#endif
#ifdef PNG_UNKNOWN_CHUNKS_SUPPORTED
extern PNG_EXPORT(void, png_set_unknown_chunks) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_unknown_chunkp unknowns, int num_unknowns));
extern PNG_EXPORT(void, png_set_unknown_chunk_location)
   PNGARG((png_structp png_ptr, png_infop info_ptr, int chunk, int location));
extern PNG_EXPORT(png_uint_32,png_get_unknown_chunks) PNGARG((png_structp
   png_ptr, png_infop info_ptr, png_unknown_chunkpp entries));
#endif

extern PNG_EXPORT(void, png_set_invalid) PNGARG((png_structp png_ptr,
   png_infop info_ptr, int mask));

#ifdef PNG_INFO_IMAGE_SUPPORTED
extern PNG_EXPORT(void, png_read_png) PNGARG((png_structp png_ptr,
                        png_infop info_ptr,
                        int transforms,
                        png_voidp params));
extern PNG_EXPORT(void, png_write_png) PNGARG((png_structp png_ptr,
                        png_infop info_ptr,
                        int transforms,
                        png_voidp params));
#endif

#ifdef PNG_DEBUG
#if (PNG_DEBUG > 0)
#if !defined(PNG_DEBUG_FILE) && defined(_MSC_VER)
#include <crtdbg.h>
#if (PNG_DEBUG > 1)
#ifndef _DEBUG
#  define _DEBUG
#endif
#ifndef png_debug
#define png_debug(l,m)  _RPT0(_CRT_WARN,m PNG_STRING_NEWLINE)
#endif
#ifndef png_debug1
#define png_debug1(l,m,p1)  _RPT1(_CRT_WARN,m PNG_STRING_NEWLINE,p1)
#endif
#ifndef png_debug2
#define png_debug2(l,m,p1,p2) _RPT2(_CRT_WARN,m PNG_STRING_NEWLINE,p1,p2)
#endif
#endif
#else 
#ifndef PNG_DEBUG_FILE
#define PNG_DEBUG_FILE stderr
#endif 

#if (PNG_DEBUG > 1)
#  ifdef __STDC__
#    ifndef png_debug
#      define png_debug(l,m) \
       { \
       int num_tabs=l; \
       fprintf(PNG_DEBUG_FILE,"%s"m PNG_STRING_NEWLINE,(num_tabs==1 ? "\t" : \
         (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":"")))); \
       }
#    endif
#    ifndef png_debug1
#      define png_debug1(l,m,p1) \
       { \
       int num_tabs=l; \
       fprintf(PNG_DEBUG_FILE,"%s"m PNG_STRING_NEWLINE,(num_tabs==1 ? "\t" : \
         (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":""))),p1); \
       }
#    endif
#    ifndef png_debug2
#      define png_debug2(l,m,p1,p2) \
       { \
       int num_tabs=l; \
       fprintf(PNG_DEBUG_FILE,"%s"m PNG_STRING_NEWLINE,(num_tabs==1 ? "\t" : \
         (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":""))),p1,p2); \
       }
#    endif
#  else 
#    ifndef png_debug
#      define png_debug(l,m) \
       { \
       int num_tabs=l; \
       char format[256]; \
       snprintf(format,256,"%s%s%s",(num_tabs==1 ? "\t" : \
         (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":""))), \
         m,PNG_STRING_NEWLINE); \
       fprintf(PNG_DEBUG_FILE,format); \
       }
#    endif
#    ifndef png_debug1
#      define png_debug1(l,m,p1) \
       { \
       int num_tabs=l; \
       char format[256]; \
       snprintf(format,256,"%s%s%s",(num_tabs==1 ? "\t" : \
         (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":""))), \
         m,PNG_STRING_NEWLINE); \
       fprintf(PNG_DEBUG_FILE,format,p1); \
       }
#    endif
#    ifndef png_debug2
#      define png_debug2(l,m,p1,p2) \
       { \
       int num_tabs=l; \
       char format[256]; \
       snprintf(format,256,"%s%s%s",(num_tabs==1 ? "\t" : \
         (num_tabs==2 ? "\t\t":(num_tabs>2 ? "\t\t\t":""))), \
         m,PNG_STRING_NEWLINE); \
       fprintf(PNG_DEBUG_FILE,format,p1,p2); \
       }
#    endif
#  endif 
#endif 

#endif 
#endif 
#endif 
#ifndef png_debug
#define png_debug(l, m)
#endif
#ifndef png_debug1
#define png_debug1(l, m, p1)
#endif
#ifndef png_debug2
#define png_debug2(l, m, p1, p2)
#endif

extern PNG_EXPORT(png_charp,png_get_copyright) PNGARG((png_structp png_ptr));
extern PNG_EXPORT(png_charp,png_get_header_ver) PNGARG((png_structp png_ptr));
extern PNG_EXPORT(png_charp,png_get_header_version) PNGARG((png_structp png_ptr));
extern PNG_EXPORT(png_charp,png_get_libpng_ver) PNGARG((png_structp png_ptr));

#ifdef PNG_MNG_FEATURES_SUPPORTED
extern PNG_EXPORT(png_uint_32,png_permit_mng_features) PNGARG((png_structp
   png_ptr, png_uint_32 mng_features_permitted));
#endif

#define PNG_HANDLE_CHUNK_AS_DEFAULT   0
#define PNG_HANDLE_CHUNK_NEVER        1
#define PNG_HANDLE_CHUNK_IF_SAFE      2
#define PNG_HANDLE_CHUNK_ALWAYS       3

#ifdef PNG_ASSEMBLER_CODE_SUPPORTED
#ifdef PNG_MMX_CODE_SUPPORTED
#define PNG_ASM_FLAG_MMX_SUPPORT_COMPILED  0x01  
#define PNG_ASM_FLAG_MMX_SUPPORT_IN_CPU    0x02  
#define PNG_ASM_FLAG_MMX_READ_COMBINE_ROW  0x04
#define PNG_ASM_FLAG_MMX_READ_INTERLACE    0x08
#define PNG_ASM_FLAG_MMX_READ_FILTER_SUB   0x10
#define PNG_ASM_FLAG_MMX_READ_FILTER_UP    0x20
#define PNG_ASM_FLAG_MMX_READ_FILTER_AVG   0x40
#define PNG_ASM_FLAG_MMX_READ_FILTER_PAETH 0x80
#define PNG_ASM_FLAGS_INITIALIZED          0x80000000  

#define PNG_MMX_READ_FLAGS ( PNG_ASM_FLAG_MMX_READ_COMBINE_ROW  \
                           | PNG_ASM_FLAG_MMX_READ_INTERLACE    \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_SUB   \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_UP    \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_AVG   \
                           | PNG_ASM_FLAG_MMX_READ_FILTER_PAETH )
#define PNG_MMX_WRITE_FLAGS ( 0 )

#define PNG_MMX_FLAGS ( PNG_ASM_FLAG_MMX_SUPPORT_COMPILED \
                      | PNG_ASM_FLAG_MMX_SUPPORT_IN_CPU   \
                      | PNG_MMX_READ_FLAGS                \
                      | PNG_MMX_WRITE_FLAGS )

#define PNG_SELECT_READ   1
#define PNG_SELECT_WRITE  2
#endif 

#ifndef PNG_1_0_X
extern PNG_EXPORT(png_uint_32,png_get_mmx_flagmask)
   PNGARG((int flag_select, int *compilerID));

extern PNG_EXPORT(png_uint_32,png_get_asm_flagmask)
   PNGARG((int flag_select));

extern PNG_EXPORT(png_uint_32,png_get_asm_flags)
   PNGARG((png_structp png_ptr));

extern PNG_EXPORT(png_byte,png_get_mmx_bitdepth_threshold)
   PNGARG((png_structp png_ptr));

extern PNG_EXPORT(png_uint_32,png_get_mmx_rowbytes_threshold)
   PNGARG((png_structp png_ptr));

extern PNG_EXPORT(void,png_set_asm_flags)
   PNGARG((png_structp png_ptr, png_uint_32 asm_flags));

extern PNG_EXPORT(void,png_set_mmx_thresholds)
   PNGARG((png_structp png_ptr, png_byte mmx_bitdepth_threshold,
   png_uint_32 mmx_rowbytes_threshold));

#endif 

#ifndef PNG_1_0_X
extern PNG_EXPORT(int,png_mmx_support) PNGARG((void));
#endif 
#endif 

#ifdef PNG_ERROR_NUMBERS_SUPPORTED
extern PNG_EXPORT(void,png_set_strip_error_numbers) PNGARG((png_structp
   png_ptr, png_uint_32 strip_mode));
#endif

#ifdef PNG_SET_USER_LIMITS_SUPPORTED
extern PNG_EXPORT(void,png_set_user_limits) PNGARG((png_structp
   png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max));
extern PNG_EXPORT(png_uint_32,png_get_user_width_max) PNGARG((png_structp
   png_ptr));
extern PNG_EXPORT(png_uint_32,png_get_user_height_max) PNGARG((png_structp
   png_ptr));
#endif

#ifdef PNG_READ_COMPOSITE_NODIV_SUPPORTED

 

#  define png_composite(composite, fg, alpha, bg)                            \
     { png_uint_16 temp = (png_uint_16)((png_uint_16)(fg) * (png_uint_16)(alpha) \
                        +        (png_uint_16)(bg)*(png_uint_16)(255 -       \
                        (png_uint_16)(alpha)) + (png_uint_16)128);           \
       (composite) = (png_byte)((temp + (temp >> 8)) >> 8); }

#  define png_composite_16(composite, fg, alpha, bg)                         \
     { png_uint_32 temp = (png_uint_32)((png_uint_32)(fg) * (png_uint_32)(alpha) \
                        + (png_uint_32)(bg)*(png_uint_32)(65535L -           \
                        (png_uint_32)(alpha)) + (png_uint_32)32768L);        \
       (composite) = (png_uint_16)((temp + (temp >> 16)) >> 16); }

#else  

#  define png_composite(composite, fg, alpha, bg)                            \
     (composite) = (png_byte)(((png_uint_16)(fg) * (png_uint_16)(alpha) +    \
       (png_uint_16)(bg) * (png_uint_16)(255 - (png_uint_16)(alpha)) +       \
       (png_uint_16)127) / 255)

#  define png_composite_16(composite, fg, alpha, bg)                         \
     (composite) = (png_uint_16)(((png_uint_32)(fg) * (png_uint_32)(alpha) + \
       (png_uint_32)(bg)*(png_uint_32)(65535L - (png_uint_32)(alpha)) +      \
       (png_uint_32)32767) / (png_uint_32)65535L)

#endif 

#ifdef PNG_READ_BIG_ENDIAN_SUPPORTED
#  define png_get_uint_32(buf) ( *((png_uint_32p) (buf)))
#  define png_get_uint_16(buf) ( *((png_uint_16p) (buf)))
#  define png_get_int_32(buf)  ( *((png_int_32p)  (buf)))
#else
extern PNG_EXPORT(png_uint_32,png_get_uint_32) PNGARG((png_bytep buf));
extern PNG_EXPORT(png_uint_16,png_get_uint_16) PNGARG((png_bytep buf));
extern PNG_EXPORT(png_int_32,png_get_int_32) PNGARG((png_bytep buf));
#endif 
extern PNG_EXPORT(png_uint_32,png_get_uint_31)
  PNGARG((png_structp png_ptr, png_bytep buf));

extern PNG_EXPORT(void,png_save_uint_32)
   PNGARG((png_bytep buf, png_uint_32 i));
extern PNG_EXPORT(void,png_save_int_32)
   PNGARG((png_bytep buf, png_int_32 i));

extern PNG_EXPORT(void,png_save_uint_16)
   PNGARG((png_bytep buf, unsigned int i));




#define PNG_HAVE_IHDR               0x01
#define PNG_HAVE_PLTE               0x02
#define PNG_HAVE_IDAT               0x04
#define PNG_AFTER_IDAT              0x08 
#define PNG_HAVE_IEND               0x10

#ifdef PNG_INTERNAL

#define PNG_HAVE_gAMA               0x20
#define PNG_HAVE_cHRM               0x40
#define PNG_HAVE_sRGB               0x80
#define PNG_HAVE_CHUNK_HEADER      0x100
#define PNG_WROTE_tIME             0x200
#define PNG_WROTE_INFO_BEFORE_PLTE 0x400
#define PNG_BACKGROUND_IS_GRAY     0x800
#define PNG_HAVE_PNG_SIGNATURE    0x1000
#define PNG_HAVE_CHUNK_AFTER_IDAT 0x2000 

#define PNG_BGR                0x0001
#define PNG_INTERLACE          0x0002
#define PNG_PACK               0x0004
#define PNG_SHIFT              0x0008
#define PNG_SWAP_BYTES         0x0010
#define PNG_INVERT_MONO        0x0020
#define PNG_DITHER             0x0040
#define PNG_BACKGROUND         0x0080
#define PNG_BACKGROUND_EXPAND  0x0100
                          
#define PNG_16_TO_8            0x0400
#define PNG_RGBA               0x0800
#define PNG_EXPAND             0x1000
#define PNG_GAMMA              0x2000
#define PNG_GRAY_TO_RGB        0x4000
#define PNG_FILLER             0x8000L
#define PNG_PACKSWAP          0x10000L
#define PNG_SWAP_ALPHA        0x20000L
#define PNG_STRIP_ALPHA       0x40000L
#define PNG_INVERT_ALPHA      0x80000L
#define PNG_USER_TRANSFORM   0x100000L
#define PNG_RGB_TO_GRAY_ERR  0x200000L
#define PNG_RGB_TO_GRAY_WARN 0x400000L
#define PNG_RGB_TO_GRAY      0x600000L  
                       
#define PNG_ADD_ALPHA       0x1000000L  
#define PNG_EXPAND_tRNS     0x2000000L  
#define PNG_PREMULTIPLY_ALPHA 0x4000000L  
                                          
                       
                       
                       
                       

#define PNG_STRUCT_PNG   0x0001
#define PNG_STRUCT_INFO  0x0002

#define PNG_WEIGHT_SHIFT 8
#define PNG_WEIGHT_FACTOR (1<<(PNG_WEIGHT_SHIFT))
#define PNG_COST_SHIFT 3
#define PNG_COST_FACTOR (1<<(PNG_COST_SHIFT))

#define PNG_FLAG_ZLIB_CUSTOM_STRATEGY     0x0001
#define PNG_FLAG_ZLIB_CUSTOM_LEVEL        0x0002
#define PNG_FLAG_ZLIB_CUSTOM_MEM_LEVEL    0x0004
#define PNG_FLAG_ZLIB_CUSTOM_WINDOW_BITS  0x0008
#define PNG_FLAG_ZLIB_CUSTOM_METHOD       0x0010
#define PNG_FLAG_ZLIB_FINISHED            0x0020
#define PNG_FLAG_ROW_INIT                 0x0040
#define PNG_FLAG_FILLER_AFTER             0x0080
#define PNG_FLAG_CRC_ANCILLARY_USE        0x0100
#define PNG_FLAG_CRC_ANCILLARY_NOWARN     0x0200
#define PNG_FLAG_CRC_CRITICAL_USE         0x0400
#define PNG_FLAG_CRC_CRITICAL_IGNORE      0x0800
#define PNG_FLAG_FREE_PLTE                0x1000
#define PNG_FLAG_FREE_TRNS                0x2000
#define PNG_FLAG_FREE_HIST                0x4000
#define PNG_FLAG_KEEP_UNKNOWN_CHUNKS      0x8000L
#define PNG_FLAG_KEEP_UNSAFE_CHUNKS       0x10000L
#define PNG_FLAG_LIBRARY_MISMATCH         0x20000L
#define PNG_FLAG_STRIP_ERROR_NUMBERS      0x40000L
#define PNG_FLAG_STRIP_ERROR_TEXT         0x80000L
#define PNG_FLAG_MALLOC_NULL_MEM_OK       0x100000L
#define PNG_FLAG_ADD_ALPHA                0x200000L  
#define PNG_FLAG_STRIP_ALPHA              0x400000L  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  

#define PNG_FLAG_CRC_ANCILLARY_MASK (PNG_FLAG_CRC_ANCILLARY_USE | \
                                     PNG_FLAG_CRC_ANCILLARY_NOWARN)

#define PNG_FLAG_CRC_CRITICAL_MASK  (PNG_FLAG_CRC_CRITICAL_USE | \
                                     PNG_FLAG_CRC_CRITICAL_IGNORE)

#define PNG_FLAG_CRC_MASK           (PNG_FLAG_CRC_ANCILLARY_MASK | \
                                     PNG_FLAG_CRC_CRITICAL_MASK)


#define PNG_COLOR_DIST(c1, c2) (abs((int)((c1).red) - (int)((c2).red)) + \
   abs((int)((c1).green) - (int)((c2).green)) + \
   abs((int)((c1).blue) - (int)((c2).blue)))

#define PNG_ROWBYTES(pixel_bits, width) \
    ((pixel_bits) >= 8 ? \
    ((width) * (((png_uint_32)(pixel_bits)) >> 3)) : \
    (( ((width) * ((png_uint_32)(pixel_bits))) + 7) >> 3) )

#define PNG_OUT_OF_RANGE(value, ideal, delta) \
        ( (value) < (ideal)-(delta) || (value) > (ideal)+(delta) )

#if !defined(PNG_NO_EXTERN) || defined(PNG_ALWAYS_EXTERN)
#ifdef PNG_USE_GLOBAL_ARRAYS
   PNG_EXPORT_VAR (PNG_CONST png_byte FARDATA) png_sig[8];
#else
#endif
#endif 

#define PNG_IHDR png_byte png_IHDR[5] = { 73,  72,  68,  82, '\0'}
#define PNG_IDAT png_byte png_IDAT[5] = { 73,  68,  65,  84, '\0'}
#define PNG_IEND png_byte png_IEND[5] = { 73,  69,  78,  68, '\0'}
#define PNG_PLTE png_byte png_PLTE[5] = { 80,  76,  84,  69, '\0'}
#define PNG_bKGD png_byte png_bKGD[5] = { 98,  75,  71,  68, '\0'}
#define PNG_cHRM png_byte png_cHRM[5] = { 99,  72,  82,  77, '\0'}
#define PNG_gAMA png_byte png_gAMA[5] = {103,  65,  77,  65, '\0'}
#define PNG_hIST png_byte png_hIST[5] = {104,  73,  83,  84, '\0'}
#define PNG_iCCP png_byte png_iCCP[5] = {105,  67,  67,  80, '\0'}
#define PNG_iTXt png_byte png_iTXt[5] = {105,  84,  88, 116, '\0'}
#define PNG_oFFs png_byte png_oFFs[5] = {111,  70,  70, 115, '\0'}
#define PNG_pCAL png_byte png_pCAL[5] = {112,  67,  65,  76, '\0'}
#define PNG_sCAL png_byte png_sCAL[5] = {115,  67,  65,  76, '\0'}
#define PNG_pHYs png_byte png_pHYs[5] = {112,  72,  89, 115, '\0'}
#define PNG_sBIT png_byte png_sBIT[5] = {115,  66,  73,  84, '\0'}
#define PNG_sPLT png_byte png_sPLT[5] = {115,  80,  76,  84, '\0'}
#define PNG_sRGB png_byte png_sRGB[5] = {115,  82,  71,  66, '\0'}
#define PNG_tEXt png_byte png_tEXt[5] = {116,  69,  88, 116, '\0'}
#define PNG_tIME png_byte png_tIME[5] = {116,  73,  77,  69, '\0'}
#define PNG_tRNS png_byte png_tRNS[5] = {116,  82,  78,  83, '\0'}
#define PNG_zTXt png_byte png_zTXt[5] = {122,  84,  88, 116, '\0'}

#ifdef PNG_USE_GLOBAL_ARRAYS
PNG_EXPORT_VAR (png_byte FARDATA) png_IHDR[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_IDAT[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_IEND[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_PLTE[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_bKGD[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_cHRM[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_gAMA[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_hIST[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_iCCP[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_iTXt[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_oFFs[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_pCAL[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_sCAL[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_pHYs[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_sBIT[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_sPLT[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_sRGB[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_tEXt[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_tIME[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_tRNS[5];
PNG_EXPORT_VAR (png_byte FARDATA) png_zTXt[5];
#endif 

#if defined(PNG_1_0_X) || defined (PNG_1_2_X)
extern PNG_EXPORT(void,png_read_init) PNGARG((png_structp png_ptr))
    PNG_DEPRECATED;
#undef png_read_init
#define png_read_init(png_ptr) png_read_init_3(&png_ptr, \
    PNG_LIBPNG_VER_STRING,  png_sizeof(png_struct));
#endif

extern PNG_EXPORT(void,png_read_init_3) PNGARG((png_structpp ptr_ptr,
    png_const_charp user_png_ver, png_size_t png_struct_size));
#if defined(PNG_1_0_X) || defined (PNG_1_2_X)
extern PNG_EXPORT(void,png_read_init_2) PNGARG((png_structp png_ptr,
    png_const_charp user_png_ver, png_size_t png_struct_size, png_size_t
    png_info_size));
#endif

#if defined(PNG_1_0_X) || defined (PNG_1_2_X)
extern PNG_EXPORT(void,png_write_init) PNGARG((png_structp png_ptr))
    PNG_DEPRECATED;
#undef png_write_init
#define png_write_init(png_ptr) png_write_init_3(&png_ptr, \
    PNG_LIBPNG_VER_STRING, png_sizeof(png_struct));
#endif

extern PNG_EXPORT(void,png_write_init_3) PNGARG((png_structpp ptr_ptr,
    png_const_charp user_png_ver, png_size_t png_struct_size));
extern PNG_EXPORT(void,png_write_init_2) PNGARG((png_structp png_ptr,
    png_const_charp user_png_ver, png_size_t png_struct_size, png_size_t
    png_info_size));

PNG_EXTERN png_voidp png_create_struct PNGARG((int type)) PNG_PRIVATE;

PNG_EXTERN void png_destroy_struct PNGARG((png_voidp struct_ptr)) PNG_PRIVATE;

PNG_EXTERN png_voidp png_create_struct_2 PNGARG((int type, png_malloc_ptr
  malloc_fn, png_voidp mem_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_destroy_struct_2 PNGARG((png_voidp struct_ptr,
   png_free_ptr free_fn, png_voidp mem_ptr)) PNG_PRIVATE;

PNG_EXTERN void png_info_destroy PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;

#ifndef PNG_1_0_X
PNG_EXTERN voidpf png_zalloc PNGARG((voidpf png_ptr, uInt items,
   uInt size)) PNG_PRIVATE;

PNG_EXTERN void png_zfree PNGARG((voidpf png_ptr, voidpf ptr)) PNG_PRIVATE;

#ifdef PNG_SIZE_T
   PNG_EXTERN png_size_t PNGAPI png_convert_size PNGARG((size_t size))
      PNG_PRIVATE;
#endif


PNG_EXTERN void PNGAPI png_default_read_data PNGARG((png_structp png_ptr,
   png_bytep data, png_size_t length)) PNG_PRIVATE;

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
PNG_EXTERN void PNGAPI png_push_fill_buffer PNGARG((png_structp png_ptr,
   png_bytep buffer, png_size_t length)) PNG_PRIVATE;
#endif

PNG_EXTERN void PNGAPI png_default_write_data PNGARG((png_structp png_ptr,
   png_bytep data, png_size_t length)) PNG_PRIVATE;

#ifdef PNG_WRITE_FLUSH_SUPPORTED
#ifdef PNG_STDIO_SUPPORTED
PNG_EXTERN void PNGAPI png_default_flush PNGARG((png_structp png_ptr))
   PNG_PRIVATE;
#endif
#endif
#else 
#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
PNG_EXTERN void png_push_fill_buffer PNGARG((png_structp png_ptr,
   png_bytep buffer, png_size_t length)) PNG_PRIVATE;
#endif
#endif 

PNG_EXTERN void png_reset_crc PNGARG((png_structp png_ptr)) PNG_PRIVATE;

PNG_EXTERN void png_write_data PNGARG((png_structp png_ptr, png_bytep data,
   png_size_t length)) PNG_PRIVATE;

PNG_EXTERN void png_read_data PNGARG((png_structp png_ptr, png_bytep data,
   png_size_t length)) PNG_PRIVATE;

PNG_EXTERN void png_crc_read PNGARG((png_structp png_ptr, png_bytep buf,
   png_size_t length)) PNG_PRIVATE;

#if defined(PNG_zTXt_SUPPORTED) || defined(PNG_iTXt_SUPPORTED) || \
    defined(PNG_iCCP_SUPPORTED) || defined(PNG_sPLT_SUPPORTED)
PNG_EXTERN void png_decompress_chunk PNGARG((png_structp png_ptr,
   int comp_type, png_size_t chunklength,
   png_size_t prefix_length, png_size_t *data_length)) PNG_PRIVATE;
#endif

PNG_EXTERN int png_crc_finish PNGARG((png_structp png_ptr, png_uint_32 skip)
   PNG_PRIVATE);

PNG_EXTERN int png_crc_error PNGARG((png_structp png_ptr)) PNG_PRIVATE;

/* Calculate the CRC over a section of data.  Note that we are only
 * passing a maximum of 64K on systems that have this as a memory limit,
 * since this is the maximum buffer size we can specify.
 */
PNG_EXTERN void png_calculate_crc PNGARG((png_structp png_ptr, png_bytep ptr,
   png_size_t length)) PNG_PRIVATE;

#ifdef PNG_WRITE_FLUSH_SUPPORTED
PNG_EXTERN void png_flush PNGARG((png_structp png_ptr)) PNG_PRIVATE;
#endif

PNG_EXTERN void png_write_sig PNGARG((png_structp png_ptr)) PNG_PRIVATE;


PNG_EXTERN void png_write_IHDR PNGARG((png_structp png_ptr, png_uint_32 width,
   png_uint_32 height,
   int bit_depth, int color_type, int compression_method, int filter_method,
   int interlace_method)) PNG_PRIVATE;

PNG_EXTERN void png_write_PLTE PNGARG((png_structp png_ptr, png_colorp palette,
   png_uint_32 num_pal)) PNG_PRIVATE;

PNG_EXTERN void png_write_IDAT PNGARG((png_structp png_ptr, png_bytep data,
   png_size_t length)) PNG_PRIVATE;

PNG_EXTERN void png_write_IEND PNGARG((png_structp png_ptr)) PNG_PRIVATE;

#ifdef PNG_WRITE_gAMA_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
PNG_EXTERN void png_write_gAMA PNGARG((png_structp png_ptr, double file_gamma))
    PNG_PRIVATE;
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
PNG_EXTERN void png_write_gAMA_fixed PNGARG((png_structp png_ptr,
    png_fixed_point file_gamma)) PNG_PRIVATE;
#endif
#endif

#ifdef PNG_WRITE_sBIT_SUPPORTED
PNG_EXTERN void png_write_sBIT PNGARG((png_structp png_ptr, png_color_8p sbit,
   int color_type)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_cHRM_SUPPORTED
#ifdef PNG_FLOATING_POINT_SUPPORTED
PNG_EXTERN void png_write_cHRM PNGARG((png_structp png_ptr,
   double white_x, double white_y,
   double red_x, double red_y, double green_x, double green_y,
   double blue_x, double blue_y)) PNG_PRIVATE;
#endif
#ifdef PNG_FIXED_POINT_SUPPORTED
PNG_EXTERN void png_write_cHRM_fixed PNGARG((png_structp png_ptr,
   png_fixed_point int_white_x, png_fixed_point int_white_y,
   png_fixed_point int_red_x, png_fixed_point int_red_y, png_fixed_point
   int_green_x, png_fixed_point int_green_y, png_fixed_point int_blue_x,
   png_fixed_point int_blue_y)) PNG_PRIVATE;
#endif
#endif

#ifdef PNG_WRITE_sRGB_SUPPORTED
PNG_EXTERN void png_write_sRGB PNGARG((png_structp png_ptr,
   int intent)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_iCCP_SUPPORTED
PNG_EXTERN void png_write_iCCP PNGARG((png_structp png_ptr,
   png_charp name, int compression_type,
   png_charp profile, int proflen)) PNG_PRIVATE;
   
#endif

#ifdef PNG_WRITE_sPLT_SUPPORTED
PNG_EXTERN void png_write_sPLT PNGARG((png_structp png_ptr,
   png_sPLT_tp palette)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_tRNS_SUPPORTED
PNG_EXTERN void png_write_tRNS PNGARG((png_structp png_ptr, png_bytep trans,
   png_color_16p values, int number, int color_type)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_bKGD_SUPPORTED
PNG_EXTERN void png_write_bKGD PNGARG((png_structp png_ptr,
   png_color_16p values, int color_type)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_hIST_SUPPORTED
PNG_EXTERN void png_write_hIST PNGARG((png_structp png_ptr, png_uint_16p hist,
   int num_hist)) PNG_PRIVATE;
#endif

#if defined(PNG_WRITE_TEXT_SUPPORTED) || defined(PNG_WRITE_pCAL_SUPPORTED) || \
    defined(PNG_WRITE_iCCP_SUPPORTED) || defined(PNG_WRITE_sPLT_SUPPORTED)
PNG_EXTERN png_size_t png_check_keyword PNGARG((png_structp png_ptr,
   png_charp key, png_charpp new_key)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_tEXt_SUPPORTED
PNG_EXTERN void png_write_tEXt PNGARG((png_structp png_ptr, png_charp key,
   png_charp text, png_size_t text_len)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_zTXt_SUPPORTED
PNG_EXTERN void png_write_zTXt PNGARG((png_structp png_ptr, png_charp key,
   png_charp text, png_size_t text_len, int compression)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_iTXt_SUPPORTED
PNG_EXTERN void png_write_iTXt PNGARG((png_structp png_ptr,
   int compression, png_charp key, png_charp lang, png_charp lang_key,
   png_charp text)) PNG_PRIVATE;
#endif

#ifdef PNG_TEXT_SUPPORTED  
PNG_EXTERN int png_set_text_2 PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_textp text_ptr, int num_text)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_oFFs_SUPPORTED
PNG_EXTERN void png_write_oFFs PNGARG((png_structp png_ptr,
   png_int_32 x_offset, png_int_32 y_offset, int unit_type)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_pCAL_SUPPORTED
PNG_EXTERN void png_write_pCAL PNGARG((png_structp png_ptr, png_charp purpose,
   png_int_32 X0, png_int_32 X1, int type, int nparams,
   png_charp units, png_charpp params)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_pHYs_SUPPORTED
PNG_EXTERN void png_write_pHYs PNGARG((png_structp png_ptr,
   png_uint_32 x_pixels_per_unit, png_uint_32 y_pixels_per_unit,
   int unit_type)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_tIME_SUPPORTED
PNG_EXTERN void png_write_tIME PNGARG((png_structp png_ptr,
   png_timep mod_time)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_sCAL_SUPPORTED
#if defined(PNG_FLOATING_POINT_SUPPORTED) && !defined(PNG_NO_STDIO)
PNG_EXTERN void png_write_sCAL PNGARG((png_structp png_ptr,
   int unit, double width, double height)) PNG_PRIVATE;
#else
#ifdef PNG_FIXED_POINT_SUPPORTED
PNG_EXTERN void png_write_sCAL_s PNGARG((png_structp png_ptr,
   int unit, png_charp width, png_charp height)) PNG_PRIVATE;
#endif
#endif
#endif

PNG_EXTERN void png_write_finish_row PNGARG((png_structp png_ptr)) PNG_PRIVATE;

PNG_EXTERN void png_write_start_row PNGARG((png_structp png_ptr)) PNG_PRIVATE;

#ifdef PNG_READ_GAMMA_SUPPORTED
PNG_EXTERN void png_build_gamma_table PNGARG((png_structp png_ptr)) PNG_PRIVATE;
#endif

PNG_EXTERN void png_combine_row PNGARG((png_structp png_ptr, png_bytep row,
   int mask)) PNG_PRIVATE;

#ifdef PNG_READ_INTERLACING_SUPPORTED
PNG_EXTERN void png_do_read_interlace PNGARG((png_structp png_ptr)) PNG_PRIVATE;
#endif


#ifdef PNG_WRITE_INTERLACING_SUPPORTED
PNG_EXTERN void png_do_write_interlace PNGARG((png_row_infop row_info,
   png_bytep row, int pass)) PNG_PRIVATE;
#endif

PNG_EXTERN void png_read_filter_row PNGARG((png_structp png_ptr,
   png_row_infop row_info, png_bytep row, png_bytep prev_row,
   int filter)) PNG_PRIVATE;

PNG_EXTERN void png_write_find_filter PNGARG((png_structp png_ptr,
   png_row_infop row_info)) PNG_PRIVATE;

PNG_EXTERN void png_write_filtered_row PNGARG((png_structp png_ptr,
   png_bytep filtered_row)) PNG_PRIVATE;
PNG_EXTERN void png_read_finish_row PNGARG((png_structp png_ptr));

PNG_EXTERN void png_read_start_row PNGARG((png_structp png_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_read_transform_info PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;

#ifdef PNG_READ_FILLER_SUPPORTED
PNG_EXTERN void png_do_read_filler PNGARG((png_row_infop row_info,
   png_bytep row, png_uint_32 filler, png_uint_32 flags)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_SWAP_ALPHA_SUPPORTED
PNG_EXTERN void png_do_read_swap_alpha PNGARG((png_row_infop row_info,
   png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_SWAP_ALPHA_SUPPORTED
PNG_EXTERN void png_do_write_swap_alpha PNGARG((png_row_infop row_info,
   png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_INVERT_ALPHA_SUPPORTED
PNG_EXTERN void png_do_read_invert_alpha PNGARG((png_row_infop row_info,
   png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_INVERT_ALPHA_SUPPORTED
PNG_EXTERN void png_do_write_invert_alpha PNGARG((png_row_infop row_info,
   png_bytep row)) PNG_PRIVATE;
#endif

#if defined(PNG_WRITE_FILLER_SUPPORTED) || \
    defined(PNG_READ_STRIP_ALPHA_SUPPORTED)
PNG_EXTERN void png_do_strip_filler PNGARG((png_row_infop row_info,
   png_bytep row, png_uint_32 flags)) PNG_PRIVATE;
#endif

#if defined(PNG_READ_SWAP_SUPPORTED) || defined(PNG_WRITE_SWAP_SUPPORTED)
PNG_EXTERN void png_do_swap PNGARG((png_row_infop row_info,
    png_bytep row)) PNG_PRIVATE;
#endif

#if defined(PNG_READ_PACKSWAP_SUPPORTED) || defined(PNG_WRITE_PACKSWAP_SUPPORTED)
PNG_EXTERN void png_do_packswap PNGARG((png_row_infop row_info,
    png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_RGB_TO_GRAY_SUPPORTED
PNG_EXTERN int png_do_rgb_to_gray PNGARG((png_structp png_ptr, png_row_infop
   row_info, png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_GRAY_TO_RGB_SUPPORTED
PNG_EXTERN void png_do_gray_to_rgb PNGARG((png_row_infop row_info,
   png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_PACK_SUPPORTED
PNG_EXTERN void png_do_unpack PNGARG((png_row_infop row_info,
    png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_SHIFT_SUPPORTED
PNG_EXTERN void png_do_unshift PNGARG((png_row_infop row_info, png_bytep row,
   png_color_8p sig_bits)) PNG_PRIVATE;
#endif

#if defined(PNG_READ_INVERT_SUPPORTED) || defined(PNG_WRITE_INVERT_SUPPORTED)
PNG_EXTERN void png_do_invert PNGARG((png_row_infop row_info,
    png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_16_TO_8_SUPPORTED
PNG_EXTERN void png_do_chop PNGARG((png_row_infop row_info,
    png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_DITHER_SUPPORTED
PNG_EXTERN void png_do_dither PNGARG((png_row_infop row_info,
   png_bytep row, png_bytep palette_lookup,
    png_bytep dither_lookup)) PNG_PRIVATE;

#  ifdef PNG_CORRECT_PALETTE_SUPPORTED
PNG_EXTERN void png_correct_palette PNGARG((png_structp png_ptr,
   png_colorp palette, int num_palette)) PNG_PRIVATE;
#  endif
#endif

#if defined(PNG_READ_BGR_SUPPORTED) || defined(PNG_WRITE_BGR_SUPPORTED)
PNG_EXTERN void png_do_bgr PNGARG((png_row_infop row_info,
    png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_PACK_SUPPORTED
PNG_EXTERN void png_do_pack PNGARG((png_row_infop row_info,
   png_bytep row, png_uint_32 bit_depth)) PNG_PRIVATE;
#endif

#ifdef PNG_WRITE_SHIFT_SUPPORTED
PNG_EXTERN void png_do_shift PNGARG((png_row_infop row_info, png_bytep row,
   png_color_8p bit_depth)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_BACKGROUND_SUPPORTED
#ifdef PNG_READ_GAMMA_SUPPORTED
PNG_EXTERN void png_do_background PNGARG((png_row_infop row_info, png_bytep row,
   png_color_16p trans_values, png_color_16p background,
   png_color_16p background_1,
   png_bytep gamma_table, png_bytep gamma_from_1, png_bytep gamma_to_1,
   png_uint_16pp gamma_16, png_uint_16pp gamma_16_from_1,
   png_uint_16pp gamma_16_to_1, int gamma_shift)) PNG_PRIVATE;
#else
PNG_EXTERN void png_do_background PNGARG((png_row_infop row_info, png_bytep row,
   png_color_16p trans_values, png_color_16p background)) PNG_PRIVATE;
#endif
#endif

#ifdef PNG_READ_GAMMA_SUPPORTED
PNG_EXTERN void png_do_gamma PNGARG((png_row_infop row_info, png_bytep row,
   png_bytep gamma_table, png_uint_16pp gamma_16_table,
   int gamma_shift)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_EXPAND_SUPPORTED
PNG_EXTERN void png_do_expand_palette PNGARG((png_row_infop row_info,
   png_bytep row, png_colorp palette, png_bytep trans,
   int num_trans)) PNG_PRIVATE;
PNG_EXTERN void png_do_expand PNGARG((png_row_infop row_info,
   png_bytep row, png_color_16p trans_value)) PNG_PRIVATE;
#endif


PNG_EXTERN void png_handle_IHDR PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
PNG_EXTERN void png_handle_PLTE PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));
PNG_EXTERN void png_handle_IEND PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));

#ifdef PNG_READ_bKGD_SUPPORTED
PNG_EXTERN void png_handle_bKGD PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_cHRM_SUPPORTED
PNG_EXTERN void png_handle_cHRM PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_gAMA_SUPPORTED
PNG_EXTERN void png_handle_gAMA PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_hIST_SUPPORTED
PNG_EXTERN void png_handle_hIST PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_iCCP_SUPPORTED
extern void png_handle_iCCP PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length));
#endif 

#ifdef PNG_READ_iTXt_SUPPORTED
PNG_EXTERN void png_handle_iTXt PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_oFFs_SUPPORTED
PNG_EXTERN void png_handle_oFFs PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_pCAL_SUPPORTED
PNG_EXTERN void png_handle_pCAL PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_pHYs_SUPPORTED
PNG_EXTERN void png_handle_pHYs PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_sBIT_SUPPORTED
PNG_EXTERN void png_handle_sBIT PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_sCAL_SUPPORTED
PNG_EXTERN void png_handle_sCAL PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_sPLT_SUPPORTED
extern void png_handle_sPLT PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif 

#ifdef PNG_READ_sRGB_SUPPORTED
PNG_EXTERN void png_handle_sRGB PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_tEXt_SUPPORTED
PNG_EXTERN void png_handle_tEXt PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_tIME_SUPPORTED
PNG_EXTERN void png_handle_tIME PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_tRNS_SUPPORTED
PNG_EXTERN void png_handle_tRNS PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

#ifdef PNG_READ_zTXt_SUPPORTED
PNG_EXTERN void png_handle_zTXt PNGARG((png_structp png_ptr, png_infop info_ptr,
   png_uint_32 length)) PNG_PRIVATE;
#endif

PNG_EXTERN void png_handle_unknown PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 length)) PNG_PRIVATE;

PNG_EXTERN void png_check_chunk_name PNGARG((png_structp png_ptr,
   png_bytep chunk_name)) PNG_PRIVATE;

PNG_EXTERN void png_do_read_transformations
   PNGARG((png_structp png_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_do_write_transformations
   PNGARG((png_structp png_ptr)) PNG_PRIVATE;

PNG_EXTERN void png_init_read_transformations
   PNGARG((png_structp png_ptr)) PNG_PRIVATE;

#ifdef PNG_PROGRESSIVE_READ_SUPPORTED
PNG_EXTERN void png_push_read_chunk PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_read_sig PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_check_crc PNGARG((png_structp png_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_crc_skip PNGARG((png_structp png_ptr,
   png_uint_32 length)) PNG_PRIVATE;
PNG_EXTERN void png_push_crc_finish PNGARG((png_structp png_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_save_buffer PNGARG((png_structp png_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_restore_buffer PNGARG((png_structp png_ptr,
   png_bytep buffer, png_size_t buffer_length)) PNG_PRIVATE;
PNG_EXTERN void png_push_read_IDAT PNGARG((png_structp png_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_process_IDAT_data PNGARG((png_structp png_ptr,
   png_bytep buffer, png_size_t buffer_length)) PNG_PRIVATE;
PNG_EXTERN void png_push_process_row PNGARG((png_structp png_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_handle_unknown PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 length)) PNG_PRIVATE;
PNG_EXTERN void png_push_have_info PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_have_end PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_push_have_row PNGARG((png_structp png_ptr,
   png_bytep row)) PNG_PRIVATE;
PNG_EXTERN void png_push_read_end PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_process_some_data PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
PNG_EXTERN void png_read_push_finish_row
   PNGARG((png_structp png_ptr)) PNG_PRIVATE;
#ifdef PNG_READ_tEXt_SUPPORTED
PNG_EXTERN void png_push_handle_tEXt PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 length)) PNG_PRIVATE;
PNG_EXTERN void png_push_read_tEXt PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
#endif
#ifdef PNG_READ_zTXt_SUPPORTED
PNG_EXTERN void png_push_handle_zTXt PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 length)) PNG_PRIVATE;
PNG_EXTERN void png_push_read_zTXt PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
#endif
#ifdef PNG_READ_iTXt_SUPPORTED
PNG_EXTERN void png_push_handle_iTXt PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_uint_32 length)) PNG_PRIVATE;
PNG_EXTERN void png_push_read_iTXt PNGARG((png_structp png_ptr,
   png_infop info_ptr)) PNG_PRIVATE;
#endif

#endif 

#ifdef PNG_MNG_FEATURES_SUPPORTED
PNG_EXTERN void png_do_read_intrapixel PNGARG((png_row_infop row_info,
   png_bytep row)) PNG_PRIVATE;
PNG_EXTERN void png_do_write_intrapixel PNGARG((png_row_infop row_info,
   png_bytep row)) PNG_PRIVATE;
#endif

#ifdef PNG_ASSEMBLER_CODE_SUPPORTED
#ifdef PNG_MMX_CODE_SUPPORTED
 
PNG_EXTERN void png_init_mmx_flags PNGARG((png_structp png_ptr)) PNG_PRIVATE;
#endif
#endif


#if defined(PNG_INCH_CONVERSIONS) && defined(PNG_FLOATING_POINT_SUPPORTED)
PNG_EXTERN png_uint_32 png_get_pixels_per_inch PNGARG((png_structp png_ptr,
png_infop info_ptr));

PNG_EXTERN png_uint_32 png_get_x_pixels_per_inch PNGARG((png_structp png_ptr,
png_infop info_ptr));

PNG_EXTERN png_uint_32 png_get_y_pixels_per_inch PNGARG((png_structp png_ptr,
png_infop info_ptr));

PNG_EXTERN float png_get_x_offset_inches PNGARG((png_structp png_ptr,
png_infop info_ptr));

PNG_EXTERN float png_get_y_offset_inches PNGARG((png_structp png_ptr,
png_infop info_ptr));

#ifdef PNG_pHYs_SUPPORTED
PNG_EXTERN png_uint_32 png_get_pHYs_dpi PNGARG((png_structp png_ptr,
png_infop info_ptr, png_uint_32 *res_x, png_uint_32 *res_y, int *unit_type));
#endif 
#endif  

PNG_EXTERN png_uint_32 png_read_chunk_header
   PNGARG((png_structp png_ptr)) PNG_PRIVATE;

#ifdef PNG_cHRM_SUPPORTED
PNG_EXTERN int png_check_cHRM_fixed PNGARG((png_structp png_ptr,
   png_fixed_point int_white_x, png_fixed_point int_white_y,
   png_fixed_point int_red_x, png_fixed_point int_red_y, png_fixed_point
   int_green_x, png_fixed_point int_green_y, png_fixed_point int_blue_x,
   png_fixed_point int_blue_y)) PNG_PRIVATE;
#endif

#ifdef PNG_cHRM_SUPPORTED
#ifdef PNG_CHECK_cHRM_SUPPORTED
PNG_EXTERN void png_64bit_product PNGARG((long v1, long v2,
   unsigned long *hi_product, unsigned long *lo_product)) PNG_PRIVATE;
#endif
#endif

PNG_EXTERN void png_check_IHDR PNGARG((png_structp png_ptr,
   png_uint_32 width, png_uint_32 height, int bit_depth,
   int color_type, int interlace_type, int compression_type,
   int filter_type)) PNG_PRIVATE;

PNG_EXTERN png_voidp png_calloc PNGARG((png_structp png_ptr,
   png_uint_32 size));


#endif 

#ifdef __cplusplus
}
#endif

#endif 
#endif 
