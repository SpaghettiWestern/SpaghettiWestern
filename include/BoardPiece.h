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

protected:
	BoardCoordinate location;
	ScreenCoordinate screen_location;

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
	BoardPiece(const BoardCoordinate& loc);
	BoardPiece(int hitpoints);
	BoardPiece(const BoardCoordinate& loc, int hitpoints);

	bool setSpriteSheet(std::string spriteSheetFilepath);
	const GLuint& getSpriteSheet() const;

	const BoardCoordinate& getLocation() const;
	void setLocation(BoardCoordinate new_location);


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
