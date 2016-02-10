#ifndef FRAME_H
#define FRAME_H

#include <tuple>
#include "Util.h"

class Frame{
private:
	std::tuple<int, int, int> color;
	float size;

public:
	ScreenCoordinate tex_topLeft;
	ScreenCoordinate tex_botRight;

	Frame();
	Frame(std::tuple<int, int, int> color, float size);
	Frame(ScreenCoordinate topLeft, ScreenCoordinate botRight, float size);

	bool operator==(const Frame& other) const;

	float getSize() const;
	const std::tuple<int, int, int>& getColor() const;

};


#endif
