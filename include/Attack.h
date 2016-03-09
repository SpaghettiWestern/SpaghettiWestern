#ifndef ATTACK_H
#define ATTACK_H

class Attack{
private:
	int damage;
	double accuracy;
	double spread;
	double speed;

	void deepCopy(const Attack& other);

public:
	Attack(int damage = 0, double accuracy = 0.0, double spread = 0.0, double speed = 0.01);
	Attack(const Attack& other);

	Attack& operator=(const Attack& other);

	int getDamage() const;
	double getAccuracy() const;
	double getSpread() const;
	double getSpeed() const;

	void setDamage(int new_damage);
	void setAccuracy(double new_accuracy);
	void setSpread(double new_spread);
	void setSpeed(double new_speed);

};



#endif
