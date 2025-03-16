#include "board.h"

string BLANK = "-|-";
string WHITE = "-W-";
string BLACK = "-B-";
string turns[] = { WHITE, BLACK };

Board::Board()
{
    board.push_back({"  ", "  A", "  B", "  C", "  D", "  E", "  F", "  G", "  H", "  I", "  J", "  K", "  L", "  M", "  N", "  O", "  P", "  Q", "  R", "  S"});

    for (int i = 1; i <= 19; i++ ) {
        string linestr = i < 10 ? to_string(i) + "  " : to_string(i) + " ";
        board.push_back({linestr, "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-", "-|-"});
    }

    board[10][10] = BLACK;
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

}

bool Board::make_play(string coord, int turn) {
    
    int row = atoi(coord.substr(1).c_str());
    int col = get_col_index(coord[0]);

    if (!is_valid_move(row, col)) {
        return false;
    }

    this->board[row][col] = turns[turn];

    if (is_win(row, col, turn)) {
        this->winner = turn;
    }

    return true;
}

int Board::get_col_index(char c) {

    int val = toupper((int)c) - 64;

    if (val < 1 || val > 19) {
        return -1;
    }

    return val;

}

bool Board::is_valid_move(int row, int col){
    if (board[row][col] != BLANK) {
        return false;
    }

    for ( int i = -1; i < 2; i++ ) {
        for ( int j = -1; j < 2; j++ ) {

            if (
                (i == 0 && j == 0) ||
                row + i < 1 || row + i > 19 ||
                col + j < 1 || col + j > 19
            ) {
                continue;
            }

            if (board[row + i][col + j] != BLANK) {
                return true;
            }
        }
    }

    return false;
}

bool Board::is_win(int row, int col, int turn) {
    int connected;
    for ( int i = -1; i < 2; i++ ) {
        
        for ( int j = -1; j < 2; j++ ) {

            int curr_row = row + i;
            int curr_col = col + j;
            int v_dir = i;
            int h_dir = j;

            if (
                (i == 0 && j == 0) ||
                curr_row < 1 || curr_row > 19 ||
                curr_col < 1 || curr_col > 19 ||
                board[curr_row][curr_col] != turns[turn]
            ) {
                continue;
            }
            connected = 1;

            bool flipped = false;
            while (true) {
                if (
                    curr_row == 0 || curr_row > 19 ||
                    curr_col == 0 || curr_col > 19 ||
                    board[curr_row][curr_col] != turns[turn]
                ) {

                    if (flipped) {
                        
                        break;
                    }

                    flipped = true;
                    v_dir *= -1;
                    h_dir *= -1;
                    curr_row = row + v_dir;
                    curr_col = col + h_dir;

                } else {

                    connected++;
                    curr_row += v_dir;
                    curr_col += h_dir;
                }

            }

            if (connected >= 6) {
                return true;
            }
        }

    }

    return false;
}

vector<vector<string>> Board::get_board() {
    return board;
}