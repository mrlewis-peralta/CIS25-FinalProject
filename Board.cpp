//
// Created by lib_laptop on 11/26/2025.
//

#include "Board.h"
#include <iostream>

Board::Board() : filledCells(0) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            grid[r][c] = ' ';  // empty cell
        }
    }
}

void Board::display() const {
    std::cout << "\n   0   1   2\n";
    for (int r = 0; r < 3; r++) {
        std::cout << r << "  ";
        for (int c = 0; c < 3; c++) {
            std::cout << grid[r][c];
            if (c < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (r < 2) {
            std::cout << "  ---+---+---\n";
        }
    }
    std::cout << "\n";
}

// Getter
char Board::getCellValue(int row, int col) const {
    // assume valid indices for now
    return grid[row][col];
}

bool Board::isValidMove(int row, int col) const {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) return false;
    else return (grid[row][col] == ' ');
}

void Board::applyMove(int row, int col, char symbol) {
    // Caller should already have checked isValidMove
    if (isValidMove(row, col)) {
        grid[row][col] = symbol;
        ++filledCells;
    }
}

bool Board::winCheck(char symbol) const {
    // rows
    for (int r = 0; r < 3; ++r) {
        if (grid[r][0] == symbol &&
            grid[r][1] == symbol &&
            grid[r][2] == symbol) {
            return true;
            }
    }

    // columns
    for (int c = 0; c < 3; ++c) {
        if (grid[0][c] == symbol &&
            grid[1][c] == symbol &&
            grid[2][c] == symbol) {
            return true;
            }
    }

    // diagonals
    if (grid[0][0] == symbol &&
        grid[1][1] == symbol &&
        grid[2][2] == symbol) {
        return true;
        }

    if (grid[0][2] == symbol &&
        grid[1][1] == symbol &&
        grid[2][0] == symbol) {
        return true;
        }

    return false;
}

bool Board::tieCheck() const {
    // full board and no winner for X or O
    if (filledCells < 9) {
        return false;
    }
    return !winCheck('X') && !winCheck('O');
}