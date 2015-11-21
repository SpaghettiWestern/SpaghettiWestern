#include <iostream>

#include "Attack.h"
#include "UnitTest++.h"

SUITE(Attack){
	TEST(constructor_onevar){
		std::cerr << "Testing Attack\n";

		Attack testattack(28);
		CHECK(testattack.getDamage() == 28);
		CHECK(testattack.getAccuracy() == 0.0);
		CHECK(testattack.getSpread() == 0.0);
		CHECK(testattack.getSpeed() == 0.01);
	}

	TEST(constructor_twovar){
		Attack testattack(28, 10.1);

		CHECK(testattack.getDamage() == 28);
		CHECK(testattack.getAccuracy() == 10.1);
		CHECK(testattack.getSpread() == 0.0);
		CHECK(testattack.getSpeed() == 0.01);
	}

	TEST(constructor_threevar){
		Attack testattack(28, 10.1, 0.01244);

		CHECK(testattack.getDamage() == 28);
		CHECK(testattack.getAccuracy() == 10.1);
		CHECK(testattack.getSpread() == 0.01244);
		CHECK(testattack.getSpeed() == 0.01);
	}

	TEST(constructor_fourvar){
		Attack testattack(28, 10.1, 0.01244, 0.111);

		CHECK(testattack.getDamage() == 28);
		CHECK(testattack.getAccuracy() == 10.1);
		CHECK(testattack.getSpread() == 0.01244);
		CHECK(testattack.getSpeed() == 0.111);
	}

	TEST(setdamage){
		Attack testattack(28, 10.1, 0.01244, 0.111);
		CHECK(testattack.getDamage() == 28);

		testattack.setDamage(0);
		CHECK(testattack.getDamage() == 0);

		testattack.setDamage(-28);
		CHECK(testattack.getDamage() == -28);
	}

	TEST(setaccuracy){
		Attack testattack(28, 10.1, 0.01244, 0.111);
		CHECK(testattack.getAccuracy() == 10.1);

		testattack.setAccuracy(0.1111);
		CHECK(testattack.getAccuracy() == .1111);

		testattack.setAccuracy(-10.1);
		CHECK(testattack.getAccuracy() == -10.1);
	}

	TEST(setspread){
		Attack testattack(28, 10.1, 0.01244, 0.111);
		CHECK(testattack.getSpread() == 0.01244);

		testattack.setSpread(0.1111);
		CHECK(testattack.getSpread() == 0.1111);

		testattack.setSpread(-10.1);
		CHECK(testattack.getSpread() == -10.1);
	}

	TEST(setspeed){
		Attack testattack(28, 10.1, 0.01244, 0.111);
		CHECK(testattack.getSpeed() == 0.111);

		testattack.setSpeed(0.1111);
		CHECK(testattack.getSpeed() == 0.1111);

		testattack.setSpeed(-10.1);
		CHECK(testattack.getSpeed() == -10.1);
	}


}
