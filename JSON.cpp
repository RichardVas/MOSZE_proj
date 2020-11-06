#include "JSON.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <sstream>

JSON::type JSON::determine_type(const std::string &str)
{
	if ((str.back() == '\"') && (str.front() == '\"'))
		return String;
	else
	{
		if (str.find('.') != std::string::npos)
			return Double;
		else
			return Integer;
	}
}



void JSON::getmap(const std::string& key, const std::string& value) {
	if (stringMap.count(key) || doubleMap.count(key) || intMap.count(key)) {
		throw ParseException("Key \"" + key + "\" already exists!");
	}
	if (determine_type(value) == JSON::String) {
		stringMap[key] = (std::string)value.substr(1, value.size() - 2);
	}
	else if (determine_type(value)== JSON::Double) {
		doubleMap[key] = (double)std::stof(value);
	}
	else if (determine_type(value)==JSON::Integer) {
		intMap[key] = (int)std::stoi(value);
	}
	else {
		throw ParseException("Unknown value type! \"" + value + "\"");
	}
}

unsigned JSON::count(const std::string& key) const {
	return stringMap.count(key) + doubleMap.count(key) + intMap.count(key);
}

void JSON::parseRaw(std::string data) {

	std::string ws = " \t\n\v\f\r";
	data.erase(0, data.find_first_not_of(ws));
	data.erase(data.find_last_not_of(ws) + 1);

	if (data[0] != '{') { throw ParseException("Missing \"{\" bracket!"); }
	if (data[data.size() - 1] != '}') { throw ParseException("Missing \"}\" bracket!"); }

	data.erase(0, 1);

	if (data.size() == 0) { throw ParseException("Empty JSON file!"); }

	std::string tag = "";
	std::string value = "";

	bool isTag = true;
	bool inQuotes = false;
	for (unsigned i = 0; i < data.size(); ++i) {
		if (data[i] == '"') { inQuotes = !inQuotes; }
		if (inQuotes) {
			if (isTag) { tag += data[i]; }
			else { value += data[i]; }
		}
		else {
			if (data[i] == ':') { isTag = false; }
			else if (data[i] == ',' || data[i] == '}') {
				tag = tag.substr(1, tag.size() - 2);

				if (tag.size() <= 0) { throw ParseException("Invalid tag!"); }

				if (value.size() <= 0) { throw ParseException("Invalid value!"); }

				if (stringMap.count(tag) || doubleMap.count(tag) || intMap.count(tag)) {
					throw ParseException("Multiple definition of \"" + tag + "\"!");
				}

				getmap(tag, value);

				isTag = true;
				tag = "";
				value = "";
			}
			else if (!isspace(data[i])) {
				if (isTag) { tag += data[i]; }
				else { value += data[i]; }
			}
		}
	}
	if (!isTag || inQuotes) { throw ParseException("Invalid end of file!"); }
}

JSON JSON::parseFromFile(const std::string& filename) {
	JSON ret;
	std::ifstream file(filename);

	if (file.is_open()) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		ret.parseRaw(buffer.str());

		file.close();
	}
	else {
		throw ParseException("Failed to open file!");
	}
	return ret;
}

JSON JSON::parseFromStream(std::ifstream& file) {
	JSON ret;

	if (file.is_open()) {
		std::stringstream buffer;
		buffer << file.rdbuf();
		ret.parseRaw(buffer.str());

		file.close();
	}
	else {
		throw ParseException("Invalid stream!");
	}
	return ret;
}

JSON JSON::parseFromString(const std::string& text) {
	if (text.size() <= 0) { throw ParseException("Input string is empty!"); }
	JSON ret;
	ret.parseRaw(text);
	return ret;
}

template<>
std::string JSON::get<std::string>(const std::string& tag) const {
	try {
		return stringMap.at(tag);
	}
	catch (const std::out_of_range& e) {
		throw ParseException("Tag \"" + tag + "\" not found!");
	}
}

template<>
double JSON::get<double>(const std::string& tag) const {
	try {
		return doubleMap.at(tag);
	}
	catch (const std::out_of_range& e) {
		throw ParseException("Tag \"" + tag + "\" not found!");
	}
}

template<>
int JSON::get<int>(const std::string& tag) const {
	try {
		return intMap.at(tag);
	}
	catch (const std::out_of_range& e) {
		throw ParseException("Tag \"" + tag + "\" not found!");
	}
}
