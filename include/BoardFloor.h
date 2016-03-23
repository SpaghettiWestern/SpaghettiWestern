#ifndef BOARDFLOOR_H
#define BOARDFLOOR_H

#include "BoardStatic.h"

class BoardFloor : public BoardStatic{
public:
	BoardFloor(bool isTraversable);
	BoardFloor(Coordinate3D<int> loc, bool isTraversable);
	BoardFloor(bool isTraversable, int hitpoints);
	BoardFloor(Coordinate3D<int> loc, bool isTraversable, int hitpoints);
	BoardFloor(const BoardFloor& other);

	BoardFloor& operator=(const BoardFloor& other);

private:
	void deepCopy(const BoardFloor& other);

};

#endif
