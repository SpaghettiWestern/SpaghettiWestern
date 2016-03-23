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
	void deepCopy(const BoardActor& other);

	Player& owner;

	std::vector<Coordinate2D<double>> move_path;
	void generateMovePath(Coordinate3D<int> start, Coordinate3D<int> end);
	void generateMovePath(std::vector<Coordinate3D<int>> path);
	int move_path_index;
	Coordinate3D<int> destination;

	int move_speed;
	void recieveDamage(int damage);

protected:
	virtual void initAnimations();

public:

	BoardActor(Coordinate3D<int> loc, Player& owner);
	BoardActor(Coordinate3D<int> loc, Player& owner, int hitpoints);
	~BoardActor();

	BoardActor& operator=(const BoardActor& other);

	bool isAlive() const;

	void setAnimation_Moving();
	void setAnimation_Idle();
	void resetAnimation();

	bool isMoving() const;
	void startMove(std::vector<Coordinate3D<int>>& path);
	void stopMove();
	void moveStep();
	Coordinate3D<int> getNextStep() const;
	const Coordinate3D<int>& getDestination() const;
	int getMoveSpeed() const;

	virtual bool update();

	virtual actor_type getType() const;

	const Player& getOwner() const;
};



#endif
