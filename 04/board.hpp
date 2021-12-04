#ifndef BOARD_H__
#define BOARD_H__

class Board {
  public:
    int bingo[5][5];
    int marked[5][5];
    bool win = false;

    Board();
    void reset();
    bool checkrows();
    bool checkcols();
    bool check();
    void print();
    void printmarked();
    void mark(int);
    int unmarkedsum();
};

#endif