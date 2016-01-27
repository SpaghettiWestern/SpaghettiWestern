#include "BoardPiece.h"

BoardPiece::BoardPiece(){
	location = Coordinate(-1,-1);
	resetScreenLocation();
	initAnimations();
	max_hitpoints = -1;
	curr_hitpoints = -1;
}

BoardPiece::BoardPiece(Coordinate loc){
	location = loc;
	resetScreenLocation();
	initAnimations();
	max_hitpoints = -1;
	curr_hitpoints = -1;
}

BoardPiece::BoardPiece(int hitpoints){
	location = Coordinate(-1,-1);
	resetScreenLocation();
	initAnimations();
	max_hitpoints = hitpoints;
	curr_hitpoints = hitpoints;

}

BoardPiece::BoardPiece(Coordinate loc, int hitpoints){
	location = loc;
	resetScreenLocation();
	initAnimations();
	max_hitpoints = hitpoints;
	curr_hitpoints = hitpoints;

}

void BoardPiece::initAnimations(){
	animations.clear();
	animations.push_back(Animation());

	active_animation = 0;
}

void BoardPiece::setAnimation(const Animation& new_animation){
	animations[active_animation] = new_animation;
}

void BoardPiece::resetAnimation(){
	animations[active_animation].reset();
}

const Frame& BoardPiece::getCurrentAnimationFrame() const{
	return animations[active_animation].getCurrFrame();
}


void BoardPiece::recieveDamage(int damage){
	// negative health is signaling invincibility right now
	if (curr_hitpoints < 0 ){
		return;
	}
	curr_hitpoints = curr_hitpoints - damage;
	if(curr_hitpoints <= 0){
		curr_hitpoints = 0;
		return;
	}
	if(curr_hitpoints > max_hitpoints){
		curr_hitpoints = max_hitpoints;
	}
}


int BoardPiece::getCurrentHealth() const{
	return curr_hitpoints;
}

int BoardPiece::getMaxHealth() const{
	return max_hitpoints;
}

bool BoardPiece::recieveAttack(const Attack& attack){
	recieveDamage(attack.getDamage());
	return true;
}

void BoardPiece::resetScreenLocation(){
	screen_location = Util::coordToScreen(location);
}

const Coordinate& BoardPiece::getLocation() const{
	return location;
}

void BoardPiece::setLocation(Coordinate new_location){
	if(new_location != location){
		location = new_location;
		if(Util::screenToCoord(screen_location) != location){
			resetScreenLocation();
		}
	}
}

const ScreenCoordinate& BoardPiece::getScreenLocation() const{
	return screen_location;
}

bool BoardPiece::updateAnimation(){
	return animations[active_animation].update();
}

bool BoardPiece::update(){
	return updateAnimation();
}



