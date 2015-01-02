#include <iostream>

#include "Attack.h"
#include "UnitTest++.h"

SUITE(Attack){
	TEST(constructor){
		std::cerr << "Testing Attack\n";

		Attack testattack(28);
		CHECK(testattack.getDamage() == 28);
	}

	TEST(setdamage){
		Attack testattack(28);
		CHECK(testattack.getDamage() == 28);

		testattack.setDamage(0);
		CHECK(testattack.getDamage() == 0);

		testattack.setDamage(-28);
		CHECK(testattack.getDamage() == -28);
	}

}
