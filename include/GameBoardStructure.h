#ifndef GAMEBOARDSTRUCTURE_H
#define GAMEBOARDSTRUCTURE_H

#include <memory>
#include <map>
#include <vector>

#include "Util.h"
#include "BoardActor.h"
#include "BoardStatic.h"
#include "Player.h"
#include "Effect.h"
#include "AttackEffect.h"
#include "BoardCell.h"

class GameBoardStructure{
private:
	std::map<BoardCoordinate, std::unique_ptr<BoardCell>> environmentCells;
	std::map<Coordinate, GLuint> groundTexture;
	std::map<BoardCoordinate, std::vector<std::unique_ptr<Effect>>> effects;

	int length;
	int width;
	int height;

	void initEnvironment();
	void initActors();

	bool handleEffect(const std::unique_ptr<Effect>& effect, const BoardCoordinate& loc);
	void updateEffects_base();
	void updateEffects_reposition();
	void updateEnvironment();
	void updateEffects();

public:
	GameBoardStructure(int length, int width);
	GameBoardStructure(const GameBoardStructure& other);
	GameBoardStructure& operator=(const GameBoardStructure& other);

	const BoardCell& getEnvironmentCell(int x, int y, int z) const;
	const BoardCell& getEnvironmentCell(const BoardCoordinate& loc) const;

	GLuint getGroundTexture(int x, int y) const;
	GLuint getGroundTexture(const Coordinate& loc) const;

	bool addBoardEffect(std::unique_ptr<Effect>& effect);
	bool addActor(std::shared_ptr<BoardActor>& actor);
	bool addFloor(std::unique_ptr<BoardFloor>& floor);
	bool addWall(std::unique_ptr<BoardWall>& wall);
	bool addObject(std::unique_ptr<BoardStatic>& object);
	bool addDecoration(std::unique_ptr<BoardDecoration>& decoration);

	bool openSpace(const BoardCoordinate& loc) const;
	bool inBounds(const BoardCoordinate& loc) const;
	bool traversableSpace(const BoardCoordinate& loc) const;

	bool actorExists(int x, int y, int z) const;
	bool actorExists(const BoardCoordinate& loc) const;

	const std::vector<std::shared_ptr<BoardActor>>& getActors(const BoardCoordinate& loc) const;
	const std::shared_ptr<BoardActor>& getActor(int x, int y, int z) const;
	const std::shared_ptr<BoardActor>& getActor(const BoardCoordinate& loc) const;
	bool removeActor(const BoardCoordinate& loc);
	bool moveActor(const BoardCoordinate& curr_loc, const BoardCoordinate& new_loc);

	const std::map<BoardCoordinate, std::vector<std::unique_ptr<Effect>>>& getEffects() const;
	const std::vector<std::unique_ptr<Effect>>& getEffects(const BoardCoordinate& loc) const;
	int numEffects(const BoardCoordinate& loc) const;
	bool effectsExist(const BoardCoordinate& loc) const;
	const Effect& getEffect(const BoardCoordinate& loc) const;
	bool addSurfaceEffect(std::unique_ptr<Effect>& new_effect);

	int getLength() const;
	int getWidth() const;
	int getHeight() const;

	void update();
};


#endif
