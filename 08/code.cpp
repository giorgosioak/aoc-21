#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include<bits/stdc++.h>
#include "entry.hpp"



int main () {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */
    
    std::vector<Entry> entrys;
     
    while ( !input.eof() ) {
        bool is_input = true;
		std::string line, display;

        Entry entry;

		std::getline(input, line);
        std::istringstream linestream(line);
		while (linestream >> display) {

            if ( display == "|" ) { is_input = false; continue; }

            sort(display.begin(), display.end());
            
            if ( is_input ) {
                entry.input.push_back(display);
            } else {
                entry.output.push_back(display);
            }            
		}
        entrys.push_back(entry);
	}

	/* --- Part 1 --- */

    int count = 0;

    for ( auto entry : entrys ) {
        for ( auto display : entry.output ) {
            switch (display.size()) {
                case 2:
                    /* Digit 1 uses 2 segments */
                case 4:
                    /* Digit 4 uses 4 segments */
                case 3:
                    /* Digit 7 uses 3 segments */
                case 7:
                    /* Digit 8 uses 7 segments */
                    count++;
                    break;
                default:
                    break;
            }
        }
    }

	std::cout << "Part1: " << count << std::endl;

	/* --- Part 2 --- */

    int sum = 0;
    for ( auto entry : entrys ) {
        entry.check();
        sum += entry.value;
    }

	std::cout << "Part2: " << sum << std::endl;

    return 0;
}