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
	AttackEffect(ScreenCoordinate loc, const Attack& attack);
	AttackEffect(ScreenCoordinate loc, const std::vector<ScreenCoordinate>& path, const Attack& attack);
	AttackEffect(ScreenCoordinate loc, const Animation& anim, const Attack& attack);
	AttackEffect(ScreenCoordinate loc, const Animation& anim, const std::vector<ScreenCoordinate>& path, const Attack& attack);

	void generatePath(ScreenCoordinate dest);

	const Attack& getAttack() const;
	virtual effect_type getType() const;

	virtual bool update();

};
