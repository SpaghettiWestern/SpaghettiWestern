#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>
#include <map>

#include "Util.h"
#include "PathGenerator.h"
#include "GameBoardStructure.h"
#include "Effect.h"
#include "MovingEffect.h"
#include "BoardStatic.h"
#include "StaticCover.h"

class GameBoard {
private:
	std::shared_ptr<GameBoardStructure> board;
	PathGenerator pathgen;

	std::vector<std::unique_ptr<Effect>> surface_effects;

	void updateActors();
	void updateEffects();
	void updateBoard();


public:
	GameBoard();
	GameBoard(int length, int width);
	GameBoard(const GameBoard& other_board);

	GameBoard& operator=(const GameBoard& other);

	const GameBoardStructure& getBoard() const;

	bool openSpace(const Coordinate& loc);

	bool canAttack(const Coordinate& attacker_loc, const Coordinate& attack_loc);

	bool actorExists(const Coordinate& loc);
	BoardActor& getActor(const Coordinate& loc);
	bool addActor(std::shared_ptr<BoardActor> new_actor);

	bool addStaticCoverPiece(Coordinate loc, bool traversable, int hitpoints, int deflection_chance);

	bool removeActor(const Coordinate& loc);

	bool moveActor(Coordinate start, Coordinate end);
	bool moveActor(BoardActor& actor, Coordinate goal);

	const std::map<Coordinate, std::vector<std::unique_ptr<Effect>>>& getBoardEffects() const;
	bool addBoardEffect(const ScreenCoordinate& loc);
	bool addBoardEffect(const ScreenCoordinate& loc, const Animation& animation);
	bool addBoardEffect(std::unique_ptr<Effect>& new_effect);
	bool addMovingBoardEffect(const ScreenCoordinate& loc, const std::vector<ScreenCoordinate>& path);

	const std::vector<std::unique_ptr<Effect>>& getSurfaceEffects() const;
	bool addSurfaceEffect(const ScreenCoordinate& loc);
	bool addSurfaceEffect(const ScreenCoordinate& loc, const Animation& animation);
	bool addSurfaceEffect(std::unique_ptr<Effect>& new_effect);
	bool addMovingSurfaceEffect(const ScreenCoordinate& loc, const std::vector<ScreenCoordinate>& path);

	void update();
};

#endif




