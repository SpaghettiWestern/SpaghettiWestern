#include "Animation.h"

Animation::Animation(){
	curr_frame = 0;
	repeating = true;
	frames.clear();
}

Animation::Animation(bool repeating) : repeating(repeating){
	frames.clear();
	curr_frame = 0;
}

Animation::Animation(const Animation& other){
	deepCopy(other);
}

Animation& Animation::operator=(const Animation& other){
	deepCopy(other);
	return *this;
}

void Animation::deepCopy(const Animation& other){
	frames = other.frames;
	repeating = other.repeating;
	curr_frame = other.curr_frame;
}


bool Animation::update(){
	if(curr_frame < frames.size()-1){
		curr_frame++;
		return true;
	}
	if(repeating){
		curr_frame = 0;
		return true;
	}
	return false;
}

const Frame& Animation::getCurrFrame() const{
	return frames[curr_frame];
}

void Animation::addFrame(Frame new_frame){
	frames.push_back(new_frame);
}

void Animation::reset(){
	curr_frame = 0;
}

