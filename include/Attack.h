#ifndef ATTACK_H
#define ATTACK_H

class Attack{
private:
	int damage;
	double accuracy;
	double spread;
	double speed;

public:
	Attack(int damage = 0, double accuracy = 0.0, double spread = 0.0, double speed = 0.01);
	int getDamage() const;
	double getAccuracy() const;
	double getSpread() const;
	double getSpeed() const;

	void setDamage(int new_damage);
	void setAccuracy(float new_accuracy);
	void setSpread(float new_spread);
	void setSpeed(float new_speed);

};



#endif
