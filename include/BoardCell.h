#ifndef BOARDSPACE_H
#define BOARDSPACE_H
#include "Coordinate.h"
#include "BoardCell.h"
#include "BoardPiece.h"
#include "BoardActor.h"
#include "BoardStatic.h"
#include "BoardFloor.h"
#include "BoardWall.h"
#include "BoardDecoration.h"
#include "Effect.h"

class BoardCell {
public:
	BoardCell(Coordinate3D<int> location);

	bool isTraversable() const;
	bool actorExists() const;

	bool addEffect(std::unique_ptr<Effect>& effect);
	bool setActor(std::shared_ptr<BoardActor>& actor);
	bool setFloor(std::unique_ptr<BoardFloor>& floor);
	bool setWall(std::unique_ptr<BoardWall>& wall, WallEdge edge);
	bool addObject(std::unique_ptr<BoardStatic>& objects);
	bool addDecoration(std::unique_ptr<BoardDecoration>& decoration);

	bool removeActor();
	std::shared_ptr<BoardActor>& getActor();

	std::vector<std::unique_ptr<BoardStatic>>& getObjects();
	std::vector<std::shared_ptr<BoardCell>>& getNeighbors();

	std::unique_ptr<BoardFloor>& getFloor();
	std::shared_ptr<BoardActor>& getActor();
	std::unique_ptr<BoardWall>& getWall(WallEdge edge);

	std::vector<std::unique_ptr<Effect>>& getEffects();
	std::vector<std::unique_ptr<BoardStatic>>& getObjects();
	std::vector<std::unique_ptr<BoardDecoration>>& getDecorations();

	Coordinate3D<int> getLocation();

	bool update();

private:
	Coordinate3D<int> location;

	std::vector<std::shared_ptr<BoardCell>> neighbors;

	std::unique_ptr<BoardFloor> floor;
	std::shared_ptr<BoardActor> actor;
	std::unique_ptr<BoardWall> walls[4];

	std::vector<std::unique_ptr<Effect>> effects;
	std::vector<std::unique_ptr<BoardStatic>> objects;
	std::vector<std::unique_ptr<BoardDecoration>> decorations;
	int roomTag;


};

#endif
