#include "../Jsonparser.h"
#include <gtest/gtest.h>

#include <fstream>
#include <utility>


TEST(JsonparserTest, Test_parseJson_ifstream_good)
{
	std::string inputFilename = "units/Maple.json";
	std::map<std::string, std::string> expected;
	expected.insert(std::pair<std::string, std::string>("name", "Maple"));
	expected.insert(std::pair<std::string, std::string>("hp", "150"));
	expected.insert(std::pair<std::string, std::string>("dmg", "10"));


    std::ifstream inputFile(inputFilename);

	std::map<std::string, std::string> testingFunction = Jsonparser::parseJson(inputFile);

    inputFile.close();

	ASSERT_EQ(expected, testingFunction);
}

TEST(JsonparserTest, Test_parseJson_fname_good)
{
	std::string inputFilename = "units/Maple.json";
	
	std::map<std::string, std::string> exp_output;
	exp_output.insert(std::pair<std::string, std::string>("name", "Maple"));
	exp_output.insert(std::pair<std::string, std::string>("hp", "150"));
	exp_output.insert(std::pair<std::string, std::string>("dmg", "10"));
	
	std::map<std::string, std::string> test_output = Jsonparser::parseJson(inputFilename);
	
	ASSERT_EQ(exp_output, test_output);
}

TEST(JsonparserTest, Test_parseJson_fname_bad)
{
	std::string inputFilename = "test/bad_unit.json";
	
	ASSERT_THROW(Jsonparser::parseJson(inputFilename), std::runtime_error);
}

TEST(JsonparserTest, Test_getmap_bad)
{
	std::string str = "{\n\t\"INVALID\" \"JSON\",\n\t,\n\t\"FORMAT\"   ,\n \"FAIL\": -1}";

	ASSERT_THROW(Jsonparser::getmap(str), std::runtime_error);
}

TEST(JsonparserTest, whitespace)
{
	
	std::string str1 = "\n\t\\\:,\n "" ";

	
	

	ASSERT_THROW(Jsonparser::getmap(str1), std::runtime_error);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
