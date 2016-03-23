#include "Effect.h"

Effect::Effect(){
	loc = Coordinate2D<double>(0.0,0.0);
	initAnimation();
}

Effect::Effect(Coordinate2D<double> loc) : loc(loc){
	initAnimation();
}

void Effect::initAnimation(){
	animation.reset();
	animation.addFrame(Frame(std::make_tuple(0,0,255), .01));
	animation.addFrame(Frame(std::make_tuple(0,0,0), .01));
}

Effect::Effect(Coordinate2D<double> loc, Animation animation) : loc(loc), animation(animation){

}

Effect::Effect(const Effect& other){
	deepCopy(other);
}

Effect& Effect::operator=(const Effect& other){
	deepCopy(other);
	return *this;
}

void Effect::deepCopy(const Effect& other){
	loc = other.loc;
	animation = other.animation;
}

Coordinate2D<double> Effect::getScreenLocation() const{
	return loc;
}
void Effect::setScreenLocation(const Coordinate2D<double>& new_loc){
	loc = new_loc;
}

void Effect::setAnimation(const Animation& new_animation){
	animation = new_animation;
}
const Frame& Effect::getCurrentAnimationFrame() const{
	return animation.getCurrFrame();
}

effect_type Effect::getType() const{
	return EFFECT;
}

bool Effect::update(){
	return animation.update();
}
