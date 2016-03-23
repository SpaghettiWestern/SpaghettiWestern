#include "BoardDecoration.h"


BoardDecoration::BoardDecoration() : BoardPiece(){

}

BoardDecoration::BoardDecoration(const Coordinate3D<int>& loc) : BoardPiece(loc){

}

BoardDecoration::BoardDecoration(int hitpoints) : BoardPiece(hitpoints){

}

BoardDecoration::BoardDecoration(const Coordinate3D<int>& loc, int hitpoints) : BoardPiece(loc, hitpoints){

}

BoardDecoration::BoardDecoration(const BoardDecoration& other) : BoardPiece((const BoardPiece&) other){
	deepCopy(other);
}

BoardDecoration& BoardDecoration::operator=(const BoardDecoration& other){
	BoardPiece::operator =((const BoardPiece&) other);
	deepCopy(other);
	return *this;
}

void BoardDecoration::deepCopy(const BoardDecoration& other){

}
