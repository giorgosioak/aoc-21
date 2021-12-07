#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>

int main () {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */

    long lanternfish[9] = { 0 };
    long sum = 0;

	while ( !input.eof() ) { 
		int x;
		std::string line;

		std::getline(input, line, ',');
		std::istringstream linestream(line);

		while (linestream >> x) {
			lanternfish[x]++;
		}
	}

	/* --- Part 1 --- */

    for (int day = 1; day <= 80; day++) {
        long rotate = lanternfish[0];
        lanternfish[0] = lanternfish[1];
        lanternfish[1] = lanternfish[2];
        lanternfish[2] = lanternfish[3];
        lanternfish[3] = lanternfish[4];
        lanternfish[4] = lanternfish[5];
        lanternfish[5] = lanternfish[6];
        lanternfish[6] = lanternfish[7] + rotate;
        lanternfish[7] = lanternfish[8];
        lanternfish[8] = rotate;
    }

    sum = 0; sum = std::accumulate(lanternfish , lanternfish+9 , sum);

	std::cout << "Part1: " << sum << std::endl;

	/* --- Part 2 --- */

    for (int day = 81; day <= 256; day++) {
        long rotate = lanternfish[0];
        lanternfish[0] = lanternfish[1];
        lanternfish[1] = lanternfish[2];
        lanternfish[2] = lanternfish[3];
        lanternfish[3] = lanternfish[4];
        lanternfish[4] = lanternfish[5];
        lanternfish[5] = lanternfish[6];
        lanternfish[6] = lanternfish[7] + rotate;
        lanternfish[7] = lanternfish[8];
        lanternfish[8] = rotate;
    }

    sum = 0; sum = std::accumulate(lanternfish , lanternfish+9 , sum);

	std::cout << "Part2: " << sum << std::endl;

	return 0;
}
