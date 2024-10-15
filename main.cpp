#include <iostream>
#include <vector>
#include <unordered_map>

#include "gameState.h"
#include "moves.h"
#include "solver.h"
#include "gameHistory.h"


void play(gameState &state) {
    char move;
    while (true){
        std ::cin >> move;
        switch (move) {
            case 'w':
                state.move(moves::up);
                break;
            case 'a':
                state.move(moves::left);
                break;
            case 's':
                state.move(moves::down);
                break;
            case 'd':
                state.move(moves::right);
                break;
            default:
                return;
        }
        system("cls");
        state.print();
    }
}


int main() {
    Solver solver = Solver();
    std::vector<int> board = { 1, 2, 3, 4, 5, 6, 7, 8, 0};
    gameState state(board);
    state.print();

    board = std::vector<int> {7, 3, 2, 5, 6, 8, 4, 0, 1,};
    gameState state2(board);
    state2.print();

    gameHistory history = solver.solve(state2, state);

    history.print();
    history.printFull(state2);

    return 0;
}