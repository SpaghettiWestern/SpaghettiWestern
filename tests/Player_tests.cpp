#include "Player.h"
#include "BoardActor.h"
#include "UnitTest++.h"

#include <vector>

SUITE(Player){
	TEST(constructor_basic){
		std::cerr << "Testing Player\n";

		Player testplayer("tester1", true);
		CHECK(testplayer.getName().compare("tester1") == 0);
		CHECK(testplayer.isHuman() == true);

		Player testcpu("tester2", false);
		CHECK(testcpu.getName().compare("tester2") == 0);
		CHECK(testcpu.isHuman() == false);
	}

	TEST(createactor_nohp){
		Player testplayer("tester1", true);
		CHECK(testplayer.getName().compare("tester1") == 0);
		CHECK(testplayer.isHuman() == true);

		testplayer.createActor(Coordinate(0,0));
		const BoardActor& testact = testplayer.getActor(0);
		CHECK(testact.getLocation() == Coordinate(0,0));
		CHECK(testact.getCurrentHealth() == -1);
		CHECK(testact.getMaxHealth() == -1);
	}

	TEST(createactor_hp){
		Player testplayer("tester1", true);
		CHECK(testplayer.getName().compare("tester1") == 0);
		CHECK(testplayer.isHuman() == true);

		testplayer.createActor(Coordinate(0,0), 28);
		const BoardActor& testact = testplayer.getActor(0);
		CHECK(testact.getLocation() == Coordinate(0,0));
		CHECK(testact.getCurrentHealth() == 28);
		CHECK(testact.getMaxHealth() == 28);
	}

	TEST(actorexists){
		Player testplayer("tester1", true);
		CHECK(testplayer.getName().compare("tester1") == 0);
		CHECK(testplayer.isHuman() == true);

		CHECK(testplayer.actorExists(0) == false);
		testplayer.createActor(Coordinate(0,0), 28);
		CHECK(testplayer.actorExists(0) == true);

		CHECK(testplayer.actorExists(1) == false);
		testplayer.createActor(Coordinate(0,0), 28);
		CHECK(testplayer.actorExists(1) == true);
		CHECK(testplayer.actorExists(0) == true);
	}

	TEST(deleteactor){
		Player testplayer("tester1", true);
		CHECK(testplayer.getName().compare("tester1") == 0);
		CHECK(testplayer.isHuman() == true);

		CHECK(testplayer.deleteActor(0) == false);
		CHECK(testplayer.deleteActor(-1) == false);
		testplayer.createActor(Coordinate(0,0), 28);
		CHECK(testplayer.actorExists(0) == true);
		CHECK(testplayer.deleteActor(0) == true);
		CHECK(testplayer.actorExists(0) == false);

		testplayer.createActor(Coordinate(0,0), 28);
		testplayer.createActor(Coordinate(0,0), 28);
		CHECK(testplayer.actorExists(1) == true);
		CHECK(testplayer.deleteActor(1) == true);
		CHECK(testplayer.actorExists(1) == false);
		CHECK(testplayer.deleteActor(1) == false);
		CHECK(testplayer.deleteActor(0) == true);
	}



}
