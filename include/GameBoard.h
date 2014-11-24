#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>

#include "Util.h"
#include "PathGenerator.h"
#include "GameBoardStructure.h"

class GameBoard {
private:
	std::shared_ptr<GameBoardStructure> board;
	PathGenerator pathgen;


public:
	GameBoard();
	GameBoard(int length, int width);

	GameBoardStructure& getBoard();

	bool openSpace(const Coordinate& loc);

	bool canAttack(const Coordinate& attacker_loc, const Coordinate& attack_loc);

	bool actorExists(const Coordinate& loc);
	BoardActor& getActor(const Coordinate& loc);
	bool addActor(std::shared_ptr<BoardActor> new_actor);

	bool moveActor(Coordinate start, Coordinate end);
	bool moveActor(BoardActor& actor, Coordinate goal);

	void update();
};

#endif




