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

	const GameBoard& getGameBoard() const;
	const std::vector<Player>& getPlayers() const;

	bool playerExists(int index) const;
	const Player& getPlayer(int index) const;

	bool createActor(Coordinate loc, int owner_index, int hitpoints);
	bool createActor(Coordinate loc, int owner_index, int hitpoints, Attack attack);

	bool createWall(Coordinate loc, int hitpoints);

	bool sendAttack(Coordinate attacker_loc, Coordinate attack_loc);
	bool sendAttack(ActionActor& attacker, BoardActor& receiver);

	bool playStaticEffect(const ScreenCoordinate& loc, bool surface_level);
	bool playMovingEffect(const ScreenCoordinate& start, const ScreenCoordinate& dest, bool surface_level);

	void update();

};


#endif
