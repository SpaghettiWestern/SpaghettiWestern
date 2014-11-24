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
	int max_hitpoints;
	int curr_hitpoints;

	std::vector<ScreenCoordinate> move_path;
	void generateMovePath(Coordinate start, Coordinate end);
	void generateMovePath(std::vector<Coordinate> path);
	int move_path_index;
	Coordinate destination;

	int move_speed;

	void recieveDamage(int damage);


protected:
	std::vector<Animation> animations;
	int active_animation;
	void initAnimations();


public:
	BoardActor(Coordinate loc, Player& owner);
	BoardActor(Coordinate loc, Player& owner, int hitpoints);

	int getCurrentHealth();
	int getMaxHealth();

	void recieveAttack(Attack& attack);
	bool isAlive();

	void setAnimation_Moving();
	void setAnimation_Idle();
	Frame& getCurrentAnimationFrame();
	void updateAnimation();
	void resetAnimation();

	bool isMoving();
	void startMove(std::vector<Coordinate> path);
	void stopMove();
	void moveStep();
	Coordinate getNextStep();
	Coordinate getDestination();
	int getMoveSpeed();

	void update();

	virtual actor_type getType();

	Player& getOwner();
};



#endif
