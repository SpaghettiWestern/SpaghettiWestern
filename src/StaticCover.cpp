#include "StaticCover.h"

StaticCover::StaticCover(bool isTraversable, int deflection_chance) :
		BoardStatic(isTraversable, -1), deflection_chance(deflection_chance){

}

StaticCover::StaticCover(Coordinate3D<int> loc, bool isTraversable, int deflection_chance) :
	BoardStatic(loc, isTraversable, -1), deflection_chance(deflection_chance){

}

StaticCover::StaticCover(bool isTraversable, int hitpoints, int deflection_chance) :
	BoardStatic(isTraversable, hitpoints), deflection_chance(deflection_chance){

}

StaticCover::StaticCover(Coordinate3D<int> loc, bool isTraversable, int hitpoints, int deflection_chance) :
	BoardStatic(loc, isTraversable, hitpoints), deflection_chance(deflection_chance){

}

StaticCover::StaticCover(const StaticCover& other) : BoardStatic((const BoardStatic&) other){
	deepCopy(other);
}

StaticCover& StaticCover::operator=(const StaticCover& other){
	BoardStatic::operator=((const BoardStatic&) other);
	deepCopy(other);
	return *this;
}

void StaticCover::deepCopy(const StaticCover& other){
	deflection_chance = other.deflection_chance;
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

