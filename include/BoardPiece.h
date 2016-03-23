#ifndef BOARDPIECE_H
#define BOARDPIECE_H

#include "Util.h"
#include "Animation.h"
#include "Attack.h"

#include "GL/gl.h"

#include <string>

class GameBoard;

class BoardPiece{
private:
	void deepCopy(const BoardPiece& other);

protected:
	Coordinate3D<int> location;
	Coordinate2D<double> screen_location;

	std::vector<Animation> animations;
	int active_animation;
	virtual void initAnimations();

	int max_hitpoints;
	int curr_hitpoints;

	void resetScreenLocation();
	void recieveDamage(int damage);

	GLuint spriteSheet;

public:
	BoardPiece();
	BoardPiece(const Coordinate3D<int>& loc);
	BoardPiece(int hitpoints);
	BoardPiece(const Coordinate3D<int>& loc, int hitpoints);

	BoardPiece& operator=(const BoardPiece& other);

	bool setSpriteSheet(std::string spriteSheetFilepath);
	const GLuint& getSpriteSheet() const;

	const Coordinate3D<int>& getLocation() const;
	void setLocation(Coordinate3D<int> new_location);

	const GLuint& getSpriteSheet();

	int getCurrentHealth() const;
	int getMaxHealth() const;
	virtual bool recieveAttack(const Attack& attack);

	void setAnimation(const Animation& new_animation);
	void resetAnimation();
	bool updateAnimation();
	const Frame& getCurrentAnimationFrame() const;

	const Coordinate2D<double>& getScreenLocation() const;

	virtual bool update();
};

#endif
