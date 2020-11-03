#pragma once
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>

#include<map>
#include<algorithm>
#include<string>


class Fighter {

	int HP;
	const int DMG;
	const std::string name;

public:

	Fighter(std::string iname, int ihp, int idmg) : name(iname), HP(ihp), DMG(idmg) {}
	~Fighter() {}
	void take_dmg(Fighter &enemy);
	void deal_dmg(Fighter &enemy);

	int getHP() const { return HP; }
	int getDMG() const { return DMG; }
	std::string getName() const { return name; }


	friend std::ostream& operator<<(std::ostream& os, const Fighter& fi);
	friend bool operator==(const Fighter &f1, const Fighter &f2)
	{
		return (f1.HP == f2.HP && f1.DMG == f2.DMG && f1.name == f2.name);
	}

	
};
