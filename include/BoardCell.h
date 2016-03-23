#ifndef BOARDSPACE_H
#define BOARDSPACE_H
#include "Coordinate.h"
#include "BoardPiece.h"
#include "BoardActor.h"
#include "BoardStatic.h"
#include "BoardFloor.h"
#include "BoardWall.h"
#include "BoardDecoration.h"
#include "Effect.h"

#include <memory>

class BoardCell {
public:
	BoardCell(Coordinate3D<int> location);
	BoardCell(const BoardCell& other);
	BoardCell& operator=(const BoardCell& other);

	bool isTraversable() const;
	bool actorExists() const;

	bool addEffect(std::unique_ptr<Effect>& effect);
	bool setActor(std::shared_ptr<BoardActor>& actor);
	bool setFloor(std::unique_ptr<BoardFloor>& floor);
	bool setWall(std::unique_ptr<BoardWall>& wall, BoardWall::WallEdge edge);
	bool addObject(std::unique_ptr<BoardStatic>& objects);
	bool addDecoration(std::unique_ptr<BoardDecoration>& decoration);
	bool addNeighbor(const std::shared_ptr<BoardCell>& neighbor);

	bool removeActor();

	unsigned int getNumNeighbors() const;
	unsigned int getNumEffects() const;
	unsigned int getNumObjects() const;
	unsigned int getNumDecorations() const;

	const BoardActor& getActor() const;
	const BoardCell& getNeighbor(int index) const;
	const BoardFloor& getFloor() const;
	const BoardWall& getWall(BoardWall::WallEdge edge) const;
	const Effect& getEffect(int index) const;
	const BoardStatic& getObject(int index) const;
	const BoardDecoration& getDecoration(int index) const;
	int getRoomTag() const;

	std::shared_ptr<BoardActor> getActorPointer();

	bool receiveAttack(const Attack& attack);

	Coordinate3D<int> getLocation() const;

	bool update();

private:
	void deepCopy(const BoardCell& other);

	Coordinate3D<int> location;

	std::vector<std::shared_ptr<BoardCell>> neighbors;

	std::unique_ptr<BoardFloor> boardfloor;
	std::shared_ptr<BoardActor> actor;
	std::unique_ptr<BoardWall> walls[4];

	std::vector<std::unique_ptr<Effect>> effects;
	std::vector<std::unique_ptr<BoardStatic>> objects;
	std::vector<std::unique_ptr<BoardDecoration>> decorations;
	int roomTag;


};

#endif
