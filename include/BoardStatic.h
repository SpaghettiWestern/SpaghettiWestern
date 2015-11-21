#ifndef BOARDSTATIC_H
#define BOARDSTATIC_H

#include "BoardPiece.h"
#include "Util.h"

enum static_type {BOARDSTATIC, STATICCOVER};

class BoardStatic : public BoardPiece{
private:
	bool traversable;

protected:
	virtual void initAnimations();

public:
	BoardStatic(bool isTraversable);
	BoardStatic(Coordinate loc, bool isTraversable);
	BoardStatic(bool isTraversable, int hitpoints);
	BoardStatic(Coordinate loc, bool isTraversable, int hitpoints);

	void setTraversable(bool traversable);
	bool isTraversable() const;

	virtual static_type getType() const;

	virtual bool update();

};

#endif
