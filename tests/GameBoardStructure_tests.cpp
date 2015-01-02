#include "GameBoard.h"
#include "Player.h"
#include "UnitTest++.h"

#include <memory>
#include <exception>

SUITE(GameBoardStructure){
	TEST(constructor_default){
		std::cerr << "Testing GameBoardStructure\n";
		int length = 20;
		int width = 20;

		GameBoardStructure testboard(length, width);
		for(int i = 0; i < width; i++){
			for(int j = 0; j < length; j++){
				CHECK(testboard.getEnvironmentPiece(i,j).getLocation() == Coordinate(i,j));
			}
		}

		CHECK(testboard.getLength() == length);
		CHECK(testboard.getWidth() == width);
	}

	TEST(constructor_dimensions){
		int length = 40;
		int width = 30;

		GameBoardStructure testboard(length, width);
		for(int i = 0; i < width; i++){
			for(int j = 0; j < length; j++){
				CHECK(testboard.getEnvironmentPiece(i,j).getLocation() == Coordinate(i,j));
			}
		}

		CHECK(testboard.getLength() == length);
		CHECK(testboard.getWidth() == width);
	}

	TEST(openSpace){
		GameBoardStructure testboard(3,3);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate(0,0), testplayer));

		testboard.addActor(testact);

		CHECK(testboard.openSpace(Coordinate(0,0)) == false);
		testboard.removeActor(Coordinate(1,1));
		CHECK(testboard.openSpace(Coordinate(1,1)) == true);
	}

	TEST(inBounds){
		//(length, width)
		GameBoardStructure testboard(3,4);
		//(x,y)
		CHECK(testboard.inBounds(Coordinate(0,0)) == true);
		CHECK(testboard.inBounds(Coordinate(3,2)) == true);
		CHECK(testboard.inBounds(Coordinate(1,1)) == true);
		CHECK(testboard.inBounds(Coordinate(-1,-1)) == false);
		CHECK(testboard.inBounds(Coordinate(4,3)) == false);
		CHECK(testboard.inBounds(Coordinate(-1,2)) == false);
		CHECK(testboard.inBounds(Coordinate(2,-1)) == false);
		CHECK(testboard.inBounds(Coordinate(2,3)) == false);
		CHECK(testboard.inBounds(Coordinate(4,2)) == false);
	}

	TEST(actorExists){
		GameBoardStructure testboard(3,3);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate(1,0), testplayer));
		testboard.addActor(testact);

		CHECK(testboard.actorExists(Coordinate(1,0)) == true);
		CHECK(testboard.actorExists(Coordinate(0,1)) == false);
	}

	TEST(addActor){
		GameBoardStructure testboard(3,3);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate(1,0), testplayer));
		CHECK(testboard.addActor(testact) == true);
		CHECK(testboard.addActor(testact) == false);

	}

	TEST(removeActor){
		GameBoardStructure testboard(3,3);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate(0,0), testplayer));
		testboard.addActor(testact);
		CHECK(testboard.actorExists(Coordinate(0,0)) == true);
		testboard.removeActor(Coordinate(0,0));
		CHECK(testboard.actorExists(Coordinate(0,0)) == false);
	}

	TEST(moveActor){
		GameBoardStructure testboard(3,3);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate(0,0), testplayer));
		testboard.addActor(testact);
		CHECK(testboard.actorExists(Coordinate(0,0)) == true);
		CHECK(testboard.actorExists(Coordinate(1,1)) == false);
		CHECK(testboard.getActor(0,0)->getLocation() == Coordinate(0,0));

		CHECK(testboard.moveActor(Coordinate(0,0), Coordinate(1,1)) == true);
		CHECK(testboard.actorExists(Coordinate(0,0)) == false);
		CHECK(testboard.actorExists(Coordinate(1,1)) == true);
		CHECK(testboard.getActor(1,1)->getLocation() == Coordinate(1,1));

		CHECK(testboard.moveActor(Coordinate(1,1), Coordinate(1,2)) == true);
		CHECK(testboard.actorExists(Coordinate(1,1)) == false);
		CHECK(testboard.actorExists(Coordinate(1,2)) == true);
		CHECK(testboard.getActor(1,2)->getLocation() == Coordinate(1,2));

		CHECK(testboard.moveActor(Coordinate(1,2), Coordinate(1,1)) == true);
		CHECK(testboard.actorExists(Coordinate(1,2)) == false);
		CHECK(testboard.actorExists(Coordinate(1,1)) == true);
		CHECK(testboard.getActor(1,1)->getLocation() == Coordinate(1,1));

		CHECK(testboard.moveActor(Coordinate(0,1), Coordinate(1,0)) == false);
	}
}
















