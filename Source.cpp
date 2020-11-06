#include"Fighter.h"
#include"Jsonparser.h"



int main(int argc, char* argv[])
{

	try {

		
		std::map<std::string, std::string>map1 = Jsonparser::parseJson(argv[1]);
		std::map<std::string, std::string>map2 = Jsonparser::parseJson(argv[2]);


		Fighter u1(map1["name"], std::stoi(map1["hp"]),std::stof( map1["dmg"]),std::stof(map1["attackcooldown"]));
		Fighter u2(map2["name"], std::stoi(map2["hp"]), std::stof(map2["dmg"]), std::stof(map2["attackcooldown"]));
		Fighter *outcome = &u1.duel(&u2);
		std::cout << outcome->getName() << " wins. " << "Remaining HP: " << outcome->getHP() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
		

	return 0;
}
