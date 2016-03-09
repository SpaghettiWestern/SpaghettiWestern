#ifndef ACTIONACTOR_H
#define ACTIONACTOR_H

#include "Util.h"
#include "BoardActor.h"
#include "Player.h"
#include "Attack.h"

class ActionActor : public BoardActor{
private:
	Attack attack;
	void deepCopy(const ActionActor other);

public:
	ActionActor(Coordinate3D<int> loc, Player& owner, int hitpoints, Attack attack);
	ActionActor(Coordinate3D<int> loc, Player&owner, Attack attack);
	ActionActor(const ActionActor& other);
	ActionActor& operator=(const ActionActor& other);

	const Attack& getAttack() const;
	actor_type getType() const;
};


#endif
