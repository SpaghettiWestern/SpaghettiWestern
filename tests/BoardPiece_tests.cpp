#include "BoardPiece.h"
#include "UnitTest++.h"

SUITE(BoardPiece){
	TEST(boardpiece_constructor_default)
	{
		std::cerr << "Testing BoardPiece\n";
		BoardPiece testpiece;
		CHECK(testpiece.getLocation() == Coordinate(-1,-1));
	}

	TEST(boardpiece_constructor_coord){
		BoardPiece testpiece(Coordinate(1,2));
		CHECK(testpiece.getLocation() == Coordinate(1,2));
	}

}
