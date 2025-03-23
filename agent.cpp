#include "agent.h"
#define SIZE 19
#define INF 100000

Agent::Agent(int picked_turn, int enemy_turn, int limit_time) {
    turn = picked_turn;
    enemy = enemy_turn;
    time = limit_time;
}

Agent::~Agent() {}

vector<pair<int, int>> Agent::get_available_moves() {

    vector<pair<int, int>> moves;

    for (unsigned int i = 0; i < status.size(); i++ ) {
        for (unsigned int j = 0; j < status[i].size(); j++ ) {
            if (status[i][j] == -1 && check_surroundings(i, j)) {
                moves.push_back({i, j});
            }
        }
    }

    return moves;
}

bool Agent::check_surroundings(int pos_i, int pos_j) {

    for ( int i = -1; i < 2; i++ ) {
        for ( int j = -1; j < 2; j++ ) {
            if (
                (i == 0 && j == 0) || 
                pos_i + i < 0   || pos_i + i >= 18  ||
                pos_j + j < 0   || pos_j + j >= 18
            ) {
                continue;
            }

            if (status[pos_i + i][pos_j + j] != -1) {
                return true;
            }
        }
    }

    return false;

}

// Nuevo algoritmo Alpha-Beta con profundidad
int Agent::alphaBeta(int depth, int alpha, int beta, bool isMaximizing) {
    if (depth == 0 || checkWin(turn) || checkWin(enemy))
        return evaluateBoard();

    vector<pair<int, int>> moves = get_available_moves(status);

    if (isMaximizing) {
        int maxEval = -INF;
        for (auto move : moves) {
            status[move.first][move.second] = turn;
            int eval = alphaBeta(depth - 1, alpha, beta, false);
            status[move.first][move.second] = -1; 
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    } else {
        int minEval = INF;
        for (auto move : moves) {
            status[move.first][move.second] = enemy;
            int eval = alphaBeta(depth - 1, alpha, beta, true);
            status[move.first][move.second] = -1; 
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

pair<int, int> Agent::findBestMove(vector<vector<int>> board) {
    status = board;
    vector<pair<int, int>> moves = get_available_moves();

    if (moves.empty()) return {-1, -1};

    pair<int, int> bestMove;
    int bestValue = -INF;
    for (size_t i = 0; i < min(moves.size(), (size_t)10); i++) {
        status[moves[i].first][moves[i].second] = turn;
        int moveValue = alphaBeta(0, -INF, INF, false);
        status[moves[i].first][moves[i].second] = -1;

        if (moveValue > bestValue) {
            bestMove = moves[i];
            bestValue = moveValue;
        }
    }
    return bestMove;
}

bool Agent::checkWin(int player) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (status[i][j] == player) {
                if (j <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (status[i][j + k] != player) { win = false; break; }
                    if (win) return true;
                }
                if (i <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (status[i + k][j] != player) { win = false; break; }
                    if (win) return true;
                }
                if (i <= SIZE - 6 && j <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (status[i + k][j + k] != player) { win = false; break; }
                    if (win) return true;
                }
                if (i >= 5 && j <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (status[i - k][j + k] != player) { win = false; break; }
                    if (win) return true;
                }
            }
        }
    }
    return false;
}

int Agent::evaluateBoard() {
    if (checkWin(enemy)) return INF;
    if (checkWin(turn)) return -INF;
    return rand() % 100;
}
