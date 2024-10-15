#include <vector>
#ifndef GAMEOF9TH_GAMESTATE_H
#define GAMEOF9TH_GAMESTATE_H


class gameState {
public:
    gameState();
    explicit gameState(unsigned int code);
    explicit gameState(const std::vector<int>& board);
    gameState(const gameState& other);
    void setCode(unsigned int c);
    [[nodiscard]] unsigned int getCode() const;
    [[nodiscard]] int getPossibleMoves() const;
    void move(int move);
    [[nodiscard]] std::vector<int> getBoard() const;
    void setBoard(const std::vector<int>& board);
    void print() const;
    [[nodiscard]] int calculateSum() const;
private:
    // 4 bits is position of empty cell, 1 empty bit, 9 times 3 bits for each cell to code numbers 0-7 representing 1-8
    // empty cell codes as 7 for future simplisity
    unsigned int code;
};

class gameStateHash {
public:
    size_t operator()(const gameState& state) const;
};

class gameStateEqual {
public:
    bool operator()(const gameState& lhs, const gameState& rhs) const;
};


#endif //GAMEOF9TH_GAMESTATE_H
