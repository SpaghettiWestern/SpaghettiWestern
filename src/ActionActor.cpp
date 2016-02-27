#include "ActionActor.h"

ActionActor::ActionActor(Coordinate3D<int> loc, Player& owner, int hitpoints, Attack attack) :
	BoardActor(loc, owner, hitpoints), attack(attack){

}

ActionActor::ActionActor(Coordinate3D<int> loc, Player& owner, Attack attack) :
	BoardActor(loc, owner, -1), attack(attack){
}

const Attack& ActionActor::getAttack() const{
	return attack;
}

actor_type ActionActor::getType() const{
	return ACTIONACTOR;
}
