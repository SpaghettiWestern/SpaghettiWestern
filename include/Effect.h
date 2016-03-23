#ifndef EFFECT_H
#define EFFECT_H

#include "Animation.h"
#include "Util.h"

enum effect_type {EFFECT, MOVINGEFFECT, ATTACKEFFECT};

class Effect {
private:
	void initAnimation();
	void deepCopy(const Effect& other);

protected:
	Coordinate2D<double> loc;
	Animation animation;

public:
	Effect();
	Effect(Coordinate2D<double> loc);
	Effect(Coordinate2D<double> loc, Animation animation);
	Effect(const Effect& other);

	Effect& operator=(const Effect& other);

	Coordinate2D<double> getScreenLocation() const;
	void setScreenLocation(const Coordinate2D<double>& new_loc);

	void setAnimation(const Animation& new_animation);
	const Frame& getCurrentAnimationFrame() const;

	virtual effect_type getType() const;

	virtual bool update();
};













#endif
