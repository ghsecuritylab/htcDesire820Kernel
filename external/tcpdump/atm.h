/*
 * Copyright (c) 2002 Guy Harris.
 *                All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code
 * distributions retain the above copyright notice and this paragraph
 * in its entirety, and (2) distributions including binary code include
 * the above copyright notice and this paragraph in its entirety in
 * the documentation or other materials provided with the distribution.
 * The name of Guy Harris may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @(#) $Header: /tcpdump/master/tcpdump/atm.h,v 1.1.4.1 2005/06/20 07:45:05 hannes Exp $
 */

#define ATM_UNKNOWN	0	
#define ATM_LANE	1	
#define ATM_LLC		2	

#define ATM_OAM_NOHEC   0
#define ATM_OAM_HEC     1