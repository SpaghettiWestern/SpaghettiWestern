#ifndef ACTIONACTOR_H
#define ACTIONACTOR_H

#include "Util.h"
#include "BoardActor.h"
#include "Player.h"
#include "Attack.h"

class ActionActor : public BoardActor{
private:
	Attack attack;

public:
	ActionActor(Coordinate loc, Player& owner, int hitpoints, Attack attack);
	ActionActor(Coordinate loc, Player&owner, Attack attack);
	const Attack& getAttack() const;
	actor_type getType() const;
};


#endif
