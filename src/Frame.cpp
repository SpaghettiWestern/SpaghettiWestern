#include "Frame.h"

Frame::Frame() : color(std::make_tuple(255,255,255)), size(.05){

}

Frame::Frame(std::tuple<int, int, int> color, float size) : color(color), size(size){

}

bool Frame::operator==(const Frame& other){
	return std::get<0>(color) == std::get<0>(other.color) &&
		std::get<1>(color) == std::get<1>(other.color) &&
		std::get<2>(color) == std::get<2>(other.color) &&
		size == other.size;
}

float Frame::getSize(){
	return size;
}

std::tuple<int, int, int> Frame::getColor(){
	return color;
}
