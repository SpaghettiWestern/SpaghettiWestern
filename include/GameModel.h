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
	GameModel(int board_length, int board_width, int board_height);
	GameModel(int board_length, int board_width, int board_height, std::vector<std::pair<std::string, bool>> init_players);

	GameBoard& getGameBoard();
	const std::vector<Player>& getPlayers() const;

	bool playerExists(int index) const;
	const Player& getPlayer(int index) const;


	bool createActor(Coordinate3D<int> loc, int owner_index, int hitpoints);
	bool createActor(Coordinate3D<int> loc, int owner_index, int hitpoints, Attack attack);

	bool createWall(Coordinate3D<int> loc, int hitpoints);

	bool sendAttack(Coordinate3D<int> attacker_loc, Coordinate3D<int> attack_loc);
	bool sendAttack(ActionActor& attacker, BoardActor& receiver);

	bool playStaticEffect(const Coordinate2D<double>& loc, bool surface_level);
	bool playMovingEffect(const Coordinate2D<double>& start, const Coordinate2D<double>& dest, bool surface_level);

	void update();
};


#endif
