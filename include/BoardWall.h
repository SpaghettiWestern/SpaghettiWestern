#ifndef BOARDWALL_H
#define BOARDWALL_H

#include "BoardStatic.h"



class BoardWall : public BoardStatic{
public:
	enum WallEdge{ NORTHWEST, SOUTHWEST, NORTHEAST, SOUTHEAST};

	BoardWall(WallEdge edge, bool isTraversable);
	BoardWall(WallEdge edge, Coordinate3D<int> loc, bool isTraversable);
	BoardWall(WallEdge edge, bool isTraversable, int hitpoints);
	BoardWall(WallEdge edge, Coordinate3D<int> loc, bool isTraversable, int hitpoints);
	BoardWall(const BoardWall& other);

	BoardWall& operator=(const BoardWall& other);

	WallEdge getEdge() const;


private:
	void deepCopy(const BoardWall& other);
	WallEdge cellEdge;


};


#endif
