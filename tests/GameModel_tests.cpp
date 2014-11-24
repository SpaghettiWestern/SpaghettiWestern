#include "GameModel.h"
#include "UnitTest++.h"

#include <vector>
#include <string>
#include <utility>

SUITE(GameModel){

	TEST(constructor_noplayers){
		GameModel testmodel(50, 30);
		CHECK(testmodel.getGameBoard().getBoard().getLength() == 50);
		CHECK(testmodel.getGameBoard().getBoard().getWidth() == 30);
		CHECK(testmodel.getPlayers().size() == 0);

	}

	TEST(constructor_players){
		std::vector<std::pair<std::string, bool>> test_players =
			{std::make_pair("p1", true), std::make_pair("c1", false), std::make_pair("p2", true)};
		GameModel testmodel(50,30, test_players);

		CHECK(testmodel.getGameBoard().getBoard().getLength() == 50);
		CHECK(testmodel.getGameBoard().getBoard().getWidth() == 30);
		CHECK(testmodel.getPlayers().size() == test_players.size());
		for(unsigned int i = 0; i < test_players.size(); i++){
			CHECK(testmodel.getPlayers()[i].getName().compare(test_players[i].first) == 0);
			CHECK(testmodel.getPlayers()[i].isHuman() == test_players[i].second);
		}
	}

	void create_actor_test(GameModel& testmodel, Coordinate loc, int player, bool successful){
		std::vector<int> num_actors;
		for(unsigned int i = 0; i < testmodel.getPlayers().size(); i++)
			num_actors.push_back(testmodel.getPlayer(i).getNumActors());

		bool filled = testmodel.getGameBoard().getBoard().actorExists(loc);
		CHECK(testmodel.createActor(loc, player, 28) == successful);
		if(successful){
			CHECK(testmodel.getGameBoard().getBoard().actorExists(loc) == true);
			for(unsigned int i = 0; i < testmodel.getPlayers().size(); i++){
				if((int)i == player)
					CHECK(testmodel.getPlayer(i).actorExists(num_actors[i]) == true);
				else
					CHECK(testmodel.getPlayer(i).actorExists(num_actors[i]) == false);
			}
		}
		else{
			CHECK(testmodel.getGameBoard().getBoard().actorExists(loc) == filled);
			for(unsigned int i = 0; i < testmodel.getPlayers().size(); i++){
				CHECK(testmodel.getPlayer(i).actorExists(num_actors[i]) == false);
			}
		}
	}

	TEST(create_actor){
		std::vector<std::pair<std::string, bool>> test_players = {std::make_pair("p1", true), std::make_pair("p2", true)};
		GameModel testmodel(3,3, test_players);

		Coordinate testact1_loc(0,0);
		create_actor_test(testmodel, testact1_loc, 0, true);

		Coordinate testact2_loc(1,0);
		create_actor_test(testmodel, testact2_loc, 1, true);

		Coordinate testact3_loc(0,1);
		create_actor_test(testmodel, testact3_loc, 1, true);

		create_actor_test(testmodel, testact1_loc, 1, false);

		Coordinate bad_loc(-1, 4000);
		create_actor_test(testmodel, bad_loc, 0, false);
		Coordinate testact4_loc(1,1);
		create_actor_test(testmodel, testact4_loc, -1, false);
	}

}













