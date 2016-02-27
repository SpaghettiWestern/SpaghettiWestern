#include "AttackEffect.h"

AttackEffect::AttackEffect(const Attack& attack) : MovingEffect(), attack(attack){
}

AttackEffect::AttackEffect(Coordinate2D<double> loc, const Attack& attack) : MovingEffect(loc), attack(attack){
}

AttackEffect::AttackEffect(Coordinate2D<double> loc, const std::vector<Coordinate2D<double>>& path, const Attack& attack) : MovingEffect(loc, path), attack(attack){
}

AttackEffect::AttackEffect(Coordinate2D<double> loc, const Animation& anim, const Attack& attack) : MovingEffect(loc, anim), attack(attack){
}

AttackEffect::AttackEffect(Coordinate2D<double> loc, const Animation& anim, const std::vector<Coordinate2D<double>>& path, const Attack& attack) : MovingEffect(loc, anim, path), attack(attack){
}

void AttackEffect::generatePath(Coordinate2D<double> dest){
	double x_dist = dest.x - loc.x;
	double y_dist = dest.y - loc.y;
	double dist = sqrt(x_dist*x_dist + y_dist*y_dist);
	double dist_modifier = dist/sqrt(2.0);

	std::normal_distribution<double> num_gen(0.0, attack.getSpread() * dist_modifier);

	dest.x+=num_gen(Util::getRandomEngine());
	dest.y+=num_gen(Util::getRandomEngine());

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




