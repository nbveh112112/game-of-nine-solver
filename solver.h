#ifndef GAMEOF9TH_SOLVER_H
#define GAMEOF9TH_SOLVER_H

#include "moves.h"
#include "gameState.h"
#include "gameHistory.h"
#include <unordered_map>
#include <vector>
#include <iostream>

class Solver {
public:
    Solver();
    static bool isSolvable(const gameState& from, const gameState& to) ;
    gameHistory solve(const gameState& from, const gameState& to) ;
    gameHistory prepareSolution(const gameState& state, gameHistory& history) ;
private:
    std::unordered_map<gameState, gameHistory, gameStateHash, gameStateEqual> tableTo;
    std::unordered_map<gameState, gameHistory, gameStateHash, gameStateEqual> tableFrom;
};

#endif //GAMEOF9TH_SOLVER_H
