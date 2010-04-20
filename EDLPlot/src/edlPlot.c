/*
 * edlPlot.c
 *
 *  Created on: Apr 19, 2010
 *      Author: uclinux
 */
#include <stdlib.h>
#include "SDL/SDL.h"

#include "SDL_draw.h"

typedef struct {
	int *x;
	int *y;
} Data;

Uint32 FastestFlags(Uint32 flags, unsigned int width, unsigned int height,
 unsigned int bpp)
{
  const SDL_VideoInfo *info;

  flags |= SDL_FULLSCREEN;

  info = SDL_GetVideoInfo();
  if ( info->blit_hw_CC && info->blit_fill ) {
    flags |= SDL_HWSURFACE;
  }

  if ( (flags & SDL_HWSURFACE) == SDL_HWSURFACE ) {
    if ( info->video_mem*1024 > (height*width*bpp/8) ) {
      flags |= SDL_DOUBLEBUF;
    } else {
      flags &= ~SDL_HWSURFACE;
    }
  }

  return flags;
}

void plotAxes(SDL_Surface *screen, Uint32 c_colors[], int width, int height, int min_x, int max_x, int min_y, int max_y){
//So, "0" needs to be min_x, "height" needs to be max_x
//scale here
    int pixels_x = screen->w;
    int pixels_y = screen->h;
    int units_x = max_x - min_x;
    int units_y = max_y - min_y;

    //@NATMAT: THESE SHOULD BE USEFUL IN A TRANSLATION FUNCTION BETWEEN UNITS AND SCREEN PIXELS
    float pixels_per_unit_x = (float)pixels_x / (float)units_x;
    float pixels_per_unit_y = (float)pixels_y / (float)units_y;

    int x_axis_center = (-min_y)*pixels_per_unit_y;
    int y_axis_center = (-min_x)*pixels_per_unit_x;
    //Draw axes lines
	Draw_Line(screen, 0, x_axis_center, width, x_axis_center, c_colors[0]);
	Draw_Line(screen, y_axis_center, 0, y_axis_center, height, c_colors[0]);

	//Draw markers
	int i=1;
	while(i < width){
		Draw_Line(screen, i, x_axis_center-3, i, x_axis_center+3, c_colors[2]);
		i+= pixels_per_unit_x;
	}
	i=1;
	while(i < height){
		Draw_Line(screen, y_axis_center-3, i, y_axis_center+3, i, c_colors[2]);
		i+= pixels_per_unit_y;
	}
}

void plotLine(SDL_Surface *screen, Uint32 c_colors[], int x1, int y1, int x2, int y2, int min_x, int max_x, int min_y, int max_y){
    int units_x = max_x - min_x;
    int units_y = max_y - min_y;

    int pixels_x = screen->w;
    int pixels_y = screen->h;
    int pixels_per_unit_x = pixels_x / units_x;
    int pixels_per_unit_y = pixels_y / units_y;

    //int x_axis_center = (-min_y)*pixels_per_unit_y;
    //int y_axis_center = (-min_x)*pixels_per_unit_x;

	Draw_Line(screen, (x1*pixels_per_unit_x+screen->w/2), (-y1*pixels_per_unit_y+screen->h/2), (x2*pixels_per_unit_x+screen->w/2), (-y2*pixels_per_unit_y+screen->h/2), c_colors[1]);
	//Draw_Line(screen, (x1+screen->w/2), pixels_per_unit_y*(-y1+screen->h/2), (x2+screen->w/2), pixels_per_unit_y*(-y2+screen->h/2), c_colors[1]);
};

void plotArray(SDL_Surface *screen, Uint32 c_colors[], Data data, int min_x, int max_x, int min_y, int max_y) {
	int i = 0;
	int *x_current_ptr, *y_current_ptr;
	x_current_ptr = data.x;
	y_current_ptr = data.y;
	while (i < 5) {
		plotLine(screen, c_colors, *x_current_ptr, *y_current_ptr, *(x_current_ptr+1), *(y_current_ptr+1), min_x, max_x, min_y, max_y);
		//printf("%d, %d\n", *x_current_ptr, *y_current_ptr);
		//printf("%d, %d    %d, %d\n", *x_current_ptr, *y_current_ptr, *(x_current_ptr+1), *(y_current_ptr+1));
		x_current_ptr++;
		y_current_ptr++;
		i++;
	}
}


