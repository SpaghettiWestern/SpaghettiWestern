#ifndef BOARDPIECE_H
#define BOARDPIECE_H

#include "Util.h"
#include "Animation.h"
#include "Attack.h"

class GameBoard;

class BoardPiece{
private:

protected:
	Coordinate location;
	ScreenCoordinate screen_location;

	std::vector<Animation> animations;
	int active_animation;
	virtual void initAnimations();

	int max_hitpoints;
	int curr_hitpoints;

	void resetScreenLocation();
	void recieveDamage(int damage);

public:
	BoardPiece();
	BoardPiece(Coordinate loc);
	BoardPiece(int hitpoints);
	BoardPiece(Coordinate loc, int hitpoints);

	const Coordinate& getLocation() const;
	void setLocation(Coordinate new_location);


	int getCurrentHealth() const;
	int getMaxHealth() const;
	virtual bool recieveAttack(const Attack& attack);

	void setAnimation(const Animation& new_animation);
	void resetAnimation();
	bool updateAnimation();
	const Frame& getCurrentAnimationFrame() const;

	const ScreenCoordinate& getScreenLocation() const;

	virtual bool update();

};

#endif
