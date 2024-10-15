#include "solver.h"

Solver::Solver() : tableTo(), tableFrom() {
}
bool Solver::isSolvable(const gameState& from, const gameState& to) {
    return (from.calculateSum() - to.calculateSum()) % 2 == 0;
}
gameHistory Solver::solve(const gameState& from, const gameState& to) {
    if (!isSolvable(from, to)) {
        throw std::runtime_error("Not solvable");
    }
    tableTo[to] = gameHistory();
    tableFrom[from] = gameHistory();
    int possibleMoves;
    gameState newState;
    gameHistory newHistory;
    while (true){
        for (const auto& el : tableFrom) {
            possibleMoves = el.first.getPossibleMoves();
            for (auto move : allMoves) {
                if (possibleMoves & move) {
                    newState = gameState(el.first);
                    newState.move(move);
                    newHistory = gameHistory(tableFrom[el.first]);
                    newHistory.addMove(move);
                    if (tableTo.contains(newState)) {
                        return prepareSolution(newState, newHistory);
                    }
                    if (!tableFrom.contains(newState)) {
                        tableFrom[newState] = newHistory;
                    }
                }
            }
        }
        for (const auto& el : tableTo) {
            possibleMoves = el.first.getPossibleMoves();
            for (auto move : allMoves) {
                if (possibleMoves & move) {
                    newState = gameState(el.first);
                    newState.move(move);
                    newHistory = gameHistory(tableTo[el.first]);
                    newHistory.addMove(move);
                    if (!tableTo.contains(newState)) {
                        tableTo[newState] = newHistory;
                    }
                    if (tableFrom.contains(newState)) {
                        return prepareSolution(newState, tableFrom[newState]);
                    }
                }
            }
        }
    }
}
gameHistory Solver::prepareSolution(const gameState& state, gameHistory& history) {
    if (!tableTo.contains(state)) {
        throw std::runtime_error("Not solution found");
    }
    for (auto move : tableTo[state].reverse().getMoves()) {
        history.addMove(move);
    }
    return history;
}
