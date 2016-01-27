#include "Frame.h"

Frame::Frame() : color(std::make_tuple(255,255,255)), size(.05){

}

Frame::Frame(std::tuple<int, int, int> color, float size) : color(color), size(size){

}

Frame::Frame(std::tuple<int, int, int> color, float size, SDL_Rect textureSrc) : color(color), size(size), textureSrc(textureSrc){

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


const SDL_Rect* Frame::getSrcRect() const{
	return &textureSrc;
}

