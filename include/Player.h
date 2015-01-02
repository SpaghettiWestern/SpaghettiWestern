#ifndef PLAYER_H
#define PLAYER_H

#include "BoardActor.h"

#include <vector>
#include <memory>
#include <string>

class Player{
private:
	std::vector<std::shared_ptr<BoardActor>> actors;
	std::string name;
	bool human;

public:
	Player(std::string name, bool is_human);

	std::string getName() const;
	bool isHuman() const;
	void createActor(Coordinate loc);
	void createActor(Coordinate loc, int hitpoints);
	void addActor(std::shared_ptr<BoardActor> actor);

	int getNumActors() const;

	bool actorExists(int index) const;
	const BoardActor& getActor(int index) const;
	bool deleteActor(int index);

	void update();

};
#endif
