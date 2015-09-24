

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "SDL.h"

#define FRAME_TICKS	(1000/30)		

static void quit(int rc)
{
	SDL_Quit();
	exit(rc);
}

static void FillBackground(SDL_Surface *screen)
{
	Uint8 *buffer;
	Uint16 *buffer16;
        Uint16 color;
        Uint8  gradient;
	int    i, k;

	
	if ( SDL_LockSurface(screen) < 0 ) {
		fprintf(stderr, "Couldn't lock the display surface: %s\n",
							SDL_GetError());
		quit(2);
	}
	buffer=(Uint8 *)screen->pixels;
	if (screen->format->BytesPerPixel!=2) {
		for ( i=0; i<screen->h; ++i ) {
			memset(buffer,(i*255)/screen->h, screen->w*screen->format->BytesPerPixel);
			buffer += screen->pitch;
		}
	}
        else
        {
		for ( i=0; i<screen->h; ++i ) {
			gradient=((i*255)/screen->h);
                        color = (Uint16)SDL_MapRGB(screen->format, gradient, gradient, gradient);
                        buffer16=(Uint16*)buffer;
                        for (k=0; k<screen->w; k++)
                        {
                            *(buffer16+k)=color;
                        }
			buffer += screen->pitch;
		}
        }

	SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

SDL_Surface *CreateLight(int radius)
{
	Uint8  trans, alphamask;
	int    range, addition;
	int    xdist, ydist;
	Uint16 x, y;
	Uint16 skip;
	Uint32 pixel;
	SDL_Surface *light;

#ifdef LIGHT_16BIT
	Uint16 *buf;

	
	
	alphamask = 0x0000000F;
	light = SDL_CreateRGBSurface(SDL_SWSURFACE, 2*radius, 2*radius, 16,
			0x0000F000, 0x00000F00, 0x000000F0, alphamask);
#else
	Uint32 *buf;

	
	alphamask = 0x000000FF;
	light = SDL_CreateRGBSurface(SDL_SWSURFACE, 2*radius, 2*radius, 32,
			0xFF000000, 0x00FF0000, 0x0000FF00, alphamask);
	if ( light == NULL ) {
		fprintf(stderr, "Couldn't create light: %s\n", SDL_GetError());
		return(NULL);
	}
#endif

	
	skip = light->pitch-(light->w*light->format->BytesPerPixel);
#ifdef LIGHT_16BIT
	buf = (Uint16 *)light->pixels;
#else
	buf = (Uint32 *)light->pixels;
#endif
        
	pixel = SDL_MapRGBA(light->format, 0xFF, 0xDD, 0x88, 0);
	for ( y=0; y<light->h; ++y ) {
		for ( x=0; x<light->w; ++x ) {
			*buf++ = pixel;
		}
		buf += skip;	
	}

	
#ifdef LIGHT_16BIT
	buf = (Uint16 *)light->pixels;
#else
	buf = (Uint32 *)light->pixels;
#endif
	for ( y=0; y<light->h; ++y ) {
		for ( x=0; x<light->w; ++x ) {
			
			xdist = x-(light->w/2);
			ydist = y-(light->h/2);
			range = (int)sqrt(xdist*xdist+ydist*ydist);

			
			if ( range > radius ) {
				trans = alphamask;
			} else {
				
				trans = (Uint8)((range*alphamask)/radius);

				
				addition = (alphamask+1)/8;
				if ( (int)trans+addition > alphamask ) {
					trans = alphamask;
				} else {
					trans += addition;
				}
			}
			
			*buf++ |= (255-trans);
		}
		buf += skip;	
	}
	
	SDL_SetAlpha(light, SDL_SRCALPHA|SDL_RLEACCEL, 0);

	
	return(light);
}

static Uint32 flashes = 0;
static Uint32 flashtime = 0;

void FlashLight(SDL_Surface *screen, SDL_Surface *light, int x, int y)
{
	SDL_Rect position;
	Uint32   ticks1;
	Uint32   ticks2;

	
	position.x = x-(light->w/2);
	position.y = y-(light->h/2);
	position.w = light->w;
	position.h = light->h;
	ticks1 = SDL_GetTicks();
	SDL_BlitSurface(light, NULL, screen, &position);
	ticks2 = SDL_GetTicks();
	SDL_UpdateRects(screen, 1, &position);
	++flashes;

	
	flashtime += (ticks2-ticks1);
}

static int sprite_visible = 0;
static SDL_Surface *sprite;
static SDL_Surface *backing;
static SDL_Rect    position;
static int         x_vel, y_vel;
static int	   alpha_vel;

int LoadSprite(SDL_Surface *screen, char *file)
{
	SDL_Surface *converted;

	
	sprite = SDL_LoadBMP(file);
	if ( sprite == NULL ) {
		fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
		return(-1);
	}

	
	if ( sprite->format->palette ) {
		SDL_SetColorKey(sprite, SDL_SRCCOLORKEY,
						*(Uint8 *)sprite->pixels);
	}

	
	converted = SDL_DisplayFormat(sprite);
	SDL_FreeSurface(sprite);
	if ( converted == NULL ) {
		fprintf(stderr, "Couldn't convert background: %s\n",
							SDL_GetError());
		return(-1);
	}
	sprite = converted;

	
	backing = SDL_CreateRGBSurface(SDL_SWSURFACE, sprite->w, sprite->h, 8,
								0, 0, 0, 0);
	if ( backing == NULL ) {
		fprintf(stderr, "Couldn't create background: %s\n",
							SDL_GetError());
		SDL_FreeSurface(sprite);
		return(-1);
	}

	
	converted = SDL_DisplayFormat(backing);
	SDL_FreeSurface(backing);
	if ( converted == NULL ) {
		fprintf(stderr, "Couldn't convert background: %s\n",
							SDL_GetError());
		SDL_FreeSurface(sprite);
		return(-1);
	}
	backing = converted;

	
	position.x = (screen->w-sprite->w)/2;
	position.y = (screen->h-sprite->h)/2;
	position.w = sprite->w;
	position.h = sprite->h;
	x_vel = 0; y_vel = 0;
	alpha_vel = 1;

	
	return(0);
}

void AttractSprite(Uint16 x, Uint16 y)
{
	x_vel = ((int)x-position.x)/10;
	y_vel = ((int)y-position.y)/10;
}

void MoveSprite(SDL_Surface *screen, SDL_Surface *light)
{
	SDL_Rect updates[2];
	int alpha;

	
	if ( sprite_visible ) {
		updates[0] = position;
		SDL_BlitSurface(backing, NULL, screen, &updates[0]);
	} else {
		updates[0].x = 0; updates[0].y = 0;
		updates[0].w = 0; updates[0].h = 0;
		sprite_visible = 1;
	}

	/* Since the sprite is off the screen, we can do other drawing
	   without being overwritten by the saved area behind the sprite.
	 */
	if ( light != NULL ) {
		int x, y;

		SDL_GetMouseState(&x, &y);
		FlashLight(screen, light, x, y);
	}
	   
	
	position.x += x_vel;
	if ( (position.x < 0) || (position.x >= screen->w) ) {
		x_vel = -x_vel;
		position.x += x_vel;
	}
	position.y += y_vel;
	if ( (position.y < 0) || (position.y >= screen->h) ) {
		y_vel = -y_vel;
		position.y += y_vel;
	}

	
	alpha = sprite->format->alpha;
	if ( (alpha+alpha_vel) < 0 ) {
		alpha_vel = -alpha_vel;
	} else
	if ( (alpha+alpha_vel) > 255 ) {
		alpha_vel = -alpha_vel;
	}
	SDL_SetAlpha(sprite, SDL_SRCALPHA, (Uint8)(alpha+alpha_vel));

	
	updates[1] = position;
	SDL_BlitSurface(screen, &updates[1], backing, NULL);
	
	
	updates[1] = position;
	SDL_BlitSurface(sprite, NULL, screen, &updates[1]);

	
	SDL_UpdateRects(screen, 2, updates);
}

void WarpSprite(SDL_Surface *screen, int x, int y)
{
	SDL_Rect updates[2];

	
	updates[0] = position;
	SDL_BlitSurface(backing, NULL, screen, &updates[0]);
	position.x = x-sprite->w/2;	
	position.y = y-sprite->h/2;	
	updates[1] = position;
	SDL_BlitSurface(screen, &updates[1], backing, NULL);
	updates[1] = position;
	SDL_BlitSurface(sprite, NULL, screen, &updates[1]);
	SDL_UpdateRects(screen, 2, updates);
}

int main(int argc, char *argv[])
{
	const SDL_VideoInfo *info;
	SDL_Surface *screen;
	int    w, h;
	Uint8  video_bpp;
	Uint32 videoflags;
	int    i, done;
	SDL_Event event;
	SDL_Surface *light;
	int mouse_pressed;
	Uint32 ticks, lastticks;


	
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		return(1);
	}

	
#ifdef _WIN32_WCE
	
	w = 240;
	h = 320;
#else
	w = 640;
	h = 480;
#endif
	info = SDL_GetVideoInfo();
	if ( info->vfmt->BitsPerPixel > 8 ) {
		video_bpp = info->vfmt->BitsPerPixel;
	} else {
		video_bpp = 16;
                fprintf(stderr, "forced 16 bpp mode\n");
	}
	videoflags = SDL_SWSURFACE;
	for ( i = 1; argv[i]; ++i ) {
		if ( strcmp(argv[i], "-bpp") == 0 ) {
			video_bpp = atoi(argv[++i]);
                        if (video_bpp<=8) {
                            video_bpp=16;
                            fprintf(stderr, "forced 16 bpp mode\n");
                        }
		} else
		if ( strcmp(argv[i], "-hw") == 0 ) {
			videoflags |= SDL_HWSURFACE;
		} else
		if ( strcmp(argv[i], "-warp") == 0 ) {
			videoflags |= SDL_HWPALETTE;
		} else
		if ( strcmp(argv[i], "-width") == 0 && argv[i+1] ) {
			w = atoi(argv[++i]);
		} else
		if ( strcmp(argv[i], "-height") == 0 && argv[i+1] ) {
			h = atoi(argv[++i]);
		} else
		if ( strcmp(argv[i], "-resize") == 0 ) {
			videoflags |= SDL_RESIZABLE;
		} else
		if ( strcmp(argv[i], "-noframe") == 0 ) {
			videoflags |= SDL_NOFRAME;
		} else
		if ( strcmp(argv[i], "-fullscreen") == 0 ) {
			videoflags |= SDL_FULLSCREEN;
		} else {
			fprintf(stderr, 
			"Usage: %s [-width N] [-height N] [-bpp N] [-warp] [-hw] [-fullscreen]\n",
								argv[0]);
			quit(1);
		}
	}

	
	if ( (screen=SDL_SetVideoMode(w,h,video_bpp,videoflags)) == NULL ) {
		fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",
						w, h, video_bpp, SDL_GetError());
		quit(2);
	}
	FillBackground(screen);

	
	light = CreateLight(82);
	if ( light == NULL ) {
		quit(1);
	}

	
	if ( LoadSprite(screen, "icon.bmp") < 0 ) {
		SDL_FreeSurface(light);
		quit(1);
	}

	
	printf("Screen is at %d bits per pixel\n",screen->format->BitsPerPixel);
	if ( (screen->flags & SDL_HWSURFACE) == SDL_HWSURFACE ) {
		printf("Screen is in video memory\n");
	} else {
		printf("Screen is in system memory\n");
	}
	if ( (screen->flags & SDL_DOUBLEBUF) == SDL_DOUBLEBUF ) {
		printf("Screen has double-buffering enabled\n");
	}
	if ( (sprite->flags & SDL_HWSURFACE) == SDL_HWSURFACE ) {
		printf("Sprite is in video memory\n");
	} else {
		printf("Sprite is in system memory\n");
	}

	
	MoveSprite(screen, NULL);
	if ( (sprite->flags & SDL_HWACCEL) == SDL_HWACCEL ) {
		printf("Sprite blit uses hardware alpha acceleration\n");
	} else {
		printf("Sprite blit dosn't uses hardware alpha acceleration\n");
	}

	
	{ SDL_Rect clip;
		clip.x = 32;
		clip.y = 32;
		clip.w = screen->w-(2*32);
		clip.h = screen->h-(2*32);
		SDL_SetClipRect(screen, &clip);
	}

	
	lastticks = SDL_GetTicks();
	done = 0;
	mouse_pressed = 0;
	while ( !done ) {
		
		if ( mouse_pressed ) {
			MoveSprite(screen, light);
			mouse_pressed = 0;
		} else {
			MoveSprite(screen, NULL);
		}

		
		ticks = SDL_GetTicks();
		if ( (ticks-lastticks) < FRAME_TICKS ) {
#ifdef CHECK_SLEEP_GRANULARITY
fprintf(stderr, "Sleeping %d ticks\n", FRAME_TICKS-(ticks-lastticks));
#endif
			SDL_Delay(FRAME_TICKS-(ticks-lastticks));
#ifdef CHECK_SLEEP_GRANULARITY
fprintf(stderr, "Slept %d ticks\n", (SDL_GetTicks()-ticks));
#endif
		}
		lastticks = ticks;

		
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
				case SDL_VIDEORESIZE:
					screen = SDL_SetVideoMode(event.resize.w, event.resize.h, video_bpp, videoflags);
					if ( screen ) {
						FillBackground(screen);
					}
					break;
				
				case SDL_MOUSEMOTION:
					if (event.motion.state != 0) {
						AttractSprite(event.motion.x,
								event.motion.y);
						mouse_pressed = 1;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if ( event.button.button == 1 ) {
						AttractSprite(event.button.x,
						              event.button.y);
						mouse_pressed = 1;
					} else {
						SDL_Rect area;

						area.x = event.button.x-16;
						area.y = event.button.y-16;
						area.w = 32;
						area.h = 32;
						SDL_FillRect(screen, &area, 0);
						SDL_UpdateRects(screen,1,&area);
					}
					break;
				case SDL_KEYDOWN:
#ifdef _WIN32_WCE
					
					done = 1;
#else
					if ( event.key.keysym.sym == SDLK_ESCAPE ) {
						done = 1;
					} else if (event.key.keysym.sym == SDLK_t) {
						videoflags ^= SDL_FULLSCREEN;
						screen = SDL_SetVideoMode(w, h, video_bpp, videoflags);
						if ( screen == NULL ) {
							fprintf(stderr, "Couldn't toggle video mode: %s\n",
									SDL_GetError());
							quit(2);
						}
						FillBackground(screen);
					}
#endif

					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}
	}
	SDL_FreeSurface(light);
	SDL_FreeSurface(sprite);
	SDL_FreeSurface(backing);

	
	if ( flashes > 0 ) {
		printf("%d alpha blits, ~%4.4f ms per blit\n", 
			flashes, (float)flashtime/flashes);
	}

	SDL_Quit();
	return(0);
}
