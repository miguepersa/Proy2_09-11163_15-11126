#ifndef WHITE_TURN
#define WHITE_TURN 0
#endif

#ifndef BLACK_TURN
#define BLACK_TURN 1
#endif

#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
#include "agent.h"

using namespace std;

string convert_to_string(int i, int j);
int main(int argc, char const *argv[])
{
    if (argc < 3) {
        cout << "args error" << endl;
        return 1;

    }

    Board board;
    int turn = 0;
    string move;
    string fichas = argv[1];
    string time = argv[2];
    if (fichas != "blancas" && fichas != "negras") {
        cout << "Error al indicar color de fichas. Ingrese un color valido <blancas|negras>" << endl;
        return 1;
    }

    int agent_turn = fichas == "blancas" ? WHITE_TURN : BLACK_TURN;
    int player_turn = agent_turn == WHITE_TURN ? BLACK_TURN : WHITE_TURN;
    vector<vector<int>> status;
    Agent agent(agent_turn, player_turn, stoi(time));

    board.print_board();


    while (board.winner == -1) {

        if (turn == agent_turn) {
            cout << "Turno del agente" << endl << endl;
            status = board.get_board_status();
            pair<int, int> move1 = agent.findBestMove(status);

            board.make_play(convert_to_string(move1.first, move1.second), agent_turn);

            if (board.winner != -1) {
                break;
            }
            
            status = board.get_board_status();

            pair<int, int> move2 = agent.findBestMove(status);
            
            board.make_play(convert_to_string(move2.first, move2.second), agent_turn);
            turn = player_turn;
            board.print_board();

            if (board.winner != -1) {
                break;
            }

        } else {

            cout << "Turno del jugador" << endl << endl;
            cout << "Indique su primer movimiento: ";
            cin >> move;

            while (!board.make_play(move, player_turn)) {
                cout << "Movimiento invalido. Ingrese un movimiento valido: ";
                cin >> move;
            }

            board.print_board();

            if (board.winner != -1) {
                break;
            }

            cout << "Indique su segundo movimiento: ";
            cin >> move;

            while (!board.make_play(move, player_turn)) {
                cout << "Movimiento invalido. Ingrese un movimiento valido: ";
                cin >> move;
            }

            board.print_board();


            turn = agent_turn;
        }

        

    }

    cout << "Ganador: " << (board.winner == agent_turn ? "Agent" : "Jugador") << endl;
    return 0;
}

string convert_to_string(int i, int j) {
    stringstream m;
    char col = (char)(i + 65);
    m << col << (j + 1);
    return m.str();
}