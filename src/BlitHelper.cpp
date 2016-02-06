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
		std::cerr <<"Error loading image: "<< SDL_GetError() << "\n";
		SDL_ClearError();
	}

	SDL_Texture* texture_image = SDL_CreateTextureFromSurface(renderer, optimizedImage);
	SDL_FreeSurface(optimizedImage);
	if(texture_image == NULL){
		std::cerr <<"Error creating texture: "<< SDL_GetError() << "\n";
		SDL_ClearError();
	}


	//Return the optimized image
	return texture_image;
}

void BlitHelper::unloadImage(SDL_Texture* texture){
	if(texture != NULL){
		SDL_DestroyTexture(texture);
	}
}

GLuint BlitHelper::loadImageGL(const std::string& name) {
	SDL_Surface* optimizedImage = NULL;
	SDL_Surface* loadedImage = SDL_LoadBMP(name.c_str());
	if( loadedImage != NULL ) {
		//Create an optimized image
		optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGBA8888, 0);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	} else{
		std::cerr <<"Error loading image: "<< SDL_GetError() << "\n";
		SDL_ClearError();
	}

	// Adapted from http://stackoverflow.com/questions/18934865/sdl2-with-opengl-texture-displaying-incorrectly
	GLuint texture;
	std::cerr << "Here!\n";
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	std::cerr << "There!\n";
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, optimizedImage->w, optimizedImage->h, 0, GL_BGRA_EXT , GL_UNSIGNED_BYTE, optimizedImage->pixels);
	std::cerr << "And HERE0!!\n";
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	std::cerr << "And HERE1!!\n";
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	std::cerr << "And HERE2!!\n";
	glBindTexture(GL_TEXTURE_2D, 0);
	std::cerr << "And HERE3!!\n";
	SDL_FreeSurface(optimizedImage);

	return texture;
}

void BlitHelper::unloadImageGL(GLuint& texture){
	glDeleteTextures(1, &texture);
}
