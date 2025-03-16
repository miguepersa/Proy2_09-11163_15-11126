#include <iostream>
#include "board.h"

#define WHITE_TURN 0
#define BLACK_TURN 1

int main(int argc, char const *argv[])
{
    Board board;

    board.print_board();

    return 0;
}
