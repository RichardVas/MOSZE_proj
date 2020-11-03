#include "Jsonparser.h"
#include<sstream>
#include<string>

Jsonparser::type Jsonparser::determine_type(std::string str)
{
	if (str.find('"') != std::string::npos)
		return String;
	else
	{
		if (str.find('.') != std::string::npos)
			return Double;
		else
			return Integer;
	}
}

std::map <std::string, std::string> Jsonparser::getmap(std::string str)
{

		std::map<std::string, std::string>m;
		std::string line;

		std::istringstream stream(str);

		while (std::getline(stream, line))
		{
			std::string rightside = "";
			std::string value = "";
			std::string leftside = "";
			std::string key = "";

			bool whiteSpacesOnly = std::all_of(line.begin(), line.end(), isspace);

			if (line.find('{') == std::string::npos && line.find('}') == std::string::npos && !whiteSpacesOnly)
			{
				/*check for :*/

				if (line.find(':') == std::string::npos)
					throw std::runtime_error("Invalid Json format");
				else
				{
					leftside = line.substr(0, line.find(':') - 1);
					/*determine key*/
					unsigned int str_start = leftside.find('"');

					key = leftside.substr(str_start + 1, (leftside.rfind('"') - str_start) - 1);

					Jsonparser::type target_type = determine_type(line.substr(line.find(':')));

					if (target_type == String)
					{
						rightside = line.substr(line.find(':'));
						unsigned int val_start = rightside.find('"');
						value = rightside.substr(val_start + 1, (rightside.rfind('"') - val_start) - 1);
						m[key] = value;
					}
					else
					{
						rightside = line.substr(line.find(':'));

						value = rightside.substr(rightside.find(':') + 1);
						/*remove trash*/
						value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());
						if (value.back() == ',')
							value.pop_back();
						
						if (target_type == Integer) {
							m[key] = value;
						}
						else {
							if (target_type == Double)
							{
								m[key] = value;
							}
						}
					}
				}
			}
		}
			return m;
}

std::map <std::string, std::string> Jsonparser::parseJson(std::string fname)
{
	std::ifstream file;
	file.open(fname);
	if (!file.good()) throw std::runtime_error("File cannot be opened!");

	else {
		std::map<std::string, std::string>map; 
		std::string line, str="";
		while (std::getline(file, line)) {
			str += line;
			str += "\n";
		}

		map = getmap(str);

		file.close();
		return map;

	}

}
std::map<std::string, std::string> Jsonparser::parseJson(std::istream &input) {
	std::string str="", line;
	while (std::getline(input, line))
	{
		str += line;
		str += "\n";
	}
	return Jsonparser::getmap(str);
}
