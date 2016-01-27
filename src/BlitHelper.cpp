#include "BlitHelper.h"

SDL_Renderer* BlitHelper::renderer = NULL;


void BlitHelper::initilize_blitter(SDL_Renderer* init_renderer){
	renderer = init_renderer;
}


SDL_Texture* BlitHelper::loadImage(std::string filename){
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = SDL_LoadBMP( filename.c_str() );

	//If nothing went wrong in loading the image
	if( loadedImage != NULL )
	{
		//Create an optimized image
		optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGBA8888, 0);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	} else{
		std::cout << SDL_GetError() << "\n";
	}

	SDL_Texture* texture_image = SDL_CreateTextureFromSurface(renderer, optimizedImage);
	SDL_FreeSurface(optimizedImage);

	//Return the optimized image
	return texture_image;
}


void BlitHelper::unloadImage(SDL_Texture*& image){
	SDL_DestroyTexture(image);
	image = NULL;
}

