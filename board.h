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
    int winner = -1;

    Board();
    ~Board();
    void print_board();
    bool make_play(string, int);
    int get_col_index(char);
    bool is_valid_move(int, int);
    bool is_win(int, int, int);
    vector<vector<string>> get_board();
    vector<vector<int>> get_board_status();
    void print_board_status();
};

#endif