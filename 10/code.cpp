#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include <bits/stdc++.h>
#include <stack>

void remove_complete_lines(std::vector<std::vector<char>> &);

int main () {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */
    
    std::vector<std::vector<char>> data;
     
    while ( !input.eof() ) {
        bool is_input = true;
		std::string line;
        char c;

        std::vector<char> row;

		std::getline(input, line);
        std::istringstream linestream(line);
		while (linestream >> c) {
            row.push_back(c);
		}
        data.push_back(row);
	}

    remove_complete_lines(data);

	/* --- Part 1 --- */

    int score = 0;
    for ( int i = 0; i < data.size(); i++ ) {

        std::stack<char> stack;
        bool illegal_found = false;

        for ( int k = 0; k < data[i].size(); k++ ) {

            switch (data[i][k]){
            case '(':
            case '[':
            case '{':
            case '<': stack.push(data[i][k]); break;
            case ')': if ( stack.top() == '(' ) { stack.pop(); } else { score +=     3; illegal_found = true; } break;
            case ']': if ( stack.top() == '[' ) { stack.pop(); } else { score +=    57; illegal_found = true; } break;
            case '}': if ( stack.top() == '{' ) { stack.pop(); } else { score +=  1197; illegal_found = true; } break;
            case '>': if ( stack.top() == '<' ) { stack.pop(); } else { score += 25137; illegal_found = true; } break; 
            default:
                break;
            }

            /* If found continue to next and remove row for part 2 */

            if ( illegal_found ) {
                data.erase(data.begin()+i);
                i--;
                break;
            }

        }
    }

	std::cout << "Part1: " << score << std::endl;

	/* --- Part 2 --- */

    /* Complete and illegal lines are already removed */

    std::vector<long> scores;

    for ( int i = 0; i < data.size(); i++ ) {

        std::stack<char> stack;
        long local_score = 0;

        for ( int k = 0; k < data[i].size(); k++ ) {
            switch (data[i][k]){
            case '(':
            case '[':
            case '{':
            case '<': stack.push(data[i][k]); break;
            case ')': if ( stack.top() == '(' ) { stack.pop(); } break;
            case ']': if ( stack.top() == '[' ) { stack.pop(); } break;
            case '}': if ( stack.top() == '{' ) { stack.pop(); } break;
            case '>': if ( stack.top() == '<' ) { stack.pop(); } break;
            default:
                break;
            }
        }
        
        while ( !stack.empty() ) {
            switch (stack.top()){
            case '(': local_score = local_score*5 + 1; break;
            case '[': local_score = local_score*5 + 2; break;
            case '{': local_score = local_score*5 + 3; break;
            case '<': local_score = local_score*5 + 4; break;
            }
            stack.pop();
        }

        scores.push_back(local_score);

    }

    sort(scores.begin(), scores.end());

	std::cout << "Part2: " <<  scores[round(scores.size()/2)] << std::endl;

    return 0;
}


/* Remove complete lines */

void remove_complete_lines(std::vector<std::vector<char>> &data) {


    for ( int i = 0; i < data.size(); i++ ) {

        std::stack<int> stack;
        bool illegal_found = false;
    
        for ( int k = 0; k < data[i].size(); k++ ) {

            switch (data[i][k]){
            case '(':
            case '[':
            case '{':
            case '<': stack.push(data[i][k]); break;
            case ')': if ( stack.top() == '(' ) { stack.pop(); } break;
            case ']': if ( stack.top() == '[' ) { stack.pop(); } break;
            case '}': if ( stack.top() == '{' ) { stack.pop(); } break;
            case '>': if ( stack.top() == '<' ) { stack.pop(); } break;
            default:
                break;
            }

            if ( illegal_found ) {
                break;
            }

        }

        /* Complete line */
        if ( stack.empty() ) {
            data.erase(data.begin()+i);
            i--;
        }
    }
}