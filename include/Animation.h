#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Frame.h"

class Animation{
private:
	std::vector<Frame> frames;
	bool repeating;
	int curr_frame;

public:
	Animation();
	Animation(int length, bool repeating);
	bool update();

	const Frame& getCurrFrame() const;
	void addFrame(Frame new_frame);
	void reset();
};



#endif
