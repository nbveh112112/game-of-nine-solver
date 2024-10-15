#include "gameHistory.h"

gameHistory::gameHistory() = default;
gameHistory::gameHistory(const gameHistory& gh) {
    history = gh.history;
}

void gameHistory::addMove(int move) {
    history.push_back(move);
}

[[nodiscard]] size_t gameHistory::getLength() const {
    return history.size();
}

[[nodiscard]] std::vector<int> gameHistory::getMoves() const {
    return history;
}

gameHistory gameHistory::reverse() {
    std::reverse(history.begin(), history.end());
    for (int i = 0; i < history.size(); i++) {
        switch (history[i]) {
            case left:
                history[i] = right;
                break;
            case right:
                history[i] = left;
                break;
            case up:
                history[i] = down;
                break;
            case down:
                history[i] = up;
                break;
        }
    }
    return *this;
}

void gameHistory::print() const {
    for (int move : history) {
        switch (move) {
            case left:
                std::cout << "left ";
                break;
            case right:
                std::cout << "right ";
                break;
            case up:
                std::cout << "up ";
                break;
            case down:
                std::cout << "down ";
                break;
            default:
                throw std::runtime_error("Impossible move");
        }
    }
    std::cout << std::endl;
}

void gameHistory::printFull(gameState state) const {
    std::cout << "solution: \n";
    state.print();
    for (int move : history) {
        switch (move) {
            case left:
                std::cout << "left \n";
                break;
            case right:
                std::cout << "right \n";
                break;
            case up:
                std::cout << "up \n";
                break;
            case down:
                std::cout << "down \n";
                break;
            default:
                throw std::runtime_error("Impossible move");
        }
        state.move(move);
        state.print();
    }
    std::cout << std::endl;
}
