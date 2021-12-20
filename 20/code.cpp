#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include <bits/stdc++.h>
#include <stack>
#include <bitset>
#include <set>
#include <tuple>
#include <map>
#include <limits>

// #define input_file "example"
#define input_file "input"

std::string iea; // image enhancement algorithm

int apply(std::set<std::pair<int,int>> pixels,int operations,int size) {

    int min_size = -operations*2 - 1;
    int max_size = operations*2 + size + 1;

    for (int it = 0; it < operations; it++) {

        std::set<std::pair<int,int>> generated;
        
        for (int col = min_size; col <  max_size; col++) {
            for (int row = min_size; row < max_size; row++) {
                
                    std::string byte = std::string();
                    for (int i = row-1; i < row+2; i++) {
                        for (int k = col-1; k < col+2; k++) {
                            byte += (pixels.count({i,k})+'0');
                        }
                    }
                    std::bitset<9> b(byte);
                    
                    if( iea[b.to_ulong()] == '#' ) {
                        generated.insert({row,col});
                    }

            }
        }
        
        // std::cout << "Pixel size on operation " << it << " is: " << pixels.size() << std::endl;
        pixels = generated;
        max_size--; min_size++;

    }

    // std::cout << "Final pixel size is: " << pixels.size() << std::endl;
    return pixels.size();

}


int main() {

	/* Read input */

	if ( !std::filesystem::exists(input_file) ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input(input_file);

	/* Read data */
    
    std::vector<std::string> image;
    std::set<std::pair<int,int>> pixels;
    std:: string line;

    std::getline(input, iea);

    while ( std::getline(input, line) ) {
        if (line.empty()) { continue; }
        image.push_back(line);
    }

    const int SIZE = image.size();

    /* Save light pixels */

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
           if ( image[row][col] == '#' ) {
               pixels.insert({row,col});
           }
        }
    }
  
	/* --- Part 1 --- */

	std::cout << "Part 1: " << apply(pixels,2,SIZE) << std::endl;


	/* --- Part 2 --- */

	std::cout << "Part 2: " << apply(pixels,50,SIZE) << std::endl;

    





    return 0;
}