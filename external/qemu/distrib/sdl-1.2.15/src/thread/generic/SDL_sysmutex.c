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


#include "SDL_thread.h"
#include "SDL_systhread_c.h"


struct SDL_mutex {
	int recursive;
	Uint32 owner;
	SDL_sem *sem;
};

SDL_mutex *SDL_CreateMutex(void)
{
	SDL_mutex *mutex;

	
	mutex = (SDL_mutex *)SDL_malloc(sizeof(*mutex));
	if ( mutex ) {
		
		mutex->sem = SDL_CreateSemaphore(1);
		mutex->recursive = 0;
		mutex->owner = 0;
		if ( ! mutex->sem ) {
			SDL_free(mutex);
			mutex = NULL;
		}
	} else {
		SDL_OutOfMemory();
	}
	return mutex;
}

void SDL_DestroyMutex(SDL_mutex *mutex)
{
	if ( mutex ) {
		if ( mutex->sem ) {
			SDL_DestroySemaphore(mutex->sem);
		}
		SDL_free(mutex);
	}
}

int SDL_mutexP(SDL_mutex *mutex)
{
#if SDL_THREADS_DISABLED
	return 0;
#else
	Uint32 this_thread;

	if ( mutex == NULL ) {
		SDL_SetError("Passed a NULL mutex");
		return -1;
	}

	this_thread = SDL_ThreadID();
	if ( mutex->owner == this_thread ) {
		++mutex->recursive;
	} else {
		SDL_SemWait(mutex->sem);
		mutex->owner = this_thread;
		mutex->recursive = 0;
	}

	return 0;
#endif 
}

int SDL_mutexV(SDL_mutex *mutex)
{
#if SDL_THREADS_DISABLED
	return 0;
#else
	if ( mutex == NULL ) {
		SDL_SetError("Passed a NULL mutex");
		return -1;
	}

	
	if ( SDL_ThreadID() != mutex->owner ) {
		SDL_SetError("mutex not owned by this thread");
		return -1;
	}

	if ( mutex->recursive ) {
		--mutex->recursive;
	} else {
		mutex->owner = 0;
		SDL_SemPost(mutex->sem);
	}
	return 0;
#endif 
}