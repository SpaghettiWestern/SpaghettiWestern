#include "GameBoard.h"
#include "Player.h"
#include "UnitTest++.h"

#include <memory>
#include <exception>

SUITE(GameBoardStructure){
	TEST(constructor_default){
		std::cerr << "Testing GameBoardStructure\n";
		int length = 20;
		int width = 20;
		int height = 20;

		GameBoardStructure testboard(length, width, height);
		for(int i = 0; i < width; i++){
			for(int j = 0; j < length; j++){
				for(int k = 0; k < height; k++){
					CHECK(testboard.getEnvironmentPiece(i,j,k).getLocation() == Coordinate3D<int>(i,j,k));
				}
			}
		}

		CHECK(testboard.getLength() == length);
		CHECK(testboard.getWidth() == width);
		CHECK(testboard.getHeight() == height);
	}

	TEST(constructor_dimensions){
		int length = 40;
		int width = 30;
		int height = 5;

		GameBoardStructure testboard(length, width);
		for(int i = 0; i < width; i++){
			for(int j = 0; j < length; j++){
				for(int k =0; k < height; k++){
					CHECK(testboard.getEnvironmentPiece(i,j,k).getLocation() == Coordinate3D<int>(i,j,k));
				}
			}
		}

		CHECK(testboard.getLength() == length);
		CHECK(testboard.getWidth() == width);
		CHECK(testboard.getHeight() == height);
	}

	TEST(openSpace){
		GameBoardStructure testboard(3,3,1);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate3D<int>(0,0,0), testplayer));

		testboard.addActor(testact);

		CHECK(testboard.openSpace(Coordinate3D<int>(0,0,0)) == false);
		testboard.removeActor(Coordinate3D<int>(1,1,0));
		CHECK(testboard.openSpace(Coordinate3D<int>(1,1,0)) == true);
	}

	TEST(inBounds){
		//(length, width)
		GameBoardStructure testboard(3,4,2);
		//(x,y)
		CHECK(testboard.inBounds(Coordinate3D<int>(0,0,1)) == true);
		CHECK(testboard.inBounds(Coordinate3D<int>(3,2,1)) == true);
		CHECK(testboard.inBounds(Coordinate3D<int>(1,1,1)) == true);
		CHECK(testboard.inBounds(Coordinate3D<int>(-1,-1,1)) == false);
		CHECK(testboard.inBounds(Coordinate3D<int>(4,3,1)) == false);
		CHECK(testboard.inBounds(Coordinate3D<int>(-1,2,1)) == false);
		CHECK(testboard.inBounds(Coordinate3D<int>(2,-1,1)) == false);
		CHECK(testboard.inBounds(Coordinate3D<int>(2,3,1)) == false);
		CHECK(testboard.inBounds(Coordinate3D<int>(4,2,1)) == false);
	}

	TEST(actorExists){
		GameBoardStructure testboard(3,3,1);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate3D<int>(1,0,0), testplayer));
		testboard.addActor(testact);

		CHECK(testboard.actorExists(Coordinate3D<int>(1,0,0)) == true);
		CHECK(testboard.actorExists(Coordinate3D<int>(0,1,0)) == false);
	}

	TEST(addActor){
		GameBoardStructure testboard(3,3,1);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate3D<int>(1,0,0), testplayer));
		CHECK(testboard.addActor(testact) == true);
		CHECK(testboard.addActor(testact) == false);

	}

	TEST(removeActor){
		GameBoardStructure testboard(3,3,1);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate3D<int>(0,0,0), testplayer));
		testboard.addActor(testact);
		CHECK(testboard.actorExists(Coordinate3D<int>(0,0,0)) == true);
		testboard.removeActor(Coordinate3D<int>(0,0,0));
		CHECK(testboard.actorExists(Coordinate3D<int>(0,0,0)) == false);
	}

	TEST(moveActor){
		GameBoardStructure testboard(3,3,1);
		Player testplayer("tester1", true);
		std::shared_ptr<BoardActor> testact(new BoardActor(Coordinate3D<int>(0,0,0), testplayer));
		testboard.addActor(testact);
		CHECK(testboard.actorExists(Coordinate3D<int>(0,0,0)) == true);
		CHECK(testboard.actorExists(Coordinate3D<int>(1,1,0)) == false);
		CHECK(testboard.getActor(0,0)->getLocation() == Coordinate3D<int>(0,0,0));

		CHECK(testboard.moveActor(Coordinate3D<int>(0,0,0), Coordinate3D<int>(1,1,0)) == true);
		CHECK(testboard.actorExists(Coordinate3D<int>(0,0,0)) == false);
		CHECK(testboard.actorExists(Coordinate3D<int>(1,1,0)) == true);
		CHECK(testboard.getActor(1,1)->getLocation() == Coordinate3D<int>(1,1,0));

		CHECK(testboard.moveActor(Coordinate3D<int>(1,1,0), Coordinate3D<int>(1,2,0)) == true);
		CHECK(testboard.actorExists(Coordinate3D<int>(1,1,0)) == false);
		CHECK(testboard.actorExists(Coordinate3D<int>(1,2,0)) == true);
		CHECK(testboard.getActor(1,2,0)->getLocation() == Coordinate3D<int>(1,2,0));

		CHECK(testboard.moveActor(Coordinate3D<int>(1,2,0), Coordinate3D<int>(1,1,0)) == true);
		CHECK(testboard.actorExists(Coordinate3D<int>(1,2,0)) == false);
		CHECK(testboard.actorExists(Coordinate3D<int>(1,1,0)) == true);
		CHECK(testboard.getActor(1,1)->getLocation() == Coordinate3D<int>(1,1,0));

		CHECK(testboard.moveActor(Coordinate3D<int>(0,1,0), Coordinate3D<int>(1,0,0)) == false);
	}

	bool test_addEffect(const Coordinate3D<int>& s_loc, std::unique_ptr<Effect>& effect, GameBoardStructure& test_board, int curr_effect_num){
		CHECK(test_board.numEffects(s_loc) == curr_effect_num);
		if(curr_effect_num > 0){
			CHECK(test_board.effectsExist(s_loc) == true);
		}else{
			CHECK(test_board.effectsExist(s_loc) == false);
		}
		test_board.addBoardEffect(effect);
		CHECK(test_board.effectsExist(s_loc) == true);
		CHECK(test_board.numEffects(s_loc) == curr_effect_num+1);
		if(test_board.numEffects(s_loc) == curr_effect_num+1){
			return true;
		}
		return false;
	}


//	const std::map<Coordinate, std::vector<std::unique_ptr<Effect>>>& getEffects() const;
//	const std::vector<std::unique_ptr<Effect>>& getEffects(const Coordinate& loc) const;
//	const Effect& getEffect(const Coordinate& loc) const;
//	int numEffects(const Coordinate& loc) const;
//	bool effectsExist(const Coordinate& loc) const;
//	bool addEffect(std::unique_ptr<Effect>& new_effect);
	TEST(add_get_move_effects){
		GameBoardStructure test_board(3,3,1);
		std::vector<Coordinate3D<int>> s_loc = {Coordinate3D<int>(1,2,0), Coordinate3D<int>(0,2,0),
				Coordinate3D<int>(0,2,0), Coordinate3D<int>(-1,3,0)};

		CHECK(test_board.getEffects().size() == 0);

		std::unique_ptr<Effect> tmp_effect(new Effect(Util::coordToScreen(s_loc[0])));
		Effect& test_effect0 = *tmp_effect;
		test_addEffect(s_loc[0], tmp_effect, test_board, 0);

		tmp_effect.reset(new Effect(Util::coordToScreen(s_loc[1])));
		Effect& test_effect1 = *tmp_effect;
		test_addEffect(s_loc[1], tmp_effect, test_board, 0);

		tmp_effect.reset(new Effect(Util::coordToScreen(s_loc[2])));
		Effect& test_effect2 = *tmp_effect;
		test_addEffect(s_loc[2], tmp_effect, test_board, 1);

		tmp_effect.reset(new Effect(Util::coordToScreen(s_loc[3])));
		CHECK(test_board.effectsExist(s_loc[3]) == false);
		CHECK(test_board.numEffects(s_loc[3]) == 0);
		test_board.addBoardEffect(tmp_effect);
		CHECK(test_board.effectsExist(s_loc[3]) == false);
		CHECK(test_board.numEffects(s_loc[3]) == 0);

		CHECK(&test_board.getEffect(s_loc[0]) == &test_effect0);
		CHECK(&(*(test_board.getEffects(s_loc[0]).back())) == &test_effect0);

		CHECK(&test_board.getEffect(s_loc[1]) == &test_effect2);
		const std::vector<std::unique_ptr<Effect>>& test_effects = test_board.getEffects(s_loc[1]);
		if(test_effects.size() > 1){
			CHECK(&(*test_effects[0]) == &test_effect1);
			CHECK(&(*test_effects[1]) == &test_effect2);
		}

		CHECK(test_board.getEffects().size() == 2);
	}

	TEST(update_movingeffect){
		GameBoardStructure test_board(3,3,1);
		std::vector<Coordinate3D<int>> path = {Coordinate3D<int>(0,0,0), Coordinate3D<int>(0,1,0),
				Coordinate3D<int>(0,2,0), Coordinate3D<int>(1,2,0), Coordinate3D<int>(0,1,0)};

		std::vector<ScreenCoordinate> test_path = {Util::coordToScreen(path[4]), Util::coordToScreen(path[3]),
				Util::coordToScreen(path[2]), Util::coordToScreen(path[1])};

		std::unique_ptr<Effect> tmp_effect(new MovingEffect(Util::coordToScreen(path[0]), test_path));
		MovingEffect& test_effect = (MovingEffect&)(*tmp_effect);
		test_board.addBoardEffect(tmp_effect);


		test_effect.startMove();
		CHECK(test_effect.getScreenLocation() == Util::coordToScreen(path[0]));

		for(unsigned int i = 0; i < path.size(); i++){
			CHECK(test_board.numEffects(path[i]) == 1);
			CHECK(Util::screenToCoord(test_effect.getScreenLocation()) == path[i]);
			test_board.update();
			CHECK(test_board.numEffects(path[i]) == 0);
		}
		CHECK(test_board.numEffects(path[4]) == 0);
		CHECK(test_board.getEffects().size() == 0);
	}
}
















