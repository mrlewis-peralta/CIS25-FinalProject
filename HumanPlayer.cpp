//
// Created by lib_laptop on 11/26/2025.
//

#include "HumanPlayer.h"
#include <iostream>
#include <limits>

HumanPlayer::HumanPlayer(char symbol, const std::string& name) : Player(symbol, name) {}

void HumanPlayer::makeMove(Board& board) {
    int choice = 0;

    while (true) {
        // Show the number pad mapping
        std::cout << "\nSelect your move using the number pad layout:\n\n";
        std::cout << "  7 | 8 | 9\n";
        std::cout << " ---+---+---\n";
        std::cout << "  4 | 5 | 6\n";
        std::cout << " ---+---+---\n";
        std::cout << "  1 | 2 | 3\n\n";

        std::cout << getName() << " (" << getSymbol() << "), enter a number (1-9): ";

        std::cin >> choice;

        if (!std::cin) {
            // Handle non-numeric input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number from 1 to 9.\n";
            continue;
        }

        if (choice < 1 || choice > 9) {
            std::cout << "Choice must be between 1 and 9.\n";
            continue;
        }

        // Map numpad choice to (row, col)
        int row = 0, col = 0;
        switch (choice) {
            case 7: row = 0; col = 0; break;
            case 8: row = 0; col = 1; break;
            case 9: row = 0; col = 2; break;
            case 4: row = 1; col = 0; break;
            case 5: row = 1; col = 1; break;
            case 6: row = 1; col = 2; break;
            case 1: row = 2; col = 0; break;
            case 2: row = 2; col = 1; break;
            case 3: row = 2; col = 2; break;
        }

        if (board.isValidMove(row, col)) {
            board.applyMove(row, col, getSymbol());
            break;
        } else {
            std::cout << "That cell is already occupied. Try again.\n";
        }
    }
}