#include "MovingEffect.h"
MovingEffect::MovingEffect() : Effect(){
	move_path.clear();
	moving = false;
}

MovingEffect::MovingEffect(Coordinate2D<double> loc) : Effect(loc){
	move_path.clear();
	moving = false;
}

MovingEffect::MovingEffect(Coordinate2D<double> loc, const std::vector<Coordinate2D<double>>& path) : Effect(loc), move_path(path){
	moving = false;
}

MovingEffect::MovingEffect(Coordinate2D<double> loc, const Animation& anim) : Effect(loc, anim){
	move_path.clear();
	moving = false;
}

MovingEffect::MovingEffect(Coordinate2D<double> loc, const Animation& anim, const std::vector<Coordinate2D<double>>& path) : Effect(loc, anim), move_path(path){
	moving = false;
}

MovingEffect::MovingEffect(const MovingEffect& other) : Effect((const Effect&) other){
	deepCopy(other);
}

MovingEffect& MovingEffect::operator=(const MovingEffect& other){
	Effect::operator=((const Effect&) other);
	deepCopy(other);
	return *this;
}

void MovingEffect::deepCopy(const MovingEffect& other){
	move_path = other.move_path;
	moving = other.moving;
	pathgen = other.pathgen;
}

void MovingEffect::setPath(const std::vector<Coordinate2D<double>>& new_path){
	move_path = new_path;
}

void MovingEffect::transferPath(std::vector<Coordinate2D<double>>& new_path){
	move_path.swap(new_path);
	new_path.clear();
}

void MovingEffect::generatePath(const Coordinate2D<double>& dest, double speed){
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

Coordinate2D<double> MovingEffect::getNextStep() const{
	if(move_path.empty())
		return Coordinate2D<double>(-1.0,-1.0);
	return move_path.back();
}

effect_type MovingEffect::getType() const{
	return MOVINGEFFECT;
}

bool MovingEffect::update(){
	Effect::update();
	return moveStep();
}



