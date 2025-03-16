#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Board
{
private:
    vector<vector<string>> board = {};
public:
    Board();
    ~Board();
    void print_board();
    bool make_play(string);
};

#endif