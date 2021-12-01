#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

int main () {

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	int prev, x, sum, count = 0;
	std::vector<int> data;

	while (input >> x) {
		data.push_back(x);
	}
	
	/* --- Part 1 --- */

	prev = data[0];

	for (int i = 1; i < data.size(); i++) {

		x = data[i];

		if (x > prev) {
			count++;
		}

		prev = x;

	}

	std::cout << "Part1: " << count << std::endl;

	/* --- Part 2 --- */
	
	count = 0;
	prev = data[0] + data[1] + data[2];

	for (int i = 1; i < data.size()-2; i++) {

		sum = data[i] + data[i + 1] + data[i + 2];

		if (sum > prev) {
			count++;
		}
		
		prev = sum;
	}

	std::cout << "Part2: " << count << std::endl;

	return 0;
}