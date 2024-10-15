#ifndef GAMEOF9TH_GAMEHISTORY_H
#define GAMEOF9TH_GAMEHISTORY_H

#include "moves.h"
#include "gameState.h"
#include <unordered_map>
#include <vector>
#include <iostream>

class gameHistory{
public:
    gameHistory();
    gameHistory(const gameHistory& gh);
    void addMove(int move);
    [[nodiscard]] size_t getLength() const;
    [[nodiscard]] std::vector<int> getMoves() const;
    gameHistory reverse();
    void print() const;
    void printFull(gameState state) const;
private:
    std::vector<int> history;
};

#endif //GAMEOF9TH_GAMEHISTORY_H
