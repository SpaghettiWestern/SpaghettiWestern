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
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer);
		CHECK(testactor.getLocation() == Coordinate3D<int>(1,2,1));
		CHECK(testactor.getCurrentHealth() == -1);
		CHECK(testactor.getMaxHealth() == -1);
		CHECK(testactor.getOwner().getName().compare("tester1") == 0);
	}

	TEST(healthconstructor){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer, 28);
		CHECK(testactor.getLocation() == Coordinate3D<int>(1,2,1));
		CHECK(testactor.getCurrentHealth() == 28);
		CHECK(testactor.getMaxHealth() == 28);
		CHECK(testactor.getOwner().getName().compare("tester1") == 0);
	}


	TEST(gethealth){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer, 28);

		CHECK(testactor.getCurrentHealth() == 28);
		CHECK(testactor.getMaxHealth() == 28);
	}

	TEST(receiveAttack_mortal){
		int max_health = 28;
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer, max_health);
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
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer);
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
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer, max_health);
		Attack testattack(max_health);

		CHECK(testactor.isAlive() == true);
		testactor.recieveAttack(testattack);
		CHECK(testactor.isAlive() == false);
	}

	TEST(isalive_immortal){
		int damage = 28;
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer);
		Attack testattack(damage);

		CHECK(testactor.isAlive() == true);
		testactor.recieveAttack(testattack);
		CHECK(testactor.isAlive() == true);
	}

	TEST(getType){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer);
		CHECK(testactor.getType() == BOARDACTOR);
	}

//	void setAnimation_Moving();
//	void setAnimation_Idle();
	TEST(setAnimation){
		Player testplayer("tester1", true);
		BoardActor testactor(Coordinate3D<int>(1,2,1), testplayer);

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
		Coordinate3D<int> startloc(1,2,1);
		BoardActor testactor(startloc, testplayer);

		std::vector<Coordinate3D<int>> test_path;
		test_path.clear();

		testactor.startMove(test_path);
		CHECK(testactor.isMoving() == false);
		testactor.moveStep();
		CHECK(testactor.isMoving() == false);
		CHECK(testactor.getLocation() == startloc);

		test_path.push_back(Coordinate3D<int>(1,3,1));
		testactor.startMove(test_path);
		CHECK(testactor.isMoving() == false);
		testactor.moveStep();
		CHECK(testactor.isMoving() == false);
		CHECK(testactor.getLocation() == startloc);
	}

	TEST(movepath_generation_small){
		Player testplayer("tester1", true);
		Coordinate3D<int> startloc(1,2,1);
		BoardActor testactor(startloc, testplayer);

		std::vector<Coordinate3D<int>> test_path;
		test_path.clear();

		test_path.push_back(Coordinate3D<int>(1,3,1));
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
		Coordinate3D<int> startloc(4,3,1);
		BoardActor testactor(startloc, testplayer);

		std::vector<Coordinate3D<int>> test_path;
		test_path.clear();

		test_path.push_back(Coordinate3D<int>(0,0,1));
		test_path.push_back(Coordinate3D<int>(60,4000,1));
		test_path.push_back(Coordinate3D<int>(5,200,1));
		test_path.push_back(Coordinate3D<int>(0,4,1));
		test_path.push_back(Coordinate3D<int>(1,3,1));
		test_path.push_back(Coordinate3D<int>(1,2,1));
		test_path.push_back(Coordinate3D<int>(1,3,1));
		test_path.push_back(Coordinate3D<int>(2,3,1));
		test_path.push_back(Coordinate3D<int>(3,3,1));
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
		Coordinate3D<int> startloc(4,3,1);
		BoardActor testactor(startloc, testplayer);

		Frame idle1(Coordinate2D<double>(.25,0), Coordinate2D<double>(.5,1), .04);
		Frame idle2(Frame(Coordinate2D<double>(.75,0), Coordinate2D<double>(1,1), .04));
		Frame move1(Frame(Coordinate2D<double>(0,0), Coordinate2D<double>(.25,1), .04));
		Frame move2(Frame(Coordinate2D<double>(.5,0), Coordinate2D<double>(.75,1), .04));

		CHECK(testactor.getCurrentAnimationFrame() == idle1);
		CHECK(testactor.getLocation() == startloc);
		testactor.update();
		CHECK(testactor.getCurrentAnimationFrame() == idle2);
		CHECK(testactor.getLocation() == startloc);
		testactor.update();
		CHECK(testactor.getCurrentAnimationFrame() == idle1);
		CHECK(testactor.getLocation() == startloc);

		std::vector<Coordinate3D<int>> test_path;
		test_path.clear();

		test_path.push_back(Coordinate3D<int>(0,0,1));
		test_path.push_back(Coordinate3D<int>(60,4000,1));
		test_path.push_back(Coordinate3D<int>(5,200,1));
		test_path.push_back(Coordinate3D<int>(1,4,1));
		test_path.push_back(Coordinate3D<int>(1,3,1));
		test_path.push_back(Coordinate3D<int>(1,1,1));
		test_path.push_back(Coordinate3D<int>(777777,1000000,1));
		test_path.push_back(Coordinate3D<int>(0,0,1));
		test_path.push_back(Coordinate3D<int>(99,0,1));
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
						CHECK(testactor.getCurrentAnimationFrame() == idle1);
					}else{
						CHECK(testactor.getCurrentAnimationFrame() == move1);
					}
				}else{
					if(i == 0){
						CHECK(testactor.getCurrentAnimationFrame() == idle2);
					}else{
						CHECK(testactor.getCurrentAnimationFrame() == move2);
					}
				}
				testactor.update();
				evenstep = !evenstep;
			}
		}
		CHECK(testactor.getLocation() == test_path[0]);
	}
}





