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
    vector<pair<int, int>> get_available_moves(vector<vector<int>>);
    bool check_surroundings(int, int, vector<vector<int>>);
    int alphaBeta(int, int, int, bool);
    pair<int, int> findBestMove(vector<vector<int>>);
    int evaluateBoard();
    bool checkWin(int);
};

#endif