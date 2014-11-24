#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>
#include <string>
#include <utility>

#include "GameBoard.h"
#include "Player.h"
#include "BoardActor.h"
#include "ActionActor.h"
#include "Util.h"

class GameModel{
private:
	GameBoard board;
	std::vector<Player> players;

public:
	GameModel(int board_length, int board_width);
	GameModel(int board_length, int board_width, std::vector<std::pair<std::string, bool>> init_players);

	GameBoard& getGameBoard();
	std::vector<Player>& getPlayers();

	bool playerExists(int index);
	Player& getPlayer(int index);

	bool createActor(Coordinate loc, int owner_index, int hitpoints);
	bool createActor(Coordinate loc, int owner_index, int hitpoints, Attack attack);

	bool sendAttack(Coordinate attacker_loc, Coordinate attack_loc);
	bool sendAttack(ActionActor& attacker, BoardActor& receiver);

	void update();
};


#endif
