#include "Animation.h"

Animation::Animation(){
	curr_frame = 0;
	repeating = true;
	frames.clear();
}

Animation::Animation(int length, bool repeating) : repeating(repeating){
	frames.clear();
	frames.resize(length);
	curr_frame = 0;
}

void Animation::update(){
	if(curr_frame < frames.size()-1){
		curr_frame++;
		return;
	}
	if(repeating){
		curr_frame = 0;
	}
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
