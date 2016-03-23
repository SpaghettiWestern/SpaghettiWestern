#ifndef BOARDSTATIC_H
#define BOARDSTATIC_H

#include "BoardPiece.h"
#include "Util.h"

enum static_type {BOARDSTATIC, STATICCOVER};

class BoardStatic : public BoardPiece{
private:
	bool traversable;

	void deepCopy(const BoardStatic& other);

protected:
	virtual void initAnimations();

public:
	BoardStatic(bool isTraversable);
	BoardStatic(Coordinate3D<int> loc, bool isTraversable);
	BoardStatic(bool isTraversable, int hitpoints);
	BoardStatic(Coordinate3D<int> loc, bool isTraversable, int hitpoints);
	BoardStatic(const BoardStatic& other);
	BoardStatic& operator=(const BoardStatic& other);

	void setTraversable(bool traversable);
	bool isTraversable() const;

	virtual static_type getType() const;

	virtual bool update();

};

#endif
