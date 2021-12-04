#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <cmath>
#include "board.hpp"

int main () {

	std::vector<int> numbers;
	std::vector<Board> boards;
	std::string line;

	int x;

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read chosen numbers */

	std::getline(input, line);
	std::replace( line.begin(), line.end(), ',', ' ');
	std::istringstream linestream(line);
	while (linestream >> x) {
		numbers.push_back(x);
	}

	/* Read boards */

	while ( !input.eof() ) {
		Board b;

		for (int i = 0; i < 5; i++) {
			for (int k = 0; k < 5; k++) {
				input >> x;
				b.bingo[i][k] = x;
			}
		}

		boards.push_back(b);
	}


	/* --- Part 1 --- */

	int found = -1;
	for(int n : numbers) {
		for (int b = 0; b < boards.size(); b++) {
			// std::cout << "==== board " << b << " on n " << n  << " ====" << std::endl;
			boards[b].mark(n);
			// boards[b].printmarked();

			if ( boards[b].check() ) {
				// std::cout << "full line on n = " << n << std::endl;
				found = b;
				break;
			}
		}
		if ( found > 0 ) {
			std::cout << "Part1: " << boards[found].unmarkedsum() * n << std::endl;
			// boards[found].print();
			// boards[found].printmarked();
			break;
		}
	}

	/* Reset boards for part 2 */
	for (int b = 0; b < boards.size(); b++) {
		boards[b].reset();
	}

	/* --- Part 2 --- */

	/* Find how many boards won */

	int board_won;
	int won_at;

	for(int n : numbers) {
		for (int b = 0; b < boards.size(); b++) {

			if ( boards[b].win ) continue;

			boards[b].mark(n);
			if ( boards[b].check() ) {

				board_won = b;
				won_at = n;
				boards[b].win = true;
				
			}
		}
	}

	/* Reset boards again */
	for (int b = 0; b < boards.size(); b++) {
		boards[b].reset();
	}

	/* Get <board_won> when <won_at> */

	for(int n : numbers) {
		for (int b = 0; b < boards.size(); b++) {

			boards[b].mark(n);
			if ( boards[b].check() ) {

				if ( board_won == b && won_at == n ) {
					std::cout << "Part2: " << boards[b].unmarkedsum() * n << std::endl;
				}				
			}
		}
	}
	
	return 0;
}