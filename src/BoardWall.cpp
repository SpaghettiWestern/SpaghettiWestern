#include "BoardWall.h"

BoardWall::BoardWall(WallEdge edge, bool isTraversable) : BoardStatic(isTraversable){
	cellEdge = edge;
}

BoardWall::BoardWall(WallEdge edge, Coordinate3D<int> loc, bool isTraversable) : BoardStatic(loc, isTraversable){
	cellEdge = edge;
}

BoardWall::BoardWall(WallEdge edge, bool isTraversable, int hitpoints) : BoardStatic(isTraversable, hitpoints){
	cellEdge = edge;
}

BoardWall::BoardWall(WallEdge edge, Coordinate3D<int> loc, bool isTraversable, int hitpoints) : BoardStatic(loc, isTraversable, hitpoints){
	cellEdge = edge;
}

BoardWall::BoardWall(const BoardWall& other) : BoardStatic((const BoardStatic&) other){
	deepCopy(other);
}

BoardWall& BoardWall::operator=(const BoardWall& other){
	BoardStatic::operator =((const BoardStatic&) other);
	deepCopy(other);
	return *this;
}

void BoardWall::deepCopy(const BoardWall& other){
	cellEdge = other.cellEdge;
}


BoardWall::WallEdge BoardWall::getEdge() const{
	return cellEdge;
}
