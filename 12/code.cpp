#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include <bits/stdc++.h>
#include <stack>

#include "graph.hpp"

// #define VISUALIZATION // uncomment to view visuals

int main () {

    Graph passage;

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */
    
    int backup_octopuses[10][10];

    while ( !input.eof() ) {
		std::string line, node, neighbor;
		std::getline(input, line);
	    std::replace( line.begin(), line.end(), '-', ' ');
        std::istringstream linestream(line);

        linestream >> node >> neighbor;
        int x = passage.addNode(node);
        int y = passage.addNode(neighbor);
        passage.addEdge(x,y);
    }

	/* --- Part 1 --- */

    // passage.print();
    int start = passage.addNode("start");
    int end = passage.addNode("end");

    passage.findPaths_1(start,end); 

	std::cout << "Part1: " << passage.getPathsSize() << std::endl;

	/* --- Part 2 --- */

    passage.findPaths_2(start,end);
    // passage.printPaths();

	std::cout << "Part2: " << passage.getPathsSize() << std::endl;


    return 0;
}