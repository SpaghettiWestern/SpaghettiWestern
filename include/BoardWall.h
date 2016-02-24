#ifndef BOARDWALL_H
#define BOARDWALL_H

#include "BoardStatic.h"

enum WallEdge{ NORTHWEST, SOUTHWEST, NORTHEAST, SOUTHEAST};

class BoardWall : BoardStatic{
public:


	WallEdge getEdge();

private:
	WallEdge cellEdge;


};


#endif
