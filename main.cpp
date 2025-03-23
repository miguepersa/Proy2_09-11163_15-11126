#ifndef WHITE_TURN
#define WHITE_TURN 0
#endif

#ifndef BLACK_TURN
#define BLACK_TURN 1
#endif

#include <iostream>
#include<string>
#include "board.h"
#include "agent.h"

int main(int argc, char const *argv[])
{
    Board board;
    int turn = 0;
    string move;

    if (argv[1] != "blancas" && argv[1] != "negras") {
        cout << "Error al indicar color de fichas. Ingrese un color valido <blancas|negras>" << endl;
        return 1;
    }

    int agent_turn = argv[1] == 'blancas' ? WHITE_TURN : BLACK_TURN;
    int player_turn = agent_turn == WHITE_TURN ? BLACK_TURN : WHITE_TURN;

    Agent agent(agent_turn, player_turn, stoi(argv[2]));

    board.print_board_status();


    while (board.winner == -1) {

        if (turn == agent_turn) {
            cout << "Turno del agente" << endl << endl;

            pair<int, int> move1 = agent.findBestMove(board.get_board_status());
            board.make_play(convert_to_string(move1.first, move1.second), agent_turn);

            if (board.winner != -1) {
                break;
            }

            pair<int, int> move2 = agent.findBestMove(board.get_board_status());
            board.make_play(convert_to_string(move1.first, move1.second), agent_turn);

            turn = player_turn;
            board.print_board();

            if (board.winner != -1) {
                break;
            }
        } else {

            cout << "Turno del jugador" << endl << endl;
            cout << "Indique su primer movimiento: ";
            cin >> move;

            while (!make_play(move, player_turn)) {
                cout << "Movimiento invalido. Ingrese un movimiento valido: ";
                cin >> move;
            }

            board.print_board();

            cout << "Indique su segundo movimiento: ";
            cin >> move;

            while (!make_play(move, player_turn)) {
                cout << "Movimiento invalido. Ingrese un movimiento valido: ";
                cin >> move;
            }

            board.print_board();


            turn = agent_turn;
        }

        

    }

    cout << "Winner: " << board.winner << endl;
    return 0;
}

string convert_to_string(int i, int j) {
    stringstream m;
    char col = (char)(i + 65);
    m << vol << j;
    return m.str();
}