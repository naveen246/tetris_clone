
#ifndef IO_H_
#define IO_H_

#include <SDL/SDL.h>									
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"

#pragma comment (lib, "SDL/lib/SDL.lib")
#pragma comment (lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX};

class IO{
  public :

  	IO 						();

  	void drawRectangle		(int pX1, int pY1, int pX2, int pY2, enum color pC);
  	void clearScreen		();
 	int getScreenHeight		();
 	int initGraph			();
 	int pollKey				();
 	int getKey				();
 	int isKeyDown			(int pKey);
 	void updateScreen		();

};	


#endif