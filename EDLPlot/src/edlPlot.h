/*
* edlPlot.h
*
* Created on: Apr 18, 2010
* Author: charlie
*/

#ifndef EDLPLOT_H_
#define EDLPLOT_H_

typedef struct {
	int *x;
	int *y;
} Data;

Uint32 FastestFlags(Uint32 flags, unsigned int width, unsigned int height,
 unsigned int bpp);

void plotAxes(SDL_Surface *screen, Uint32 c_colors[], int width, int height, int min_x, int max_x, int min_y, int max_y);

void plotLine(SDL_Surface *screen, Uint32 c_colors[], int x1, int y1, int x2, int y2, int min_x, int max_x, int min_y, int max_y);

void plotArray(SDL_Surface *screen, Uint32 c_colors[], Data data, int min_x, int max_x, int min_y, int max_y);

#endif /* EDLPLOT_H_ */

