#ifndef MOVINGEFFECT_H
#define MOVINGEFFECT_H

#include "Effect.h"
#include "PathInterpolater.h"

class MovingEffect : public Effect{
private:
	std::vector<ScreenCoordinate> move_path;
	bool moving;
	PathInterpolater pathgen;

public:
	MovingEffect();
	MovingEffect(ScreenCoordinate loc);
	MovingEffect(ScreenCoordinate loc, const std::vector<ScreenCoordinate>& path);
	MovingEffect(ScreenCoordinate loc, const Animation& anim);
	MovingEffect(ScreenCoordinate loc, const Animation& anim, const std::vector<ScreenCoordinate>& path);

	void setPath(const std::vector<ScreenCoordinate>& new_path);
	void transferPath(std::vector<ScreenCoordinate>& new_path);
	void generatePath(const ScreenCoordinate& dest, double speed);

	bool startMove();
	void stopMove();
	bool isMoving() const;
	bool moveStep();
	ScreenCoordinate getNextStep() const;
	virtual effect_type getType() const;

	virtual void update();
};


#endif
