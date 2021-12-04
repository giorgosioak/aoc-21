#include <iostream>
#include "board.hpp"

Board::Board() {
    reset();
}

/* Reset mark board */
void Board::reset(){
    win = false;
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++) {
            marked[i][k] = 0;    
        }
    }
}

/* Check rows for bingo!  */
bool Board::checkrows(){
    for (int i = 0; i < 5; i++) {
        int sum = 0;
        for (int k = 0; k < 5; k++) {
            sum += marked[i][k];
        }
        if ( sum == 5 ) return true;
    }
    return false;
}

/* Check cols for bingo!  */
bool Board::checkcols(){
    for (int i = 0; i < 5; i++) {
        int sum = 0;
        for (int k = 0; k < 5; k++) {
            sum += marked[k][i];
        }
        if ( sum == 5 ) return true;
    }
    return false;
}

/* Check rows and cols for bingo!  */
bool Board::check() {
    return checkrows() || checkcols();
}

/* Print the bingo board  */
void Board::print() {
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++) {
            std::cout << bingo[i][k];
            if ( k < 4 ) std::cout << " ";
        }
        std::cout << std::endl;
    }
}

/* Print the mark board  */
void Board::printmarked() {
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++) {
            std::cout << marked[i][k];
            if ( k < 4 ) std::cout << " ";
        }
        std::cout << std::endl;
    }
}

/* If <number> is found in bingo board mark it  */
void Board::mark(int number) {
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++) {
            
            if ( number == bingo[i][k] ) {
                marked[i][k] = 1;
                return;
            }

        }
    }
}

/* Get the sum of the unmarked numbers in bingo board */
int Board::unmarkedsum() {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++) {
            
            sum += bingo[i][k] * ( 1 ^ marked[i][k] );

        }
    }
    return sum;
}