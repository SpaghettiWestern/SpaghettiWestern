#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Frame.h"
#include "BlitHelper.h"

class Animation{
private:
	std::vector<Frame> frames;
	bool repeating;
	int curr_frame;
	void deepCopy(const Animation& other);

public:
	Animation();
	Animation(bool repeating);
	Animation(const Animation& other);
	Animation& operator=(const Animation& other);

	bool update();

	const Frame& getCurrFrame() const;
	void addFrame(Frame new_frame);
	void reset();

	void loadSpriteSheet(std::string& filepath);
};



#endif
