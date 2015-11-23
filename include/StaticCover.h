#ifndef STATICCOVER_H
#define STATICCOVER_H

#include "BoardStatic.h"
#include "Attack.h"

class StaticCover : public BoardStatic{
private:
	int deflection_chance;

protected:


public:
	StaticCover(bool isTraversable, int deflection_chance);
	StaticCover(Coordinate loc, bool isTraversable, int deflection_chance);
	StaticCover(bool isTraversable, int hitpoints, int deflection_chance);
	StaticCover(Coordinate loc, bool isTraversable, int hitpoints, int deflection_chance);

	virtual bool receiveAttack(Attack& attack);
	virtual static_type getType() const;
	virtual bool update();
};



#endif
