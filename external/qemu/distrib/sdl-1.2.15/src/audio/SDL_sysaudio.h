/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is SDL_free software; you can redistribute it and/or
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

#ifndef _SDL_sysaudio_h
#define _SDL_sysaudio_h

#include "SDL_mutex.h"
#include "SDL_thread.h"

typedef struct SDL_AudioDevice SDL_AudioDevice;

#define _THIS	SDL_AudioDevice *_this
#ifndef _STATUS
#define _STATUS	SDL_status *status
#endif
struct SDL_AudioDevice {
	
	
	const char *name;

	
	
	const char *desc;

	
	
	int  (*OpenAudio)(_THIS, SDL_AudioSpec *spec);
	void (*ThreadInit)(_THIS);	
	void (*WaitAudio)(_THIS);
	void (*PlayAudio)(_THIS);
	Uint8 *(*GetAudioBuf)(_THIS);
	void (*WaitDone)(_THIS);
	void (*CloseAudio)(_THIS);

	
	
	void (*LockAudio)(_THIS);
	void (*UnlockAudio)(_THIS);

	void (*SetCaption)(_THIS, const char *caption);

	
	

	
	SDL_AudioSpec spec;

	
	SDL_AudioCVT convert;

	
	int enabled;
	int paused;
	int opened;

	
	Uint8 *fake_stream;

	
	SDL_mutex *mixer_lock;

	
	SDL_Thread *thread;
	Uint32 threadid;

	
	
	struct SDL_PrivateAudioData *hidden;

	
	
	void (*free)(_THIS);
};
#undef _THIS

typedef struct AudioBootStrap {
	const char *name;
	const char *desc;
	int (*available)(void);
	SDL_AudioDevice *(*create)(int devindex);
} AudioBootStrap;

#if SDL_AUDIO_DRIVER_BSD
extern AudioBootStrap BSD_AUDIO_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_PULSE
extern AudioBootStrap PULSE_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_ALSA
extern AudioBootStrap ALSA_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_OSS
extern AudioBootStrap DSP_bootstrap;
extern AudioBootStrap DMA_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_QNXNTO
extern AudioBootStrap QNXNTOAUDIO_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_SUNAUDIO
extern AudioBootStrap SUNAUDIO_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_DMEDIA
extern AudioBootStrap DMEDIA_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_ARTS
extern AudioBootStrap ARTS_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_ESD
extern AudioBootStrap ESD_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_NAS
extern AudioBootStrap NAS_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_DSOUND
extern AudioBootStrap DSOUND_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_WAVEOUT
extern AudioBootStrap WAVEOUT_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_PAUD
extern AudioBootStrap Paud_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_BAUDIO
extern AudioBootStrap BAUDIO_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_COREAUDIO
extern AudioBootStrap COREAUDIO_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_SNDMGR
extern AudioBootStrap SNDMGR_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_MINT
extern AudioBootStrap MINTAUDIO_GSXB_bootstrap;
extern AudioBootStrap MINTAUDIO_MCSN_bootstrap;
extern AudioBootStrap MINTAUDIO_STFA_bootstrap;
extern AudioBootStrap MINTAUDIO_XBIOS_bootstrap;
extern AudioBootStrap MINTAUDIO_DMA8_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_DISK
extern AudioBootStrap DISKAUD_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_DUMMY
extern AudioBootStrap DUMMYAUD_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_DC
extern AudioBootStrap DCAUD_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_NDS
extern AudioBootStrap NDSAUD_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_MMEAUDIO
extern AudioBootStrap MMEAUDIO_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_DART
extern AudioBootStrap DART_bootstrap;
#endif
#if SDL_AUDIO_DRIVER_EPOCAUDIO
extern AudioBootStrap EPOCAudio_bootstrap; 
#endif

extern SDL_AudioDevice *current_audio;

#endif 