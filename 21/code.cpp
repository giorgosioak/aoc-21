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
#include <limits>

#define RED   "\033[0;31m"
#define GRN   "\033[0;32m"
#define YEL   "\033[0;33m"
#define BLU   "\033[0;34m"
#define MAG   "\033[0;35m"
#define CYN   "\033[0;36m"
#define WHT   "\033[0;37m"
#define RST "\033[0;0m"

unsigned long long win1 = 0, win2 = 0;

void quantum(int pos1, int score1, int pos2, int score2, int player, unsigned long multiplier) {

    int new_pos;

    // Throw dice 3 times for each player
    if ( player == 1 ) {

        // Case 111 = 3
        new_pos = pos1+3;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score1 + new_pos >= 21 ) { win1+=multiplier; } 
        else { quantum(new_pos,score1+new_pos,pos2,score2,2,multiplier); }

        // Case 112 121 211 = 4
        new_pos = pos1+4;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score1 + new_pos >= 21 ) { win1+=multiplier*3; } 
        else { quantum(new_pos,score1+new_pos,pos2,score2,2,multiplier*3); }

        // Case 113 122 131 212 221 311 = 5
        new_pos = pos1+5;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score1 + new_pos >= 21 ) { win1+=multiplier*6; } 
        else { quantum(new_pos,score1+new_pos,pos2,score2,2,multiplier*6); }

        // Case 123 132 213 222 231 312 321 = 6
        new_pos = pos1+6;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score1 + new_pos >= 21 ) { win1+=multiplier*7; } 
        else { quantum(new_pos,score1+new_pos,pos2,score2,2,multiplier*7); }

        // Case 133 223 232 313 322 331 = 7
        new_pos = pos1+7;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score1 + new_pos >= 21 ) { win1+=multiplier*6; } 
        else { quantum(new_pos,score1+new_pos,pos2,score2,2,multiplier*6); }

        // Case 233 323 332 = 8
        new_pos = pos1+8;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score1 + new_pos >= 21 ) { win1+=multiplier*3; } 
        else { quantum(new_pos,score1+new_pos,pos2,score2,2,multiplier*3); }
        
        // Case 333 = 9
        new_pos = pos1+9;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score1 + new_pos >= 21 ) { win1+=multiplier; } 
        else { quantum(new_pos,score1+new_pos,pos2,score2,2,multiplier); }

    } else {

        // Case 111 = 3
        new_pos = pos2+3;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score2 + new_pos >= 21 ) { win2+=multiplier; }
        else { quantum(pos1,score1,new_pos,score2+new_pos,1,multiplier); }

        // Case 112 121 211 = 4
        new_pos = pos2+4;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score2 + new_pos >= 21 ) { win2+=multiplier*3; }
        else { quantum(pos1,score1,new_pos,score2+new_pos,1,multiplier*3); }

        // Case 113 122 131 212 221 311 = 5
        new_pos = pos2+5;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score2 + new_pos >= 21 ) { win2+=multiplier*6; }
        else { quantum(pos1,score1,new_pos,score2+new_pos,1,multiplier*6); }

        // Case 123 132 213 222 231 312 321 = 6
        new_pos = pos2+6;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score2 + new_pos >= 21 ) { win2+=multiplier*7; }
        else { quantum(pos1,score1,new_pos,score2+new_pos,1,multiplier*7); }

        // Case 133 223 232 313 322 331 = 7
        new_pos = pos2+7;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score2 + new_pos >= 21 ) { win2+=multiplier*6; }
        else { quantum(pos1,score1,new_pos,score2+new_pos,1,multiplier*6); }

        // Case 233 323 332 = 8
        new_pos = pos2+8;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score2 + new_pos >= 21 ) { win2+=multiplier*3; }
        else { quantum(pos1,score1,new_pos,score2+new_pos,1,multiplier*3); }
        
        // Case 333 = 9
        new_pos = pos2+9;
        while ( new_pos > 10 ) { new_pos -= 10; }
        if ( score2 + new_pos >= 21 ) { win2+=multiplier; }
        else { quantum(pos1,score1,new_pos,score2+new_pos,1,multiplier); }
    }

    return;
}

int main() {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */
    
    std::vector<std::vector<int>> graph;

    std::string line;

    int start_pos1, start_pos2;

    std::getline(input, line); 
    line.replace(line.find("Player 1 starting position: "),28,""); start_pos1 = std::stoi(line);

    std::getline(input, line);
    line.replace(line.find("Player 2 starting position: "),28,""); start_pos2 = std::stoi(line);


    std::cout << "pos1: " << start_pos1 <<  ", pos2: " << start_pos2 << std::endl;

    /* --- Part 1 --- */

    int pos1 = start_pos1, pos2 = start_pos2;
    int dice = 0, rolls = 0;
    int curr = 1;

    int score1 = 0, score2 = 0;
    while ( score1 < 1000 && score2 < 1000 ) {

        rolls+=3;
        int add_pos = dice+1 + dice+2 + dice+3;
        dice+=3; if ( dice > 100 ) { dice -= 100; }
        if ( curr == 3 ) { curr = 1; }

        // std::cout << "#" << rolls << ", dice: " << dice;

        if ( curr == 1 ) {
            pos1 += add_pos; while ( pos1 > 10 ) { pos1 -= 10; }
            score1 += pos1;
            // std::cout << MAG << "\t> Player 1: pos: " << pos1 << ", score: " << score1 << RST << std::endl;
        } else {
            pos2 += add_pos; while ( pos2 > 10 ) { pos2 -= 10; }
            score2 += pos2;
            // std::cout << YEL << "\t> Player 2: pos: " << pos2 << ", score: " << score2 << RST << std::endl;
        }
        curr++;
    }

    int loser = ( score1 < 1000 ) ? score1 : score2;

    std::cout << "Part 1: " << rolls*loser << " [ " << loser << "*" << rolls << " ]" << std::endl;
    
    /* --- Part 2 --- */

    quantum(start_pos1,0,start_pos2,0,1,1);

    if ( win1 > win2 ) {
        std::cout << "Part 2: " << win1 << " > " << win2 << std::endl;
    } else {
        std::cout << "Part 2: " << win2 << " > " << win1 << std::endl;
    }    

    return 0;

}