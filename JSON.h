#pragma once

#include <string>
#include <map>
#include <fstream>


class JSON {

	std::map<std::string, std::string> stringMap;  

	std::map<std::string, double> doubleMap;         
	std::map<std::string, int> intMap;             


	void parseRaw(std::string data);

	enum type { Integer, Double, String };
	static type determine_type(const std::string &str);


public:

	class ParseException : public std::exception {
		std::string s;
	public:
		ParseException(const std::string& ss) : s(ss) {}
		~ParseException() throw() {}
		const char* what() const throw() { return s.c_str(); }
	};


	void getmap(const std::string& key, const std::string& value);


	unsigned count(const std::string& key) const;


	static JSON parseFromFile(const std::string& filename);


	static JSON parseFromStream(std::ifstream& file);


	static JSON parseFromString(const std::string& text);


	template<typename T>
	T get(const std::string& tag) const;
};

