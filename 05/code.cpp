#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>

int getmax(int a, int b, int c) {
	if(a >= b && a >= c) return a;
    if(b >= a && b >= c) return b;
    return c;
}

void print(std::vector<std::vector<int>> diagram){
	for ( auto line : diagram) {
		for (auto var : line)
			if ( var > 0 ) {
				std::cout << var;
			} else {
				std::cout << '.';
			}
		std::cout << std::endl;
	}
}

int main () {
	std::vector<std::array<int, 4>> data;
	std::array<int, 2> size = {0,0};

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */

	while ( !input.eof() ) { 
		int a,b,x,y;
		std::string line, arrow;

		// line : 0,9 -> 5,9
		std::getline(input, line, ',');
		std::istringstream linestream(line);

		while (linestream >> x >> y >> arrow >> a >> b  ) {
			// std::cout << x << " " << y << " " << a << " " << b << std::endl;
			data.push_back({x,y,a,b});
			size[0] = getmax(size[0],x,a);
			size[1] = getmax(size[1],y,b);
		}
	}

	/* --- Part 1 --- */

	/* Create diagram */

  	std::vector<std::vector<int>> diagram (size[1]+1, std::vector<int> (size[0]+1, 0)); 

	/* Draw horizontal and vertical lines in diagram */

	for ( auto line : data) {

		if ( line[0] == line[2] ) {

			int y = line[0];
			int x = ( line[1] < line[3] ) ? line[1] : line[3];
			int x_end = ( line[1] < line[3] ) ? line[3] : line[1];

			for ( ; x <= x_end ; x++) {

				diagram[x][y]++;

			}

		} else if ( line[1] == line[3] ) {

			int x = line[1];
			int y = ( line[0] < line[2] ) ? line[0] : line[2];
			int y_end = ( line[0] < line[2] ) ? line[2] : line[0];

			for ( ; y <= y_end ; y++) {

				diagram[x][y]++;

			}

		}
	}

	/* Print diagram */

	print(diagram);

	/* Calculate points */

	int part1 = 0;
	for ( auto line : diagram) {
		for (auto var : line)
			if ( var > 1 ) {
				part1++;
			}
	}

	std::cout << "Part1: " << part1 << std::endl;

	
	/* --- Part 2 --- */

	/* Draw diagonal lines in the same diagram (input has 45 degrees only) */

	for ( auto line : data) {

		if ( line[0] != line[2] && line[1] != line[3] ) {

			int x = line[1];
			int y = line[0];

			int x_end = line[3];
			int y_end = line[2];

			if ( x < x_end && y < y_end ) {
				for ( ; x <= x_end ; x++) {
					diagram[x][y]++;
					y++;
				}
			} else if ( x < x_end && y > y_end ) {
				for ( ; x <= x_end ; x++) {
					diagram[x][y]++;
					y--;
				}
			} else if ( x > x_end && y < y_end ) {
				for ( ; x >= x_end ; x--) {
					diagram[x][y]++;
					y++;
				}
			} else if ( x > x_end && y > y_end ) {
				for ( ; x >= x_end ; x--) {
					diagram[x][y]++;
					y--;
				}
			}


		}
	}

	/* Print diagram */

	print(diagram);

	/* Calculate points */
	
	int part2 = 0;
	for ( auto line : diagram) {
		for (auto var : line)
			if ( var > 1 ) {
				part2++;
			}
	}

	std::cout << "Part2: " << part2 << std::endl;	
	
	return 0;
}