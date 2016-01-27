#include "AttackEffect.h"

AttackEffect::AttackEffect(const Attack& attack) : MovingEffect(), attack(attack){
}

AttackEffect::AttackEffect(ScreenCoordinate loc, const Attack& attack) : MovingEffect(loc), attack(attack){
}

AttackEffect::AttackEffect(ScreenCoordinate loc, const std::vector<ScreenCoordinate>& path, const Attack& attack) : MovingEffect(loc, path), attack(attack){
}

AttackEffect::AttackEffect(ScreenCoordinate loc, const Animation& anim, const Attack& attack) : MovingEffect(loc, anim), attack(attack){
}

AttackEffect::AttackEffect(ScreenCoordinate loc, const Animation& anim, const std::vector<ScreenCoordinate>& path, const Attack& attack) : MovingEffect(loc, anim, path), attack(attack){
}

void AttackEffect::generatePath(ScreenCoordinate dest){
	double x_dist = dest.first - loc.first;
	double y_dist = dest.second - loc.second;
	double dist = sqrt(x_dist*x_dist + y_dist*y_dist);
	double dist_modifier = dist/sqrt(2.0);

	std::normal_distribution<double> num_gen(0.0, attack.getSpread() * dist_modifier);

	dest.first+=num_gen(Util::getRandomEngine());
	dest.second+=num_gen(Util::getRandomEngine());

	MovingEffect::generatePath(dest, attack.getSpeed());
}

const Attack& AttackEffect::getAttack() const{
	return attack;
}

effect_type AttackEffect::getType() const{
	return ATTACKEFFECT;
}

bool AttackEffect::update(){
	return MovingEffect::update();
}




