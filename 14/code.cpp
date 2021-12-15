#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include <bits/stdc++.h>
#include <stack>
#include <tuple>
#include <map>

int main () {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */
    
    std::map<std::string,std::pair<std::string,std::string>> data;
    std::map<std::string,long> appear, temp;
    std::map<char,long> count;

    std::string polymer;
    long max, min;

    std::getline(input, polymer);

    std::string line;    
    std::getline(input, line); // skip empty line

    while ( std::getline(input, line) ) {
		line.replace(line.find(" -> "),4," ");
        std::istringstream linestream(line);

        std::string s; char c;

        linestream >> s >> c;


        std::string output_left = std::string()+ s[0] + c;
        std::string output_right = std::string() + c + s[1];

		data[s] = {output_left,output_right};

        // std::cout << s << " -> { " << output_left << " , " << output_right << " }" << std::endl;
	}

    /* init appearances */

    for (int i = 0; i < polymer.size()-1; i++) {
        std::string s = std::string() + polymer[i] + polymer[i+1];
        appear[s]++;
    }

    /* loop 10 times */

    count = {};
    for (int step = 1; step <= 10; step++) {
        temp = {};
        for (auto t : appear) {
            if ( t.second > 0 ) {
                temp[data[t.first].first] += t.second;
                temp[data[t.first].second] += t.second;
            }
        }
        appear = temp;
    }

    for (auto a : appear) {
        count[a.first[0]] += a.second;
    }

    max = 0;
    min = 0;
    count[polymer.back()]++;
    for (auto c : count ){
        if ( max == 0 ) { max = min = c.second; continue; }
        if ( c.second > max ) {
            max = c.second;
        }
        if ( c.second < min ) {
            min = c.second;
        }
    }

	std::cout << "Part1: " <<  max-min << std::endl;

    /* loop 30 more times */

    count = {};
    for (int step = 11; step <= 40; step++) {
        temp = {};
        for (auto t : appear) {
            if ( t.second > 0 ) {
                temp[data[t.first].first] += t.second;
                temp[data[t.first].second] += t.second;
            }
        }
        appear = temp;
    }

    for (auto a : appear) {
        count[a.first[0]] += a.second;
    }

    max = 0;
    min = 0;
    count[polymer.back()]++;
    for (auto c : count ){
        if ( max == 0 ) { max = min = c.second; continue; }
        if ( c.second > max ) {
            max = c.second;
        }
        if ( c.second < min ) {
            min = c.second;
        }
    }

	std::cout << "Part2: " <<  max-min << std::endl;


    return 0;
}