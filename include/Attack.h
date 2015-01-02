#ifndef ATTACK_H
#define ATTACK_H

class Attack{
private:
	int damage;

public:
	Attack(int damage);
	int getDamage() const;
	void setDamage(int new_damage);

};



#endif
