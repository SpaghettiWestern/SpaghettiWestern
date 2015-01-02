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

	int getCurrentHealth() const;
	int getMaxHealth() const;

	void recieveAttack(const Attack& attack);
	bool isAlive() const;

	void setAnimation_Moving();
	void setAnimation_Idle();
	const Frame& getCurrentAnimationFrame() const;
	void updateAnimation();
	void resetAnimation();

	bool isMoving() const;
	void startMove(std::vector<Coordinate> path);
	void stopMove();
	void moveStep();
	Coordinate getNextStep() const;
	const Coordinate& getDestination() const;
	int getMoveSpeed() const;

	void update();

	virtual actor_type getType() const;

	const Player& getOwner() const;
};



#endif
