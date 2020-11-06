#pragma once
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>

#include<map>
#include<algorithm>
#include<string>

#include<cmath>

class Fighter {
/**
*Class that handles everything that happens regarding characters.
*/
		double HP
			/**
			 * Characters health points.
			 */;
		double DMG
			/**
			 * Characters damage.
			 */;
		double attackcooldown
			/**
			 * Characters attack speed.
			 */;
		const std::string name
			/**
			 * Characters name.
			 */;
		void take_dmg(Fighter &enemy)
			/**
			 * Method for character taking damage.
			 */;
		void deal_dmg(Fighter &enemy)
			/**
			 * Method for character dealing damage.
			 */;


		double MaxHP;

		int level = 1;
		int exp = 0;


		void levelUP() /**
		*Method for character leveling up.
		*/;



	public:

		Fighter(const std::string &iname, double ihp, int idmg, double acd) : name(iname), HP(ihp), DMG(idmg), MaxHP(ihp), attackcooldown(acd) {}
		~Fighter() {}


		double getHP() const { return HP; }
		double getDMG() const { return DMG; }
		double getCD() const { return attackcooldown; }
		int getLVL() const { return level; }
		int getXP() const { return exp; }

		std::string getName() const { return name; }

		Fighter& duel(Fighter *enemy)/**
			 * Method for 2 characters fighting.
			 */;



		friend std::ostream& operator<<(std::ostream& os, const Fighter& fi)
			/**
			 * Operator overload to make the class printable.
			 */;


};
