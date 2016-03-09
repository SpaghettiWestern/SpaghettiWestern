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

	void updateActor(BoardActor& curr_actor, const Coordinate3D<int>& curr_location);

	void updateActors();
	void updateEffects();
	void updateBoard();


public:
	GameBoard();
	GameBoard(int length, int width, int height);
	GameBoard(const GameBoard& other_board);

	GameBoard& operator=(const GameBoard& other);

	const GameBoardStructure& getBoard() const;

	bool openSpace(const Coordinate3D<int>& loc);

	bool canAttack(const Coordinate3D<int>& attacker_loc, const Coordinate3D<int>& attack_loc);

	bool actorExists(const Coordinate3D<int>& loc);
	const BoardActor& getActor(const Coordinate3D<int>& loc) const;
	std::shared_ptr<BoardActor> getActorPointer(const Coordinate3D<int>& loc);
	bool addActor(std::shared_ptr<BoardActor> new_actor);

	bool addStaticCoverPiece(Coordinate3D<int> loc, bool traversable, int hitpoints, int deflection_chance);

	bool removeActor(const Coordinate3D<int>& loc);

	bool moveActor(Coordinate3D<int> start, Coordinate3D<int> end);
	bool moveActor(BoardActor& actor, Coordinate3D<int> goal);

	const std::map<Coordinate3D<int>, std::vector<std::unique_ptr<Effect>>>& getBoardEffects() const;
	bool addBoardEffect(const Coordinate2D<double>& loc);
	bool addBoardEffect(const Coordinate2D<double>& loc, const Animation& animation);
	bool addBoardEffect(std::unique_ptr<Effect>& new_effect);
	bool addMovingBoardEffect(const Coordinate2D<double>& loc, const std::vector<Coordinate2D<double>>& path);

	const std::vector<std::unique_ptr<Effect>>& getSurfaceEffects() const;
	bool addSurfaceEffect(const Coordinate2D<double>& loc);
	bool addSurfaceEffect(const Coordinate2D<double>& loc, const Animation& animation);
	bool addSurfaceEffect(std::unique_ptr<Effect>& new_effect);
	bool addMovingSurfaceEffect(const Coordinate2D<double>& loc, const std::vector<Coordinate2D<double>>& path);

	void update();
};

#endif




