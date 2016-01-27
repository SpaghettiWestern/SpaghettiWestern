#include "UnitTest++.h"
#include "GameBoard.h"
#include "ActionActor.h"

#include <memory>

SUITE(GameBoard){

	TEST(constructor_default){
		std::cerr << "Testing GameBoard\n";

		GameBoard testboard = GameBoard();
		CHECK(testboard.getBoard().getLength() == 20);
		CHECK(testboard.getBoard().getWidth() == 20);
	}

//	GameBoard(int length, int width);
//	GameBoardStructure& getBoard();
	TEST(constructor_dimensions){
		int length = 100;
		int width = 120;
		GameBoard testboard(length, width);
		CHECK(testboard.getBoard().getLength() == length);
		CHECK(testboard.getBoard().getWidth() == width);
	}

//	bool openSpace(const Coordinate& loc);
	TEST(openspace){
		GameBoard testboard(3,3);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate(0,0), testplayer));

		testboard.addActor(testact);

		CHECK(testboard.openSpace(Coordinate(0,0)) == false);
		testboard.removeActor(Coordinate(1,1));
		CHECK(testboard.openSpace(Coordinate(1,1)) == true);

		CHECK(testboard.openSpace(Coordinate(-1, 0)) == false);
		CHECK(testboard.openSpace(Coordinate(0, -1)) == false);
		CHECK(testboard.openSpace(Coordinate(4, 0)) == false);
		CHECK(testboard.openSpace(Coordinate(0, 4)) == false);
	}

//	bool canAttack(const Coordinate& attacker_loc, const Coordinate& attack_loc);
	TEST(canAttack){
		GameBoard testBoard(5,5);
		Player testplayer("tester1", true);

		Coordinate passive_1_loc(0,0);
		Coordinate passive_2_loc(0,1);
		Coordinate attacks_1_loc(1,1);
		Coordinate nobody_loc(3,3);

		std::shared_ptr<BoardActor> passive_1(new BoardActor(passive_1_loc, testplayer));
		std::shared_ptr<BoardActor> passive_2(new BoardActor(passive_2_loc, testplayer));
		std::shared_ptr<BoardActor> attacks_1(new ActionActor(attacks_1_loc, testplayer, 28, Attack(12)));

		testBoard.addActor(passive_1);
		testBoard.addActor(passive_2);
		testBoard.addActor(attacks_1);

		CHECK(testBoard.canAttack(passive_1_loc, passive_2_loc) == false);
		CHECK(testBoard.canAttack(passive_1_loc, attacks_1_loc) == false);
		CHECK(testBoard.canAttack(passive_1_loc, nobody_loc) == false);
		CHECK(testBoard.canAttack(nobody_loc, passive_2_loc) == false);
		CHECK(testBoard.canAttack(attacks_1_loc, nobody_loc) == false);
		CHECK(testBoard.canAttack(attacks_1_loc, passive_1_loc) == true);
	}

//	bool actorExists(const Coordinate& loc);
	TEST(actorExists){
		GameBoard testBoard(5,5);
		Player testplayer("tester1", true);

		Coordinate passive_1_loc(0,0);
		Coordinate attacks_1_loc(1,1);
		Coordinate nobody_loc(3,3);

		std::shared_ptr<BoardActor> passive_1(new BoardActor(passive_1_loc, testplayer));
		std::shared_ptr<BoardActor> attacks_1(new ActionActor(attacks_1_loc, testplayer, 28, Attack(12)));

		testBoard.addActor(passive_1);
		testBoard.addActor(attacks_1);

		CHECK(testBoard.actorExists(nobody_loc) == false);
		CHECK(testBoard.actorExists(passive_1_loc) == true);
		CHECK(testBoard.actorExists(attacks_1_loc) == true);
		CHECK(testBoard.actorExists(Coordinate(-1,-1)) == false);
	}

//	BoardActor& getActor(const Coordinate& loc);
//	bool addActor(std::shared_ptr<BoardActor> new_actor);
	TEST(getActor){
		GameBoard testBoard(5,5);
		Player testplayer("tester1", true);

		Coordinate passive_1_loc(0,0);
		Coordinate attacks_1_loc(1,1);

		std::shared_ptr<BoardActor> passive_1(new BoardActor(passive_1_loc, testplayer));
		std::shared_ptr<BoardActor> attacks_1(new ActionActor(attacks_1_loc, testplayer, 28, Attack(12)));

		testBoard.addActor(passive_1);
		testBoard.addActor(attacks_1);

		CHECK(testBoard.getActor(passive_1_loc).getLocation() == passive_1_loc);
		CHECK(testBoard.getActor(attacks_1_loc).getLocation() == attacks_1_loc);
	}

//	bool moveActor(Coordinate start, Coordinate end);
//	bool moveActor(BoardActor& actor, Coordinate goal);
	TEST(moveActor){
		GameBoard testboard(5,5);
		Player testplayer("tester1", true);

		Coordinate actorloc1(0,0);
		Coordinate actorloc2(2,0);
		Coordinate goal_loc1(4,3);
		Coordinate goal_loc2(3,4);

		std::shared_ptr<BoardActor> testactor1(new BoardActor(actorloc1, testplayer));
		std::shared_ptr<BoardActor> testactor2(new BoardActor(actorloc2, testplayer));

		testboard.addActor(testactor1);
		testboard.addActor(testactor2);

		CHECK(testboard.moveActor(actorloc1, Coordinate(-1,-1)) == false);
		CHECK(testboard.moveActor(actorloc1, actorloc2) == false);
		CHECK(testboard.moveActor(actorloc1, goal_loc1) == true);
		CHECK(testactor1->getDestination() == goal_loc1);
		CHECK(testactor1->isMoving() == true);

		CHECK(testboard.moveActor(*testactor2, goal_loc2) == true);
		CHECK(testactor2->getDestination() == goal_loc2);
		CHECK(testactor2->isMoving() == true);
	}

//	void update();
	TEST(update){
		GameBoard testboard(5,5);
		Player testplayer("tester1", true);
		Coordinate actor_loc(0,0);
		Coordinate goal_loc(3,4);

		std::shared_ptr<BoardActor> testactor(new BoardActor(actor_loc, testplayer));
		testboard.addActor(testactor);
		CHECK(testboard.moveActor(actor_loc, goal_loc) == true);
		CHECK(testactor->getDestination() == goal_loc);
		CHECK(testactor->isMoving() == true);

		int speed = 5;
		int max_path_length = 8;
		int i = 0;
		ScreenCoordinate curr_s(-1,-1);
		for(Coordinate curr = actor_loc; curr != goal_loc && i < max_path_length; i++){
			for(int j = 0; j < speed; j++){
				CHECK(curr_s != testactor->getScreenLocation());
				curr_s = testactor->getScreenLocation();
				testboard.update();
			}
			CHECK(curr != testactor->getLocation());
			curr = testactor->getLocation();
		}
		CHECK(testactor->getLocation() == goal_loc);
		testboard.update();
		CHECK(testactor->getLocation() == goal_loc);
	}


}
