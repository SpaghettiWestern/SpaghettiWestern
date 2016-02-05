#include "BoardStatic.h"
#include "UnitTest++.h"

SUITE(BoardStatic){
	//BoardStatic(bool isTraversable);
	TEST(constructor_0){
		std::cerr << "Testing BoardStatic\n";

		BoardStatic test_static = BoardStatic(false);
		CHECK(test_static.isTraversable() == false);
	}

	//BoardStatic(Coordinate loc, bool isTraversable);
	TEST(constructor_1){
		Coordinate test_coord = Coordinate(5,6);
		BoardStatic test_static = BoardStatic(test_coord, false);
		CHECK(test_static.isTraversable() == false);
		CHECK(test_static.getLocation() == test_coord);
	}

	//BoardStatic(bool isTraversable, int hitpoints);
	TEST(constructor_2){
		BoardStatic test_static = BoardStatic(false, 50);
		CHECK(test_static.isTraversable() == false);
		CHECK(test_static.getMaxHealth() == 50);
		CHECK(test_static.getCurrentHealth() == 50);
	}

	//BoardStatic(Coordinate loc, bool isTraversable, int hitpoints);
	TEST(constructor_3){
		Coordinate test_coord = Coordinate(5,6);
		BoardStatic test_static = BoardStatic(test_coord, false, 50);
		CHECK(test_static.isTraversable() == false);
		CHECK(test_static.getLocation() == test_coord);
		CHECK(test_static.getMaxHealth() == 50);
		CHECK(test_static.getCurrentHealth() == 50);
	}

	//bool isTraversable() const;
	//void setTraversable(bool traversable);
	TEST(set_traversable){
		BoardStatic test_static = BoardStatic(false);
		CHECK(test_static.isTraversable() == false);
		test_static.setTraversable(true);
		CHECK(test_static.isTraversable() == true);
		test_static.setTraversable(false);
		CHECK(test_static.isTraversable() == false);
	}

	//virtual static_type getType() const;
	TEST(get_type){
		BoardStatic test_static = BoardStatic(false);
		CHECK(test_static.getType() == BOARDSTATIC);
	}

	//virtual bool update();
	TEST(update){
		BoardStatic test_static = BoardStatic(false);
		//mimics BoardPiece's implementation, just look at those tests, this is just to make sure it doesn't crash
		for(int i = 0; i < 30; i++){
			test_static.update();
		}
	}
}
