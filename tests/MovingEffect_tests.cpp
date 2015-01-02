#include "UnitTest++.h"
#include "MovingEffect.h"

SUITE(MovingEffect){


//	MovingEffect();
	TEST(constructor_default){
		std::cerr << "Testing MovingEffects\n";

		MovingEffect test_effect;
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == false);
		CHECK(test_effect.getType() == MOVINGEFFECT);
		//CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}

//	MovingEffect(ScreenCoordinate loc);
	TEST(constructor_location){
		ScreenCoordinate loc(1.0,28.0);
		MovingEffect test_effect(loc);

		CHECK(test_effect.getScreenLocation() == loc);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == false);
		CHECK(test_effect.getType() == MOVINGEFFECT);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}
//	MovingEffect(ScreenCoordinate loc, const Animation& anim);
	TEST(constructor_loc_animation){
		ScreenCoordinate s_loc(10.15,73.0);
		Frame black(std::make_tuple<int,int,int>(0,0,0), .01);
		Frame yellow(std::make_tuple<int,int,int>(255,255,0), .01);
		Animation test_anim;
		test_anim.addFrame(black);
		test_anim.addFrame(yellow);

		MovingEffect test_effect(s_loc, test_anim);
		CHECK(test_effect.getType() == MOVINGEFFECT);
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getCurrentAnimationFrame() == black);
		test_effect.update();
		CHECK(test_effect.getCurrentAnimationFrame() == yellow);

		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == false);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}
//	MovingEffect(ScreenCoordinate loc, const std::vector<ScreenCoordinate>& path);
	TEST(constructor_loc_path){
		ScreenCoordinate s_loc(-12.3,28.0);
		std::vector<ScreenCoordinate> test_path;

		ScreenCoordinate path0(0.0,12.3);
		test_path.push_back(path0);

		MovingEffect test_effect(s_loc, test_path);
		CHECK(test_effect.getType() == MOVINGEFFECT);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == true);
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getNextStep() == path0);
		test_effect.update();
		CHECK(test_effect.getScreenLocation() == path0);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}

//	MovingEffect(ScreenCoordinate loc, const Animation& anim, const std::vector<ScreenCoordinate>& path);
	TEST(constructor_loc_anim_path){
		ScreenCoordinate s_loc(10.15,73.0);
		Frame black(std::make_tuple<int,int,int>(0,0,0), .01);
		Frame yellow(std::make_tuple<int,int,int>(255,255,0), .01);
		Animation test_anim;
		test_anim.addFrame(black);
		test_anim.addFrame(yellow);
		std::vector<ScreenCoordinate> test_path;
		ScreenCoordinate path0(0.0,12.3);
		test_path.push_back(path0);

		MovingEffect test_effect(s_loc, test_anim, test_path);
		CHECK(test_effect.getType() == MOVINGEFFECT);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == true);

		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getNextStep() == path0);
		CHECK(test_effect.getCurrentAnimationFrame() == black);
		test_effect.update();
		CHECK(test_effect.getScreenLocation() == path0);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
		CHECK(test_effect.getCurrentAnimationFrame() == yellow);
	}

//	void setPath(const std::vector<ScreenCoordinate>& new_path);
	TEST(setPath){
		ScreenCoordinate s_loc(1.1,2.2);
		MovingEffect test_effect(s_loc);
		std::vector<ScreenCoordinate> test_path;
		ScreenCoordinate path0(3.3, 4.4);
		test_path.push_back(path0);

		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == false);
		test_effect.setPath(test_path);
		CHECK(test_path.empty() == false);
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getNextStep() == path0);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == true);
		CHECK(test_effect.isMoving() == true);
		test_effect.update();
		CHECK(test_effect.getScreenLocation() == path0);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}

//	void transferPath(std::vector<ScreenCoordinate>& new_path);
	TEST(transferPath){
		ScreenCoordinate s_loc(1.1,2.2);
		MovingEffect test_effect(s_loc);
		std::vector<ScreenCoordinate> test_path;
		ScreenCoordinate path0(3.3, 4.4);
		test_path.push_back(path0);

		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == false);
		test_effect.transferPath(test_path);
		CHECK(test_path.empty() == true);
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getNextStep() == path0);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == true);
		CHECK(test_effect.isMoving() == true);
		test_effect.update();
		CHECK(test_effect.getScreenLocation() == path0);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}
//	void generatePath(const ScreenCoordinate& dest, double speed);
	TEST(generatePath){
		ScreenCoordinate s_loc(0.0,0.0);
		MovingEffect test_effect(s_loc);
		ScreenCoordinate d_loc(0.0, 1.0);
		double test_speed = 1.0;

		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == false);

		test_effect.generatePath(d_loc, test_speed);
		CHECK(test_effect.startMove() == true);
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.isMoving() == true);
		CHECK(test_effect.getNextStep() == d_loc);
		test_effect.update();
		CHECK(test_effect.getScreenLocation() == d_loc);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}

//	bool startMove();
//	void stopMove();
//	bool isMoving() const;
//	bool moveStep();
//	ScreenCoordinate getNextStep() const;
	TEST(moving){
		ScreenCoordinate s_loc(0.0,0.0);
		ScreenCoordinate path0(0.0,1.0);
		ScreenCoordinate path1(1.0,1.0);
		ScreenCoordinate path2(3.1244545663, -0.111111);
		std::vector<ScreenCoordinate> test_path = {path2, path1, path0};

		MovingEffect test_effect(s_loc, test_path);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == true);
		CHECK(test_effect.getScreenLocation() == s_loc);
		while(!test_path.empty()){
			ScreenCoordinate step_loc = test_path.back();
			test_path.pop_back();

			CHECK(test_effect.getNextStep() == step_loc);
			CHECK(test_effect.moveStep() == true);
			CHECK(test_effect.getScreenLocation() == step_loc);
		}
		CHECK(test_effect.getScreenLocation() == path2);
		CHECK(test_effect.isMoving() == true);
		CHECK(test_effect.moveStep() == false);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.getScreenLocation() == path2);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}

//	virtual effect_type getType() const;
	TEST(getType){
		MovingEffect test_effect;
		CHECK(test_effect.getType() == MOVINGEFFECT);
	}

//	virtual void update();
	TEST(update){
		ScreenCoordinate s_loc(0.0,0.0);
		ScreenCoordinate path0(0.0,1.0);
		ScreenCoordinate path1(1.0,1.0);
		ScreenCoordinate path2(3.1244545663, -0.111111);

		Frame black(std::make_tuple<int,int,int>(0,0,0), .01);
		Frame yellow(std::make_tuple<int,int,int>(255,255,0), .01);
		Animation test_anim;
		test_anim.addFrame(black);
		test_anim.addFrame(yellow);

		std::vector<ScreenCoordinate> test_path = {path2, path1, path0};

		MovingEffect test_effect(s_loc, test_anim, test_path);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.startMove() == true);
		CHECK(test_effect.getScreenLocation() == s_loc);
		for(unsigned int i = 0; !test_path.empty(); i++){
			if(i%2 == 0)
				CHECK(test_effect.getCurrentAnimationFrame() == black);
			else
				CHECK(test_effect.getCurrentAnimationFrame() == yellow);

			ScreenCoordinate step_loc = test_path.back();
			test_path.pop_back();

			CHECK(test_effect.getNextStep() == step_loc);
			test_effect.update();
			CHECK(test_effect.getScreenLocation() == step_loc);
		}
		CHECK(test_effect.getScreenLocation() == path2);
		CHECK(test_effect.getCurrentAnimationFrame() == yellow);
		CHECK(test_effect.isMoving() == true);
		test_effect.update();
		CHECK(test_effect.getCurrentAnimationFrame() == black);
		CHECK(test_effect.isMoving() == false);
		CHECK(test_effect.getScreenLocation() == path2);
		CHECK(test_effect.getNextStep() == ScreenCoordinate(-1.0,-1.0));
	}

}
