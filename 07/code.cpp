#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include <cmath>

int median(std::vector<int> v) {
    size_t n = v.size() / 2;
    std::nth_element(v.begin(), v.begin()+n, v.end());
    return v[n];
}

int mean(std::vector<int> v) {
    return std::reduce(v.begin(), v.end()) / v.size();
}

int main () {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */

    std::vector<int> crabs = {};
    long sum = 0, m = 0;

	while ( !input.eof() ) { 
		int x;
		std::string line;

		std::getline(input, line);
		std::replace( line.begin(), line.end(), ',', ' ');
		std::istringstream linestream(line);

		while (linestream >> x) {
			crabs.push_back(x);
		}
	}

	/* --- Part 1 --- */

    m = median(crabs);
    sum = 0;

    for ( auto c : crabs ) {
        sum += abs(c - m);
    }

	std::cout << "Part1: " << sum << std::endl;

	/* --- Part 2 --- */

    m = mean(crabs);
    sum = 0;

    for ( auto c : crabs ) {
        int cost = abs(c - m);
        sum += cost * (cost+1) / 2;
    }

	std::cout << "Part2: " << sum << std::endl;

	return 0;
}