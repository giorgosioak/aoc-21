#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

int main () {

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");


	/* --- Part 1 --- */

	int position = 0, depth = 0;
	std::vector<std::pair<std::string, int>> data;
	std::string direction; int step;

	while ( input >> direction >> step ) {
		data.push_back(std::make_pair(direction,step));
	}

	for (int i = 0; i < data.size(); i++) {

		if ( data[i].first == "forward" ) {
			position += data[i].second;
		} else if (data[i].first == "down") {
			depth += data[i].second;
		} else if (data[i].first == "up") {
			depth -= data[i].second;
		}

	}

	std::cout << "Part1: " << position * depth << std::endl;

	/* --- Part 2 --- */

	int aim = 0;
	position = 0, depth = 0;

	for (int i = 0; i < data.size(); i++) {

		if ( data[i].first == "forward" ) {
			position += data[i].second;
			depth += aim * data[i].second;
		} else if (data[i].first == "down") {
			aim += data[i].second;
		} else if (data[i].first == "up") {
			aim -= data[i].second;
		}

	}

	std::cout << "Part2: " << position * depth << std::endl;

	return 0;
}