#pragma once

#include <string>


class Monster {
protected:

	std::string name = "";      
	double healthPoints;    
	double damage;           
	double attackCooldown;   
	double cooldownState;   

	void sufferDamage(Monster& monster, const double& damage);


	void elapseTime(Monster& monster, const double& t);


	void resetCooldown();

public:

	Monster() {}


	Monster(const std::string& name, const double& healthPoints, const double& damage, const double& attackCooldown) :
		name(name), healthPoints(healthPoints), damage(damage), attackCooldown(attackCooldown), cooldownState(attackCooldown) {}


	bool isAlive() const { return healthPoints > 0; }


	bool canHit() const { return cooldownState <= 0; }


	static Monster parse(const std::string& filename);


	virtual void attack(Monster& enemy);


	std::string getName() const { return name; }


	double getHealthPoints() const { return healthPoints; }


	double getDamage() const { return damage; }

	
	double getAttackCoolDown() const { return attackCooldown; }
};

