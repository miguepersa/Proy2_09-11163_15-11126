#include <iostream>
#include "board.h"

#define WHITE_TURN 0
#define BLACK_TURN 1

int main(int argc, char const *argv[])
{
    Board board;

    board.make_play("K9", BLACK_TURN);
    board.make_play("l8", BLACK_TURN);
    board.make_play("i11", BLACK_TURN);
    board.make_play("h12", BLACK_TURN);
    board.make_play("g13", BLACK_TURN);
    board.print_board();
    cout << "Winner: " << board.winner << endl;
    return 0;
}
