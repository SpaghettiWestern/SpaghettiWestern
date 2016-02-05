#include "StaticCover.h"
#include "UnitTest++.h"

SUITE(){
	//	StaticCover(bool isTraversable, int deflection_chance);
	TEST(constructor_0){
		std::cerr << "Testing StaticCover\n";

		StaticCover test_cover = StaticCover(false, 100);
		CHECK(test_cover.isTraversable() == false);
		CHECK(test_cover.getMaxHealth() == -1);
		CHECK(test_cover.getCurrentHealth() == -1);
	}

	//	StaticCover(Coordinate loc, bool isTraversable, int deflection_chance);
	TEST(constructor_1){
		Coordinate test_coord = Coordinate(5,6);
		StaticCover test_cover = StaticCover(test_coord, false, 100);
		CHECK(test_cover.getLocation() == test_coord);
		CHECK(test_cover.isTraversable() == false);
		CHECK(test_cover.getMaxHealth() == -1);
		CHECK(test_cover.getCurrentHealth() == -1);
	}

	//	StaticCover(bool isTraversable, int hitpoints, int deflection_chance);
	TEST(constructor_2){
		StaticCover test_cover = StaticCover(false, 100, 600);
		CHECK(test_cover.isTraversable() == false);
		CHECK(test_cover.getMaxHealth() == 100);
		CHECK(test_cover.getCurrentHealth() == 100);
	}

	//	StaticCover(Coordinate loc, bool isTraversable, int hitpoints, int deflection_chance);
	TEST(constructor_3){
		Coordinate test_coord = Coordinate(5,6);
		StaticCover test_cover = StaticCover(test_coord, false, 100, 600);
		CHECK(test_cover.getLocation() == test_coord);
		CHECK(test_cover.isTraversable() == false);
		CHECK(test_cover.getMaxHealth() == 100);
		CHECK(test_cover.getCurrentHealth() == 100);
	}

	//	virtual static_type getType() const;
	TEST(get_type){
		StaticCover test_cover = StaticCover(false, 100);
		CHECK(test_cover.getType() == STATICCOVER);
	}

	//	virtual bool receiveAttack(Attack& attack);
	TEST(receive_attack){
		//cover has 100% deflection chance
		int full_deflection = 1000;
		int no_deflection = 0;
		int max_hp = 600;
		StaticCover test_cover = StaticCover(false, max_hp, full_deflection);

		int damage = 200;
		Attack test_attack = Attack(damage);

		CHECK(test_cover.getCurrentHealth() == max_hp);
		CHECK(test_cover.receiveAttack(test_attack));
		CHECK(test_cover.getCurrentHealth() == (max_hp - damage));

		StaticCover test_cover_2 = StaticCover(false, max_hp, no_deflection);
		CHECK(test_cover_2.getCurrentHealth() == max_hp);
		CHECK(!test_cover_2.receiveAttack(test_attack));
		CHECK(test_cover_2.getCurrentHealth() == (max_hp - damage));
	}

	//	virtual bool update();
	TEST(update){
		//It just calls the BoardStatic update method, so this test is just to make sure it doesn't crash
		StaticCover test_cover = StaticCover(false, 700);
		for (int i = 0; i < 30; i++){
			test_cover.update();
		}
	}


}
