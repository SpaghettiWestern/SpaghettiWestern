#ifndef BOARDDECORATION_H
#define BOARDDECORATION_H

#include "BoardPiece.h"

class BoardDecoration : public BoardPiece{
public:
	BoardDecoration();
	BoardDecoration(const Coordinate3D<int>& loc);
	BoardDecoration(int hitpoints);
	BoardDecoration(const Coordinate3D<int>& loc, int hitpoints);
	BoardDecoration(const BoardDecoration& other);

	BoardDecoration& operator=(const BoardDecoration& other);

private:
	void deepCopy(const BoardDecoration& other);

};

#endif
