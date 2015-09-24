/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

#ifndef _ATARI_C2P_h
#define _ATARI_C2P_h

#include "SDL_stdinc.h"



extern void (*SDL_Atari_C2pConvert)(
	Uint8 *src,			
	Uint8 *dest,		
	Uint32 width,		
	Uint32 height,
	Uint32 dblligne,	
	Uint32 srcpitch,	
	Uint32 dstpitch		
);



void SDL_Atari_C2pConvert8(
	Uint8 *src,			
	Uint8 *dest,		
	Uint32 width,		
	Uint32 height,
	Uint32 dblligne,	
	Uint32 srcpitch,	
	Uint32 dstpitch		
);



void SDL_Atari_C2pConvert4(
	Uint8 *src,			
	Uint8 *dest,		
	Uint32 width,		
	Uint32 height,
	Uint32 dblligne,	
	Uint32 srcpitch,	
	Uint32 dstpitch		
);


void SDL_Atari_C2pConvert4_pal(Uint16 *lightpalette);

#endif 
