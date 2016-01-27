#ifndef FRAME_H
#define FRAME_H

#include <tuple>

class Frame{
private:
	std::tuple<int, int, int> color;
	float size;

public:

	Frame();
	Frame(std::tuple<int, int, int> color, float size);

	bool operator==(const Frame& other) const;

	float getSize() const;
	const std::tuple<int, int, int>& getColor() const;
};


#endif
