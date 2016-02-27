#include "Util.h"
#include "Effect.h"
#include "MovingEffect.h"
#include "Attack.h"

#include <random>


class AttackEffect : public MovingEffect {
private:
	const Attack& attack;

public:
	AttackEffect(const Attack& attack);
	AttackEffect(Coordinate2D<double> loc, const Attack& attack);
	AttackEffect(Coordinate2D<double> loc, const std::vector<Coordinate2D<double>>& path, const Attack& attack);
	AttackEffect(Coordinate2D<double> loc, const Animation& anim, const Attack& attack);
	AttackEffect(Coordinate2D<double> loc, const Animation& anim, const std::vector<Coordinate2D<double>>& path, const Attack& attack);

	void generatePath(Coordinate2D<double> dest);

	const Attack& getAttack() const;
	virtual effect_type getType() const;

	virtual bool update();

};
