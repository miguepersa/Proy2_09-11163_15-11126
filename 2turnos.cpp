#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <algorithm>

#define SIZE 19
#define INF 100000

using namespace std;

char board[SIZE][SIZE];

void initBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '.';
}

void printBoard() {
    cout << "   ";
    for (int j = 0; j < SIZE; j++)
        cout << j % 10 << " ";
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i % 10 << " ";
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
}

bool checkWin(char player) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == player) {
                if (j <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (board[i][j + k] != player) { win = false; break; }
                    if (win) return true;
                }
                if (i <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (board[i + k][j] != player) { win = false; break; }
                    if (win) return true;
                }
                if (i <= SIZE - 6 && j <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (board[i + k][j + k] != player) { win = false; break; }
                    if (win) return true;
                }
                if (i >= 5 && j <= SIZE - 6) {
                    bool win = true;
                    for (int k = 0; k < 6; k++)
                        if (board[i - k][j + k] != player) { win = false; break; }
                    if (win) return true;
                }
            }
        }
    }
    return false;
}

vector<pair<int, int>> getAvailableMoves() {
    vector<pair<int, int>> moves;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '.') {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int ni = i + dx, nj = j + dy;
                        if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE && board[ni][nj] != '.') {
                            moves.push_back({i, j});
                            goto next_cell;
                        }
                    }
                }
            }
        next_cell:;
        }
    }
    return moves;
}

int evaluateBoard() {
    if (checkWin('W')) return INF;
    if (checkWin('B')) return -INF;
    return rand() % 100;
}

int alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer) {
    int score = evaluateBoard();
    if (score == INF || score == -INF || depth == 3) return score;

    vector<pair<int, int>> moves = getAvailableMoves();
    if (moves.empty()) return 0;

    if (maximizingPlayer) {
        int maxEval = -INF;
        for (size_t i = 0; i < min(moves.size(), (size_t)10); i++) {
            board[moves[i].first][moves[i].second] = 'B';
            int eval = alphaBeta(depth + 1, alpha, beta, false);
            board[moves[i].first][moves[i].second] = '.';
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    } else {
        int minEval = INF;
        for (size_t i = 0; i < min(moves.size(), (size_t)10); i++) {
            board[moves[i].first][moves[i].second] = 'W';
            int eval = alphaBeta(depth + 1, alpha, beta, true);
            board[moves[i].first][moves[i].second] = '.';
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

pair<int, int> findBestMove() {
    vector<pair<int, int>> moves = getAvailableMoves();
    if (moves.empty()) return {-1, -1};

    pair<int, int> bestMove;
    int bestValue = -INF;
    for (size_t i = 0; i < min(moves.size(), (size_t)10); i++) {
        board[moves[i].first][moves[i].second] = 'B';
        int moveValue = alphaBeta(0, -INF, INF, false);
        board[moves[i].first][moves[i].second] = '.';

        if (moveValue > bestValue) {
            bestMove = moves[i];
            bestValue = moveValue;
        }
    }
    return bestMove;
}

int main() {
    initBoard();
    printBoard();

    while (true) {
        int x, y;

        // 🚀 Turno del Jugador (2 movimientos)
        for (int i = 0; i < 2; i++) {
            cout << "Jugador (W), ingrese su movimiento #" << i + 1 << " (fila columna): ";
            cin >> x >> y;
            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] != '.') {
                cout << "Movimiento inválido. Intenta de nuevo.\n";
                i--;
                continue;
            }
            board[x][y] = 'W';
            printBoard();
        }

        // 🚀 Verificar si el jugador ganó
        if (checkWin('W')) {
            cout << "¡Ganaste!\n";
            break;
        }

        // 🚀 Turno de la IA (2 movimientos)
        cout << "🤖 La IA está pensando...\n";
        for (int i = 0; i < 2; i++) {
            pair<int, int> aiMove = findBestMove();
            if (aiMove.first == -1) {
                cout << "Empate.\n";
                break;
            }
            board[aiMove.first][aiMove.second] = 'B';
            printBoard();
        }

        // 🚀 Verificar si la IA ganó
        if (checkWin('B')) {
            cout << "La IA ganó. 😢\n";
            break;
        }
    }
    return 0;
}


