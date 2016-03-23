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

	void deepCopy(const Player& other);

public:
	Player(std::string name, bool is_human);
	Player(const Player& other);
	Player& operator=(const Player& other);


	std::string getName() const;
	bool isHuman() const;
	void createActor(Coordinate3D<int> loc);
	void createActor(Coordinate3D<int> loc, int hitpoints);
	void addActor(std::shared_ptr<BoardActor> actor);

	int getNumActors() const;

	bool actorExists(int index) const;
	const BoardActor& getActor(int index) const;
	bool deleteActor(int index);

	void update();

};
#endif
