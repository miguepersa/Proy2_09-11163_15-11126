#ifndef WHITE_TURN
#define WHITE_TURN 0
#endif

#ifndef BLACK_TURN
#define BLACK_TURN 1
#endif

#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include <utility>
#include <bits/stdc++.h>

using namespace std;

class Agent {
    private:

    vector<vector<int>> status;
    int turn;
    int enemy;
    int time;
    
    public:

    Agent(int, int, int);
    ~Agent();
    vector<pair<int, int>> get_available_moves();
    bool check_surroundings(int, int);
    int alphaBeta(int, int, int, bool);
    pair<int, int> findBestMove(vector<vector<int>>);
    int evaluateBoard();
    bool checkWin(int);
    int evaluatePosition(int x, int y, int player);
    int scoreLine(int x, int y, int dx, int dy, int player);
};

#endif