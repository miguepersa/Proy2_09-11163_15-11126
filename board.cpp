#include "board.h"

Board::Board()
{
    board.push_back({"  ", "  A", "  B", "  C", "  D", "  E", "  F", "  G", "  H", "  I", "  J", "  K", "  L", "  M", "  N", "  O", "  P", "  Q", "  R", "  S"});

    for (int i = 1; i <= 19; i++ ) {
        string linestr = i < 10 ? to_string(i) + "  " : to_string(i) + " ";
        board.push_back({linestr, "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-"});
    }
}

Board::~Board()
{
}


void Board::print_board() {
    for (uint i = 0; i < board.size(); i++) {
        vector<string> row = board[i];

        for (uint j = 0; j < row.size(); j++) {
            cout << row[j];
        }
        cout << endl;
    }
    cout << endl;

    cout << (int) 'S' << endl;
}

bool Board::make_play(string coord) {
    
    int col = get_col_index(coord[0]);
    int row = atoi(coord.substr(1).c_str());

    if (
        col < 1 || col > 19 ||
        row < 1 || row > 19
    ) {
        
    }
}

int get_col_index(char c) {

    int val = toupper((int)c) - 64;

    if (val < 1 || val > 19) {
        return -1;
    }

    return val;

}