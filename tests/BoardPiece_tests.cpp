#include "BoardPiece.h"
#include "Attack.h"
#include "UnitTest++.h"


SUITE(BoardPiece){
	TEST(boardpiece_constructor_default)
	{
		std::cerr << "Testing BoardPiece\n";
		BoardPiece testpiece;
		CHECK(testpiece.getLocation() == Coordinate3D<int>(-1,-1,-1));
	}

	TEST(boardpiece_constructor_coord){
		BoardPiece testpiece(Coordinate3D<int>(1,2,1));
		CHECK(testpiece.getLocation() == Coordinate3D<int>(1,2,1));
	}

	TEST(boardpiece_hitpoint_constructors){
		BoardPiece testpiece(Coordinate3D<int>(1,2,1), 100);
		CHECK(testpiece.getLocation() == Coordinate3D<int>(1,2,1));
		CHECK(testpiece.getMaxHealth() == 100);
		CHECK(testpiece.getCurrentHealth() == 100);

		BoardPiece testpiece_2(100);
		CHECK(testpiece_2.getLocation() == Coordinate3D<int>(-1,-1,-1));
		CHECK(testpiece_2.getMaxHealth() == 100);
		CHECK(testpiece_2.getCurrentHealth() == 100);
	}

	TEST(receiveAttack){
		BoardPiece testpiece(100);
		Attack testattack(28);

		CHECK(testpiece.getCurrentHealth() == 100);
		CHECK(testpiece.getMaxHealth() == 100);
		testpiece.recieveAttack(testattack);
		CHECK(testpiece.getCurrentHealth() == 72);
		CHECK(testpiece.getMaxHealth() == 100);
		testpiece.recieveAttack(testattack);
		testpiece.recieveAttack(testattack);
		testpiece.recieveAttack(testattack);
		CHECK(testpiece.getCurrentHealth() == 0);
		CHECK(testpiece.getMaxHealth() == 100);
	}


	//	Frame& getCurrentAnimationFrame();
	//	void updateAnimation();
	//	void resetAnimation();
	//  void setAnimation(const Animation& new_animation);
	TEST(updating_resetting_animations){
		Frame black(std::make_tuple<int,int,int>(0,0,0), .05);
		Frame red(std::make_tuple<int,int,int>(255,0,0), .05);
		Frame green(std::make_tuple<int,int,int>(0,255,0), .05);

		Animation r_b;
		r_b.addFrame(red);
		r_b.addFrame(black);

		Animation g_b(false);
		g_b.addFrame(green);
		g_b.addFrame(black);

		BoardPiece testpiece(Coordinate3D<int>(1,2,1));

		testpiece.setAnimation(r_b);
		CHECK(testpiece.getCurrentAnimationFrame() == red);
		CHECK(testpiece.updateAnimation() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		CHECK(testpiece.updateAnimation() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == red);
		CHECK(testpiece.updateAnimation() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		testpiece.resetAnimation();
		CHECK(testpiece.getCurrentAnimationFrame() == red);

		testpiece.setAnimation(g_b);
		CHECK(testpiece.getCurrentAnimationFrame() == green);
		CHECK(testpiece.updateAnimation() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		CHECK(testpiece.updateAnimation() == false);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		CHECK(testpiece.updateAnimation() == false);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		testpiece.resetAnimation();
		CHECK(testpiece.getCurrentAnimationFrame() == green);
		CHECK(testpiece.updateAnimation() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		testpiece.resetAnimation();
		CHECK(testpiece.getCurrentAnimationFrame() == green);
	}

	TEST(update){
		Frame black(std::make_tuple<int,int,int>(0,0,0), .05);
		Frame red(std::make_tuple<int,int,int>(255,0,0), .05);

		Animation r_b;
		r_b.addFrame(red);
		r_b.addFrame(black);

		BoardPiece testpiece(Coordinate3D<int>(1,2,1));

		testpiece.setAnimation(r_b);
		CHECK(testpiece.getCurrentAnimationFrame() == red);
		CHECK(testpiece.update() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		CHECK(testpiece.update() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == red);
		CHECK(testpiece.update() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == black);
		CHECK(testpiece.update() == true);
		CHECK(testpiece.getCurrentAnimationFrame() == red);

	}

}
