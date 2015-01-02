#include "MovingEffect.h"
MovingEffect::MovingEffect() : Effect(){
	move_path.clear();
	moving = false;
}

MovingEffect::MovingEffect(ScreenCoordinate loc) : Effect(loc){
	move_path.clear();
	moving = false;
}

MovingEffect::MovingEffect(ScreenCoordinate loc, const std::vector<ScreenCoordinate>& path) : Effect(loc), move_path(path){
	moving = false;
}

MovingEffect::MovingEffect(ScreenCoordinate loc, const Animation& anim) : Effect(loc, anim){
	move_path.clear();
	moving = false;
}

MovingEffect::MovingEffect(ScreenCoordinate loc, const Animation& anim, const std::vector<ScreenCoordinate>& path) : Effect(loc, anim), move_path(path){
	moving = false;
}


void MovingEffect::setPath(const std::vector<ScreenCoordinate>& new_path){
	move_path = new_path;
}

void MovingEffect::transferPath(std::vector<ScreenCoordinate>& new_path){
	move_path.swap(new_path);
	new_path.clear();
}

void MovingEffect::generatePath(const ScreenCoordinate& dest, double speed){
	pathgen.generatePath(loc, dest, speed);
	pathgen.transferPath(move_path);
	if(!move_path.empty()){
		move_path.pop_back(); //first coordinate in path is always the current location, we're ditching it.
	}
}

bool MovingEffect::startMove(){
	if(!move_path.empty())
	{
		moving = true;
		return true;
	}
	return false;
}

void MovingEffect::stopMove(){
	moving = false;
}

bool MovingEffect::isMoving() const{
	return moving;
}

bool MovingEffect::moveStep() {
	if(isMoving() && !move_path.empty()){
		loc = move_path.back();
		move_path.pop_back();
		return true;
	}
	stopMove();
	return false;
}

ScreenCoordinate MovingEffect::getNextStep() const{
	if(move_path.empty())
		return ScreenCoordinate(-1.0,-1.0);
	return move_path.back();
}

effect_type MovingEffect::getType() const{
	return MOVINGEFFECT;
}

void MovingEffect::update(){
	Effect::update();
	moveStep();
}



