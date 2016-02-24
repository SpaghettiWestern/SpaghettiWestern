#ifndef BOARDACTOR_H
#define BOARDACTOR_H

#include "BoardPiece.h"
#include "Attack.h"
#include "Animation.h"
#include "Util.h"


class Player;
enum actor_type {BOARDACTOR, ACTIONACTOR};

class BoardActor : public BoardPiece{
private:
	Player& owner;

	std::vector<ScreenCoordinate> move_path;
	void generateMovePath(Coordinate start, Coordinate end);
	void generateMovePath(std::vector<Coordinate> path);
	int move_path_index;
	Coordinate destination;

	int move_speed;
	void recieveDamage(int damage);

protected:
	virtual void initAnimations();

public:

	BoardActor(Coordinate loc, Player& owner);
	BoardActor(Coordinate loc, Player& owner, int hitpoints);
	~BoardActor();

	bool isAlive() const;

	void setAnimation_Moving();
	void setAnimation_Idle();
	void resetAnimation();

	bool isMoving() const;
	void startMove(std::vector<Coordinate> path);
	void stopMove();
	void moveStep();
	Coordinate getNextStep() const;
	const Coordinate& getDestination() const;
	int getMoveSpeed() const;

	virtual bool update();

	virtual actor_type getType() const;

	const Player& getOwner() const;
};



#endif
