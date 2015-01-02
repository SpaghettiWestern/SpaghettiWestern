#include "BoardStatic.h"

BoardStatic::BoardStatic(Coordinate loc, bool traversable) : BoardPiece(loc), traversable(traversable){

}


void BoardStatic::setTraversable(bool traversable){
	this->traversable = traversable;
}

bool BoardStatic::isTraversable() const{
	return traversable;
}
