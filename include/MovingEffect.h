#ifndef MOVINGEFFECT_H
#define MOVINGEFFECT_H

#include "Effect.h"
#include "PathInterpolater.h"

class MovingEffect : public Effect{
private:
	std::vector<Coordinate2D<double>> move_path;
	bool moving;
	PathInterpolater pathgen;

	void deepCopy(const MovingEffect& other);

public:
	MovingEffect();
	MovingEffect(Coordinate2D<double> loc);
	MovingEffect(Coordinate2D<double> loc, const std::vector<Coordinate2D<double>>& path);
	MovingEffect(Coordinate2D<double> loc, const Animation& anim);
	MovingEffect(Coordinate2D<double> loc, const Animation& anim, const std::vector<Coordinate2D<double>>& path);
	MovingEffect(const MovingEffect& other);

	MovingEffect& operator=(const MovingEffect& other);

	void setPath(const std::vector<Coordinate2D<double>>& new_path);
	void transferPath(std::vector<Coordinate2D<double>>& new_path);
	void generatePath(const Coordinate2D<double>& dest, double speed);

	bool startMove();
	void stopMove();
	bool isMoving() const;
	bool moveStep();
	Coordinate2D<double> getNextStep() const;
	virtual effect_type getType() const;

	virtual bool update();
};


#endif
