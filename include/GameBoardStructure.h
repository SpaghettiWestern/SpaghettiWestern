#ifndef GAMEBOARDSTRUCTURE_H
#define GAMEBOARDSTRUCTURE_H

#include <memory>
#include <map>
#include <vector>

#include "Util.h"
#include "BoardActor.h"
#include "BoardStatic.h"
#include "Player.h"

class GameBoardStructure{
private:
	std::map<Coordinate, std::unique_ptr<BoardStatic>> environment;
	std::map<Coordinate, std::shared_ptr<BoardActor>> actors;

	int length;
	int width;

	void initEnvironment();
	void initActors();

public:
	GameBoardStructure(int length, int width);

	BoardStatic& getEnvironmentPiece(int x, int y);
	BoardStatic& getEnvironmentPiece(const Coordinate& loc);

	bool openSpace(const Coordinate& loc);
	bool inBounds(const Coordinate& loc);

	bool actorExists(int x, int y);
	bool actorExists(const Coordinate& loc);
	bool addActor(std::shared_ptr<BoardActor> actor);

	std::map<Coordinate, std::shared_ptr<BoardActor>>& getActors();
	std::shared_ptr<BoardActor> getActor(int x, int y);
	std::shared_ptr<BoardActor> getActor(const Coordinate& loc);
	bool removeActor(const Coordinate& loc);
	bool moveActor(const Coordinate& curr_loc, const Coordinate& new_loc);

	int getLength();
	int getWidth();
};


#endif
