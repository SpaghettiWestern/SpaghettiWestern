#ifndef EFFECT_H
#define EFFECT_H

#include "Animation.h"
#include "Util.h"

enum effect_type {EFFECT, MOVINGEFFECT, ATTACKEFFECT};

class Effect {
private:
	void initAnimation();

protected:
	ScreenCoordinate loc;
	Animation animation;

public:
	Effect();
	Effect(ScreenCoordinate loc);
	Effect(ScreenCoordinate loc, Animation animation);

	ScreenCoordinate getScreenLocation() const;
	void setScreenLocation(const ScreenCoordinate& new_loc);

	void setAnimation(const Animation& new_animation);
	const Frame& getCurrentAnimationFrame() const;

	virtual effect_type getType() const;

	virtual bool update();
};













#endif
