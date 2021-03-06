#include "Frame.h"

Frame::Frame() : color(std::make_tuple(255,255,255)), size(.05){

}

Frame::Frame(std::tuple<int, int, int> color, float size) : color(color), size(size){

}

Frame::Frame(Coordinate2D<double> topLeft, Coordinate2D<double> botRight, float size) : tex_topLeft(topLeft), tex_botRight(botRight), size(size){
	color = std::make_tuple(0,255,0);
}

Frame::Frame(const Frame& other){
	deepCopy(other);
}


Frame& Frame::operator=(const Frame& other){
	deepCopy(other);
}

void Frame::deepCopy(const Frame& other){
	tex_topLeft = other.tex_topLeft;
	tex_botRight = other.tex_botRight;
	color = other.color;
	size = other.size;
}


bool Frame::operator==(const Frame& other) const{
	return std::get<0>(color) == std::get<0>(other.color) &&
		std::get<1>(color) == std::get<1>(other.color) &&
		std::get<2>(color) == std::get<2>(other.color) &&
		size == other.size;
}

float Frame::getSize() const{
	return size;
}

const std::tuple<int, int, int>& Frame::getColor() const{
	return color;
}
