#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <filesystem>
#include <string>

std::set<std::pair<int,int>> fold(std::set<std::pair<int,int>> data,char axis, int coord) {
	std::set<std::pair<int,int>> dots;
	if ( axis == 'x' ) {
		for (auto dot : data) {
			if (dot.first > coord) {
				dots.insert({coord - abs(dot.first-coord),dot.second});
			} else {
				dots.insert(dot);
			}
		}
	} else {
			for (auto dot : data) {
			if (dot.second > coord) {
				dots.insert({dot.first,coord - abs(dot.second-coord)});
			} else {
				dots.insert(dot);
			}
		}	
	}
	return dots;
}

int main () {

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");


	/* --- Part 1 --- */
	
	std::set<std::pair<int,int>> data;
	std::vector<std::pair<char,size_t>> folds;

	std::string line;
	
	while ( std::getline(input, line) && !line.empty()) {
	    std::replace( line.begin(), line.end(), ',', ' ');
        std::istringstream linestream(line);
		int x,y;
        linestream >> x >> y;
		data.insert({x,y});
	}

	while ( !input.eof() ) {
		std::string line;
		char fold_to;
		size_t number;
		std::getline(input, line); 
		line.replace(line.find("fold along "),11,"");
		line.replace(line.find("="),1," ");
        std::istringstream linestream(line);
		linestream >> fold_to >> number;
		folds.push_back({fold_to,number});
	}

	/* --- Part 1 --- */

	std::set<std::pair<int,int>> part1 = fold(data,folds[0].first,folds[0].second);

	std::cout << "Part1: " << part1.size() << std::endl;

	/* --- Part 2 --- */

	for( auto f : folds ) {
		data = fold(data,f.first,f.second);
	}

	int x_size = 0, y_size = 0;
	for (auto pair : data) {
		if ( pair.first > x_size ) { x_size = pair.first; }
		if ( pair.second > y_size ) { y_size = pair.second; }
	}
	x_size++;
	y_size++;

	std::vector<std::vector<char>> paper(y_size,std::vector<char> (x_size, '.'));
	for (auto pair : data) {
		paper[pair.second][pair.first] = '#';
	}

	std::cout << "Part2:" << std::endl;
	for ( auto line : paper ) {
		for ( auto point : line ) {
			if ( point == '#' ) {
				std::cout << "\033[0;31m#\033[0m";
			} else {
				std::cout << "\033[0;30m.\033[0m";
			}
		}
		std::cout << std::endl;
	}

	
	return 0;
}
