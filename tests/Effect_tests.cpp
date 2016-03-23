#include "UnitTest++.h"
#include "Effect.h"

SUITE(Effect){
	//Effect();
	TEST(constructor_defaut){
		std::cerr << "Testing Effects\n";

		Coordinate2D<double> s_loc(0.0,0.0);
		Frame black(std::make_tuple<int,int,int>(0,0,0), .01);
		Frame blue(std::make_tuple<int,int,int>(0,0,255), .01);

		Effect test_effect;
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getCurrentAnimationFrame() == blue);
		test_effect.update();
		CHECK(test_effect.getCurrentAnimationFrame() == black);
	}

	//Effect(ScreenCoordinate loc);
	TEST(constructor_loc){
		Coordinate2D<double> s_loc(10.15,73.0);
		Frame black(std::make_tuple<int,int,int>(0,0,0), .01);
		Frame blue(std::make_tuple<int,int,int>(0,0,255), .01);

		Effect test_effect(s_loc);
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getCurrentAnimationFrame() == blue);
		test_effect.update();
		CHECK(test_effect.getCurrentAnimationFrame() == black);
	}

	//Effect(ScreenCoordinate loc, Animation animation);
	TEST(constructor_loc_anim){
		Coordinate2D<double> s_loc(10.15,73.0);
		Frame black(std::make_tuple<int,int,int>(0,0,0), .01);
		Frame yellow(std::make_tuple<int,int,int>(255,255,0), .01);
		Animation test_anim;
		test_anim.addFrame(black);
		test_anim.addFrame(yellow);

		Effect test_effect(s_loc, test_anim);
		CHECK(test_effect.getScreenLocation() == s_loc);
		CHECK(test_effect.getCurrentAnimationFrame() == black);
		test_effect.update();
		CHECK(test_effect.getCurrentAnimationFrame() == yellow);
	}

	//const ScreenCoordinate& getScreenLocation();
	//void setScreenLocation(const ScreenCoordinate& new_loc);
	TEST(get_set_screenCoordinate){
		Coordinate2D<double> start_loc(10.15,73.0);
		Coordinate2D<double> new_loc(28.0, 32.1);

		Effect testeffect(start_loc);
		CHECK(testeffect.getScreenLocation() == start_loc);
		testeffect.setScreenLocation(new_loc);
		CHECK(testeffect.getScreenLocation() == new_loc);
	}

	//void setAnimation(const Animation& new_animation);
	//const Frame& getCurrentAnimationFrame();
	//void update();
	TEST(set_animation){
		Coordinate2D<double> s_loc(99999.0,111.0);
		Frame black(std::make_tuple<int,int,int>(0,0,0), .01);
		Frame blue(std::make_tuple<int,int,int>(0,0,255), .01);
		Frame yellow(std::make_tuple<int,int,int>(255,255,0), .01);

		Animation test_anim;
		test_anim.addFrame(black);
		test_anim.addFrame(yellow);

		Effect testeffect(s_loc);
		CHECK(testeffect.getScreenLocation() == s_loc);
		CHECK(testeffect.getCurrentAnimationFrame() == blue);
		testeffect.update();
		CHECK(testeffect.getCurrentAnimationFrame() == black);
		testeffect.update();
		CHECK(testeffect.getCurrentAnimationFrame() == blue);
		testeffect.setAnimation(test_anim);
		CHECK(testeffect.getCurrentAnimationFrame() == black);
		testeffect.update();
		CHECK(testeffect.getCurrentAnimationFrame() == yellow);
		testeffect.update();
		CHECK(testeffect.getCurrentAnimationFrame() == black);
	}

	TEST(getType){
		Effect testeffect;
		CHECK(testeffect.getType() == EFFECT);
	}
}

