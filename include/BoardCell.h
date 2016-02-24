#ifndef BOARDSPACE_H
#define BOARDSPACE_H

#include <BoardCell.h>
#include "BoardPiece.h"
#include "BoardActor.h"
#include "BoardStatic.h"
#include "BoardFloor.h"
#include "BoardWall.h"
#include "BoardDecoration.h"
#include "Effect.h"

class BoardCell {
public:

	bool isTraversable() const;
	bool actorExists() const;

	bool addEffect(std::unique_ptr<Effect>& effect);
	bool addActor(std::shared_ptr<BoardActor>& actor);
	bool addFloor(std::unique_ptr<BoardFloor>& floor);
	bool addWall(std::unique_ptr<BoardWall>& wall);
	bool addObject(std::unique_ptr<BoardStatic>& objects);
	bool addDecoration(std::unique_ptr<BoardDecoration>& decoration);

	bool removeActor(int index);

	const std::vector<std::shared_ptr<BoardActor>>& getActors() const;
	std::shared_ptr<BoardActor> getActor(int index);


private:
	std::vector<std::shared_ptr<BoardCell>> neighbors;

	std::vector<std::unique_ptr<Effect>> effects;
	std::vector<std::shared_ptr<BoardActor>> actors;
	std::vector<std::unique_ptr<BoardFloor>> floors;
	std::vector<std::unique_ptr<BoardWall>> walls;
	std::vector<std::unique_ptr<BoardStatic>> objects;
	std::vector<std::unique_ptr<BoardDecoration>> decorations;
	int roomTag;


};

#endif
