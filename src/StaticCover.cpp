#include "StaticCover.h"

StaticCover::StaticCover(bool isTraversable, int deflection_chance) :
		BoardStatic(isTraversable, -1), deflection_chance(deflection_chance){

}

StaticCover::StaticCover(Coordinate loc, bool isTraversable, int deflection_chance) :
	BoardStatic(loc, isTraversable, -1), deflection_chance(deflection_chance){

}

StaticCover::StaticCover(bool isTraversable, int hitpoints, int deflection_chance) :
	BoardStatic(isTraversable, hitpoints), deflection_chance(deflection_chance){

}

StaticCover::StaticCover(Coordinate loc, bool isTraversable, int hitpoints, int deflection_chance) :
	BoardStatic(loc, isTraversable, hitpoints), deflection_chance(deflection_chance){

}

bool StaticCover::receiveAttack(Attack& attack){
	BoardStatic::recieveAttack(attack);
	int hit_roll = std::rand() % 1000;
	if (hit_roll > deflection_chance)
		return false;
	return true;
}

static_type StaticCover::getType() const{
	return STATICCOVER;
}

bool StaticCover::update(){
	return BoardStatic::update();
}

