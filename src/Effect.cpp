#include "Effect.h"

Effect::Effect(){
	loc = ScreenCoordinate(0.0,0.0);
	initAnimation();
}

Effect::Effect(ScreenCoordinate loc) : loc(loc){
	initAnimation();
}

void Effect::initAnimation(){
	animation.reset();
	animation.addFrame(Frame(std::make_tuple(0,0,255), .01));
	animation.addFrame(Frame(std::make_tuple(0,0,0), .01));
}

Effect::Effect(ScreenCoordinate loc, Animation animation) : loc(loc), animation(animation){

}

ScreenCoordinate Effect::getScreenLocation() const{
	return loc;
}
void Effect::setScreenLocation(const ScreenCoordinate& new_loc){
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
