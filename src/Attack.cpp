#include "Attack.h"


Attack::Attack(int damage, double accuracy, double spread, double speed) : damage(damage), accuracy(accuracy), spread(spread), speed(speed){

}

int Attack::getDamage() const{
	return damage;
}

double Attack::getAccuracy() const{
	return accuracy;
}

double Attack::getSpread() const{
	return spread;
}

double Attack::getSpeed() const{
	return speed;
}


void Attack::setDamage(int new_damage){
	damage = new_damage;
}

void Attack::setAccuracy(double new_accuracy){
	accuracy = new_accuracy;
}

void Attack::setSpread(double new_spread){
	spread = new_spread;
}

void Attack::setSpeed(double new_speed){
	speed = new_speed;
}



