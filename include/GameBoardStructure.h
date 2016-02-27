#ifndef GAMEBOARDSTRUCTURE_H
#define GAMEBOARDSTRUCTURE_H

#include <memory>
#include <map>
#include <vector>

#include "Coordinate.h"
#include "Util.h"
#include "BoardActor.h"
#include "BoardStatic.h"
#include "Player.h"
#include "Effect.h"
#include "AttackEffect.h"
#include "BoardCell.h"

class GameBoardStructure{
private:
	std::map<Coordinate3D<int>, std::shared_ptr<BoardCell>> environmentCells;
	std::map<Coordinate2D<int>, GLuint> groundTexture;
	std::map<Coordinate3D<int>, std::vector<std::unique_ptr<Effect>>> effects;

	int length;
	int width;
	int height;

	void initEnvironment();
	void initActors();

	bool handleEffect(const std::unique_ptr<Effect>& effect, const Coordinate3D<int>& loc);
	void updateEffects_base();
	void updateEffects_reposition();
	void updateEnvironment();
	void updateEffects();

public:
	GameBoardStructure(int length, int width);
	GameBoardStructure(const GameBoardStructure& other);
	GameBoardStructure& operator=(const GameBoardStructure& other);

	std::map<Coordinate3D<int>, std::shared_ptr<BoardCell>>& getCells();
	std::shared_ptr<BoardCell>& getCell(Coordinate3D<int> loc);
	const BoardCell& getEnvironmentCell(int x, int y, int z) const;
	const BoardCell& getEnvironmentCell(const Coordinate3D<int>& loc) const;

	GLuint getGroundTexture(int x, int y) const;
	GLuint getGroundTexture(const Coordinate2D<int>& loc) const;

	bool addEnvironmentPiece(std::unique_ptr<BoardStatic>& newpiece);
	bool addBoardEffect(std::unique_ptr<Effect>& effect);
	bool addActor(std::shared_ptr<BoardActor>& actor);
	bool addFloor(std::unique_ptr<BoardFloor>& floor);
	bool addWall(std::unique_ptr<BoardWall>& wall);
	bool addObject(std::unique_ptr<BoardStatic>& object);
	bool addDecoration(std::unique_ptr<BoardDecoration>& decoration);

	bool openSpace(const Coordinate3D<int>& loc) const;
	bool inBounds(const Coordinate3D<int>& loc) const;
	bool traversableSpace(const Coordinate3D<int>& loc) const;

	bool actorExists(int x, int y, int z) const;
	bool actorExists(const Coordinate3D<int>& loc) const;

	const std::shared_ptr<BoardActor>& getActor(int x, int y, int z) const;
	const std::shared_ptr<BoardActor>& getActor(const Coordinate3D<int>& loc) const;
	bool removeActor(const Coordinate3D<int>& loc);
	bool moveActor(const Coordinate3D<int>& curr_loc, const Coordinate3D<int>& new_loc);

	const std::map<Coordinate3D<int>, std::vector<std::unique_ptr<Effect>>>& getEffects() const;
	const std::vector<std::unique_ptr<Effect>>& getEffects(const Coordinate3D<int>& loc) const;
	int numEffects(const Coordinate3D<int>& loc) const;
	bool effectsExist(const Coordinate3D<int>& loc) const;
	const Effect& getEffect(const Coordinate3D<int>& loc) const;



	int getLength() const;
	int getWidth() const;
	int getHeight() const;

	void update();
};


#endif
