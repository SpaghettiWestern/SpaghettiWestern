#ifndef FRAME_H
#define FRAME_H

#include <tuple>
#include "Util.h"

class Frame{
private:
	std::tuple<int, int, int> color;
	float size;

	void deepCopy(const Frame& other);

public:
	Coordinate2D<double> tex_topLeft;
	Coordinate2D<double> tex_botRight;

	Frame();
	Frame(std::tuple<int, int, int> color, float size);
	Frame(Coordinate2D<double> topLeft, Coordinate2D<double> botRight, float size);
	Frame(const Frame& other);

	Frame& operator=(const Frame& other);

	bool operator==(const Frame& other) const;

	float getSize() const;
	const std::tuple<int, int, int>& getColor() const;

};


#endif
