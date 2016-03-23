#include "BoardFloor.h"

BoardFloor::BoardFloor(bool isTraversable) : BoardStatic(isTraversable){

}

BoardFloor::BoardFloor(Coordinate3D<int> loc, bool isTraversable) : BoardStatic(loc, isTraversable){

}

BoardFloor::BoardFloor(bool isTraversable, int hitpoints) : BoardStatic(isTraversable, hitpoints){

}

BoardFloor::BoardFloor(Coordinate3D<int> loc, bool isTraversable, int hitpoints) : BoardStatic(loc, isTraversable, hitpoints){

}

BoardFloor::BoardFloor(const BoardFloor& other) : BoardStatic((const BoardStatic&) other){
	deepCopy(other);
}

BoardFloor& BoardFloor::operator=(const BoardFloor& other){
	BoardStatic::operator =((const BoardStatic&) other);
	deepCopy(other);
	return *this;
}

void BoardFloor::deepCopy(const BoardFloor& other){

}
