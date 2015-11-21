#include "BoardActor.h"
#include "Attack.h"
#include "Player.h"
#include "Frame.h"
#include "Animation.h"
#include "UnitTest++.h"

SUITE(boardactor){

	TEST(locationconstructor){
		std::cerr << "Testing BoardActor\n";

		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer);
		CHECK(testactor.getLocation() == Coordinate(1,2));
		CHECK(testactor.getCurrentHealth() == -1);
		CHECK(testactor.getMaxHealth() == -1);
		CHECK(testactor.getOwner().getName().compare("tester1") == 0);
	}

	TEST(healthconstructor){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer, 28);
		CHECK(testactor.getLocation() == Coordinate(1,2));
		CHECK(testactor.getCurrentHealth() == 28);
		CHECK(testactor.getMaxHealth() == 28);
		CHECK(testactor.getOwner().getName().compare("tester1") == 0);
	}


	TEST(gethealth){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer, 28);

		CHECK(testactor.getCurrentHealth() == 28);
		CHECK(testactor.getMaxHealth() == 28);
	}

	TEST(receiveAttack_mortal){
		int max_health = 28;
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer, max_health);
		Attack testattack(max_health/2);
		CHECK(testactor.getCurrentHealth() == max_health);

		testactor.recieveAttack(testattack);
		CHECK(testactor.getCurrentHealth() == max_health/2);
		CHECK(testactor.getMaxHealth() == max_health);

		testactor.recieveAttack(testattack);
		CHECK(testactor.getCurrentHealth() == 0);
		testactor.recieveAttack(testattack);
		CHECK(testactor.getCurrentHealth() == 0);

		Attack testheal(-max_health);
		testactor.recieveAttack(testheal);
		CHECK(testactor.getCurrentHealth() == max_health);
		testactor.recieveAttack(testheal);
		CHECK(testactor.getCurrentHealth() == max_health);
	}

	TEST(receiveAttack_immortal){
		int damage = 28;
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer);
		Attack testattack(damage);
		CHECK(testactor.getCurrentHealth() == -1);
		CHECK(testactor.getMaxHealth() == -1);

		testactor.recieveAttack(testattack);
		CHECK(testactor.getCurrentHealth() == -1);
		CHECK(testactor.getMaxHealth() == -1);
	}

	TEST(isalive_mortal){
		int max_health = 28;
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer, max_health);
		Attack testattack(max_health);

		CHECK(testactor.isAlive() == true);
		testactor.recieveAttack(testattack);
		CHECK(testactor.isAlive() == false);
	}

	TEST(isalive_immortal){
		int damage = 28;
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer);
		Attack testattack(damage);

		CHECK(testactor.isAlive() == true);
		testactor.recieveAttack(testattack);
		CHECK(testactor.isAlive() == true);
	}

	TEST(getType){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer);
		CHECK(testactor.getType() == BOARDACTOR);
	}

//	void setAnimation_Moving();
//	void setAnimation_Idle();
	TEST(setAnimation){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate(1,2), testplayer);

		CHECK(testactor.isMoving() == false);
		testactor.setAnimation_Moving();
		CHECK(testactor.isMoving() == true);
		testactor.setAnimation_Moving();
		CHECK(testactor.isMoving() == true);
		testactor.setAnimation_Idle();
		CHECK(testactor.isMoving() == false);
		testactor.setAnimation_Idle();
		CHECK(testactor.isMoving() == false);
	}



//	bool isMoving();
//	void startMove(std::vector<Coordinate> path);
//	void stopMove();
//	void moveStep();
//	Coordinate getNextStep();
//	Coordinate getDestination();

	TEST(movepath_generation_toosmall){
		Player testplayer("tester1", true);
		Coordinate startloc(1,2);
		BoardActor testactor(startloc, testplayer);

		std::vector<Coordinate> test_path;
		test_path.clear();

		testactor.startMove(test_path);
		CHECK(testactor.isMoving() == false);
		testactor.moveStep();
		CHECK(testactor.isMoving() == false);
		CHECK(testactor.getLocation() == startloc);

		test_path.push_back(Coordinate(1,3));
		testactor.startMove(test_path);
		CHECK(testactor.isMoving() == false);
		testactor.moveStep();
		CHECK(testactor.isMoving() == false);
		CHECK(testactor.getLocation() == startloc);
	}

	TEST(movepath_generation_small){
		Player testplayer("tester1", true);
		Coordinate startloc(1,2);
		BoardActor testactor(startloc, testplayer);

		std::vector<Coordinate> test_path;
		test_path.clear();

		test_path.push_back(Coordinate(1,3));
		test_path.push_back(startloc);

		CHECK(testactor.getLocation() == startloc);
		int speed = testactor.getMoveSpeed();
		testactor.startMove(test_path);
		CHECK(testactor.getDestination() == test_path[0]);

		for(int i = test_path.size()-1; i > -1 ; i--){
			CHECK(testactor.getLocation() == test_path[i]);
			for(int j = 0; j < speed; j++){
				testactor.moveStep();
			}
		}
		CHECK(testactor.getLocation() == test_path[0]);
	}

	TEST(movepath_generation_long){
		Player testplayer("tester1", true);
		Coordinate startloc(4,3);
		BoardActor testactor(startloc, testplayer);

		std::vector<Coordinate> test_path;
		test_path.clear();

		test_path.push_back(Coordinate(0,0));
		test_path.push_back(Coordinate(60,4000));
		test_path.push_back(Coordinate(5,200));
		test_path.push_back(Coordinate(0,4));
		test_path.push_back(Coordinate(1,3));
		test_path.push_back(Coordinate(1,2));
		test_path.push_back(Coordinate(1,3));
		test_path.push_back(Coordinate(2,3));
		test_path.push_back(Coordinate(3,3));
		test_path.push_back(startloc);

		CHECK(testactor.getLocation() == startloc);
		int speed = testactor.getMoveSpeed();
		testactor.startMove(test_path);
		CHECK(testactor.getDestination() == test_path[0]);

		for(int i = test_path.size()-1; i > -1 ; i--){
			CHECK(testactor.getLocation() == test_path[i]);
			for(int j = 0; j < speed; j++){
				testactor.moveStep();
			}
		}
		CHECK(testactor.getLocation() == test_path[0]);
	}

//	void update();
	TEST(update){
		Player testplayer("tester1", true);
		Coordinate startloc(4,3);
		BoardActor testactor(startloc, testplayer);

		Frame black(std::make_tuple<int,int,int>(0,0,0), .04);
		Frame red(std::make_tuple<int,int,int>(255,0,0), .04);
		Frame green(std::make_tuple<int,int,int>(0,255,0), .04);

		CHECK(testactor.getCurrentAnimationFrame() == red);
		CHECK(testactor.getLocation() == startloc);
		testactor.update();
		CHECK(testactor.getCurrentAnimationFrame() == black);
		CHECK(testactor.getLocation() == startloc);
		testactor.update();
		CHECK(testactor.getCurrentAnimationFrame() == red);
		CHECK(testactor.getLocation() == startloc);

		std::vector<Coordinate> test_path;
		test_path.clear();

		test_path.push_back(Coordinate(0,0));
		test_path.push_back(Coordinate(60,4000));
		test_path.push_back(Coordinate(5,200));
		test_path.push_back(Coordinate(1,4));
		test_path.push_back(Coordinate(1,3));
		test_path.push_back(Coordinate(1,1));
		test_path.push_back(Coordinate(777777,1000000));
		test_path.push_back(Coordinate(0,0));
		test_path.push_back(Coordinate(99,0));
		test_path.push_back(startloc);

		CHECK(testactor.getLocation() == startloc);
		int speed = testactor.getMoveSpeed();
		testactor.startMove(test_path);
		CHECK(testactor.getDestination() == test_path[0]);
		bool evenstep = true;
		for(int i = test_path.size()-1; i > -1 ; i--){
			CHECK(testactor.getLocation() == test_path[i]);
			for(int j = 0; j < speed; j++){
				if(evenstep){
					if(i == 0){
						CHECK(testactor.getCurrentAnimationFrame() == red);
					}else{
						CHECK(testactor.getCurrentAnimationFrame() == green);
					}
				}else{
					CHECK(testactor.getCurrentAnimationFrame() == black);
				}
				testactor.update();
				evenstep = !evenstep;
			}
		}
		CHECK(testactor.getLocation() == test_path[0]);
	}
}





