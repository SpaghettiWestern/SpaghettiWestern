#include "BoardStatic.h"

BoardStatic::BoardStatic(bool isTraversable) : BoardPiece(-1), traversable(isTraversable){
	initAnimations();
}

BoardStatic::BoardStatic(Coordinate3D<int> loc, bool traversable) : BoardPiece(loc, -1), traversable(traversable){
	initAnimations();
}

BoardStatic::BoardStatic(bool isTraversable, int hitpoints) : BoardPiece(hitpoints), traversable(isTraversable){
	initAnimations();
}

BoardStatic::BoardStatic(Coordinate3D<int> loc, bool traversable, int hitpoints) : BoardPiece(loc, hitpoints), traversable(traversable){
	initAnimations();
}


void BoardStatic::initAnimations(){
	animations.clear();

	std::normal_distribution<double> num_gen(0.0, 255.0);

	animations.push_back(Animation());
	for(int i = 0; i < 10; i++){
		if(traversable)
			animations[0].addFrame(Frame(std::make_tuple(30,0,num_gen(Util::getRandomEngine())), .1));
		else
			animations[0].addFrame(Frame(std::make_tuple(0,30,num_gen(Util::getRandomEngine())), .1));
	}

	active_animation = 0;
}

void BoardStatic::setTraversable(bool traversable){
	this->traversable = traversable;
}

bool BoardStatic::isTraversable() const{
	return traversable;
}

static_type BoardStatic::getType() const{
	return BOARDSTATIC;
}

bool BoardStatic::update(){
	return BoardPiece::update();
}

