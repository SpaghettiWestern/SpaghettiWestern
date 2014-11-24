#include "Attack.h"


Attack::Attack(int damage) : damage(damage){

}

int Attack::getDamage(){
	return damage;
}

void Attack::setDamage(int new_damage){
	damage = new_damage;
}
