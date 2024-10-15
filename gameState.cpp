#include <iostream>

#include "gameState.h"

gameState::gameState() : code(0) {}
gameState::gameState(unsigned int code) : code(code) {}
gameState::gameState(const std::vector<int>& board) : code(0) {
    setBoard(board);
}
gameState::gameState(const gameState& other) : code(other.code) {}
void gameState::setCode(unsigned int c) { code = c; }
[[nodiscard]] unsigned int gameState::getCode() const { return code; }
[[nodiscard]] int gameState::getPossibleMoves() const{ // returns 4 bits for left, up, down, right of history of not empty cell
    switch (code >> 28) {
        case 0:
            return 0b1100;
        case 1:
            return 0b1101;
        case 2:
            return 0b0101;
        case 3:
            return 0b1110;
        case 4:
            return 0b1111;
        case 5:
            return 0b0111;
        case 6:
            return 0b1010;
        case 7:
            return 0b1011;
        case 8:
            return 0b0011;

    }
    return 0;
}
void gameState::move(int move) {
    if ((getPossibleMoves() & move) == 0){
        throw std::runtime_error("Impossible move");
    }
    unsigned int movingCell;
    switch (move) {
        case 0b1000: // left
            //define value of moving cell
            movingCell = (code >> (((code >> 28) + 1) * 3)) & 0b111;
            //move it to its new position
            movingCell = movingCell << (3 * (code >> 28));
            //write it to code
            code = (code & ~(0b111 << (3 * (code >> 28)))) | movingCell;
            //write empty cell (0b111) to its new position
            code = code | (0b111 << (((code >> 28) + 1) * 3));
            //write position of empty cell to code
            code = (code & ~(0b1111 << 28)) | (((code >> 28) + 1) << 28);
            return;
        case 0b0100: // up
            movingCell = (code >> (((code >> 28) + 3) * 3)) & 0b111;
            movingCell = movingCell << (3 * (code >> 28));
            code = (code & ~(0b111 << (3 * (code >> 28)))) | movingCell;
            code = code | (0b111 << (((code >> 28) + 3) * 3));
            code = (code & ~(0b1111 << 28)) | (((code >> 28) + 3) << 28);
            return;
        case 0b0010: // down
            movingCell = (code >> (((code >> 28) - 3) * 3)) & 0b111;
            movingCell = movingCell << (3 * (code >> 28));
            code = (code & ~(0b111 << (3 * (code >> 28)))) | movingCell;
            code = code | (0b111 << (((code >> 28) - 3) * 3));
            code = (code & ~(0b1111 << 28)) | (((code >> 28) - 3) << 28);
            return;
        case 0b0001: // right
            movingCell = (code >> (((code >> 28) - 1) * 3)) & 0b111;
            movingCell = movingCell << (3 * (code >> 28));
            code = (code & ~(0b111 << (3 * (code >> 28)))) | movingCell;
            code = code | (0b111 << (((code >> 28) - 1) * 3));
            code = (code & ~(0b1111 << 28)) | (((code >> 28) - 1) << 28);
            return;
        default:
            throw std::runtime_error("Impossible move");
    }
}
[[nodiscard]] std::vector<int> gameState::getBoard() const {
    std::vector<int> board(9);
    for (int i = 0; i < 9; i++) {
        board[i] = ((code >> (i * 3)) & 0b111) + 1;
    }
    board[code >> 28] = 0;
    return board;
}
void gameState::setBoard(const std::vector<int>& board) {
    code = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            code = code | (i << 28);
            code = code | (0b111 << (i * 3));
        }
        else {
            code = code | (((board[i] - 1) & 0b111) << (i * 3));
        }
    }
}
void gameState::print() const {
    std::vector<int> board = getBoard();
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            std::cout << "  ";
        } else
            std::cout << board[i] << " ";
        if (i % 3 == 2) {
            std::cout << std::endl;
        }
    }
}
[[nodiscard]] int gameState::calculateSum() const {
    std::vector<int> board = getBoard();
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (board[i] > board[j] && board[i] != 0 && board[j] != 0) {
                sum += 1;
            }
        }
    }
    return sum;
}
bool gameStateEqual::operator()(const gameState& lhs, const gameState& rhs) const {
    return lhs.getCode() == rhs.getCode();
}
size_t gameStateHash::operator()(const gameState& state) const {
    return std::hash<unsigned int>()(state.getCode());
}