#include "Fighter.h"

void Fighter::take_dmg(Fighter& enemy) {
	HP -= enemy.getDMG();
	if (HP < 0)
		HP = 0;
}

void Fighter::deal_dmg(Fighter &enemy) {
	enemy.take_dmg(*this);
}

std::ostream& operator<<(std::ostream& os, const Fighter& fi)
{
	os << fi.getName() << ": HP: " << fi.getHP() << "," << " DMG: " << fi.getDMG() << std::endl;
	return os;
}

bool operator==(const Fighter &f1, const Fighter &f2)
{
	return (f1.HP == f2.HP && f1.DMG == f2.DMG && f1.name == f2.name);
}
