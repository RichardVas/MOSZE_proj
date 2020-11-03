#pragma once
#include"Fighter.h"

class Jsonparser
{
	/**
	*Class for parsing json input files.
	*/
	enum type { Integer, Double, String };
	static type determine_type(std::string str)/**
	*Method that returns with an enum type of a given string.
	*/;

public:

	static std::map<std::string, std::string> getmap(std::string str)/**
	*Method that creates the map of a given string, that is in a json format.
	*/;
	static std::map<std::string, std::string> parseJson(std::string fname)/**
	*Method that processes a json file that is given by its name.
	*/;
	static std::map<std::string, std::string> parseJson(std::istream &input)/**
	*Method that processes a json file that is given through an istream.
	*/;

	~Jsonparser() {}
	Jsonparser() {}
	


};
