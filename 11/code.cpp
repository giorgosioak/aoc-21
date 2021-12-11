#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include <bits/stdc++.h>
#include <stack>

// #define VISUALIZATION // uncomment to view visuals

int octopuses[10][10];
bool flashed[10][10];
int flashes = 0;

void flash(int x, int y) {

    int x_start = ( x == 0 ) ? 0 : x-1; int x_end = ( x == 9 ) ? 9 : x+1;
    int y_start = ( y == 0 ) ? 0 : y-1; int y_end = ( y == 9 ) ? 9 : y+1;


    for ( int i = x_start; i < x_end+1; i++ ) {
        for ( int k = y_start; k < y_end+1; k++ ) {
            octopuses[i][k]++;
            if ( octopuses[i][k] > 9 && !flashed[i][k] ) { octopuses[i][k] = 0; flashed[i][k] = true; flashes++; flash(i,k); }
        }
    }

}

void reset_flashed() {
    for ( int i = 0; i < 10; i++ ) {
        for ( int k = 0; k < 10; k++ ) {
            flashed[i][k] = false;
        }
    }            
}

bool did_all_flash() {
    for ( int i = 0; i < 10; i++ ) {
        for ( int k = 0; k < 10; k++ ) {
            if ( flashed[i][k] == false ) {
                return false;
            }
        }
    }
    return true;        
}

void print(int step) {
    #ifdef VISUALIZATION

    if ( step == 0 ) {
        std::cout << "Before any steps:" << std::endl;
    } else {
        std::cout << "After step " << step << ":" << std::endl;
    }

    for ( int i = 0; i < 10; i++ ) {
        for ( int k = 0; k < 10; k++ ) {
            if ( flashed[i][k] ) {
                std::cout << "\033[0;36m" << flashed[i][k] << "\033[0m ";
            } else {
                std::cout << "\033[0;37m" << flashed[i][k] << "\033[0m ";
            }
        }
        std::cout << " ";
        for ( int k = 0; k < 10; k++ ) {
            if ( octopuses[i][k] == 9 ) {
                std::cout << "\033[0;31m" << octopuses[i][k] << "\033[0m ";
            } else if ( octopuses[i][k] == 0 ) {
                std::cout << "\033[0;34m" << octopuses[i][k] << "\033[0m ";
            } else {
                std::cout << "\033[0;37m" << octopuses[i][k] << "\033[0m ";
            }
        }
        std::cout << std::endl;
    }
    #endif
}

int main () {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */
    
    int backup_octopuses[10][10];

    for ( int i = 0; i < 10; i++ ) {
		std::string line;
        char level;
		std::getline(input, line);
        std::istringstream linestream(line);
        for ( int k = 0; k < 10; k++ ) {
            linestream >> level;
            octopuses[i][k] = level-'0';
            backup_octopuses[i][k] = level-'0';
        }
    }

	/* --- Part 1 --- */

    for (int step = 0; step < 100; step++) {
        
        print(step);
        reset_flashed();

        for ( int i = 0; i < 10; i++ ) {
            for ( int k = 0; k < 10; k++ ) {
                octopuses[i][k]++;
                if ( octopuses[i][k] > 9 && !flashed[i][k] ) { octopuses[i][k] = 0; flashed[i][k] = true; flashes++; flash(i,k); }
            }
        }
        for ( int i = 0; i < 10; i++ ) {
            for ( int k = 0; k < 10; k++ ) {
                if ( flashed[i][k] ) {
                    octopuses[i][k] = 0;
                }
            }
        }
    }

	std::cout << "Part1: " <<  flashes << std::endl;

	/* --- Part 2 --- */

    for ( int i = 0; i < 10; i++ ) {
        for ( int k = 0; k < 10; k++ ) {
            octopuses[i][k] = backup_octopuses[i][k];
        }
    }
    
    int step = 0;
    while ( true ) {
        print(step);
        reset_flashed();

        for ( int i = 0; i < 10; i++ ) {
            for ( int k = 0; k < 10; k++ ) {
                octopuses[i][k]++;
                if ( octopuses[i][k] > 9 && !flashed[i][k] ) { octopuses[i][k] = 0; flashed[i][k] = true; flashes++; flash(i,k); }
            }
        }

        for ( int i = 0; i < 10; i++ ) {
            for ( int k = 0; k < 10; k++ ) {
                if ( flashed[i][k] ) {
                    octopuses[i][k] = 0;
                }
            }
        }

        if ( did_all_flash() ) {
            step++;
            print(step);
            break;
        }
        step++;
    }

	std::cout << "Part2: " <<  step << std::endl;

    return 0;
}