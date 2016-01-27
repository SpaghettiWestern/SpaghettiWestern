#ifndef BLITHELPER_H
#define BLITHELPER_H

#include <SDL2/SDL.h>
#include "Util.h"

class BlitHelper{
private:


protected:


public:
	static SDL_Renderer* renderer;

	static void initilize_blitter(SDL_Renderer* renderer);
	static SDL_Texture* loadImage(std::string filename);
	static void unloadImage(SDL_Texture*& image);


};



#endif
