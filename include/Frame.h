#ifndef FRAME_H
#define FRAME_H

#include <tuple>

#include "Util.h"
#include <SDL2/SDL.h>


class Frame{
private:
	std::tuple<int, int, int> color;
	float size;

	SDL_Rect textureSrc;


public:

	Frame();
	Frame(std::tuple<int, int, int> color, float size);

	Frame(std::tuple<int, int, int> color, float size, SDL_Rect textureSrc);


	bool operator==(const Frame& other) const;

	float getSize() const;
	const std::tuple<int, int, int>& getColor() const;

	const SDL_Rect* getSrcRect() const;

};


#endif
