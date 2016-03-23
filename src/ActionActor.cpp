#include "ActionActor.h"

ActionActor::ActionActor(Coordinate3D<int> loc, Player& owner, int hitpoints, Attack attack) :
	BoardActor(loc, owner, hitpoints), attack(attack){

}

ActionActor::ActionActor(Coordinate3D<int> loc, Player& owner, Attack attack) :
	BoardActor(loc, owner, -1), attack(attack){
}

ActionActor::ActionActor(const ActionActor& other) : BoardActor((const BoardActor&) other ){
	deepCopy(other);
}

ActionActor& ActionActor::operator=(const ActionActor& other){
	BoardActor::operator=((const BoardActor&) other);
	deepCopy(other);
	return *this;
}

void ActionActor::deepCopy(const ActionActor other){
	attack = other.attack;
}

const Attack& ActionActor::getAttack() const{
	return attack;
}

actor_type ActionActor::getType() const{
	return ACTIONACTOR;
}
