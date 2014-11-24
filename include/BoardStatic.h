#ifndef BOARDSTATIC_H
#define BOARDSTATIC_H

#include "BoardPiece.h"
#include "Util.h"

class BoardStatic : public BoardPiece{
private:
	bool traversable;

public:
	BoardStatic(Coordinate loc, bool isTraversable);
	void setTraversable(bool traversable);
	bool isTraversable();


};



#endif
