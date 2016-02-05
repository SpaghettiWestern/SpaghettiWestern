#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Frame.h"

#include <SDL2/SDL.h>


class Animation{
private:
	std::vector<Frame> frames;
	bool repeating;
	int curr_frame;

	SDL_Texture* spriteSheet = NULL;

public:
	Animation();
	Animation(bool repeating);
	bool update();

	const Frame& getCurrFrame() const;
	void addFrame(Frame new_frame);
	void reset();

	bool setSpriteSheet(SDL_Texture* newSpriteSheet);

};



#endif
