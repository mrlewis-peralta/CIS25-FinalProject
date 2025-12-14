//
// Created by lib_laptop on 11/26/2025.
//

#include "HumanPlayer.h"
#include <iostream>
#include <limits>
#include <cctype>   // NEW: for std::tolower
#include <string>   // NEW: for std::string

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

        // 🔹 Changed: read into a string instead of directly into an int
        std::string input;
        std::cin >> input;

        if (!std::cin) {
            // Handle totally broken stream
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number from 1 to 9.\n";
            continue;
        }

        // We only care about a single character (digit or letter)
        if (input.size() != 1) {
            std::cout << "Invalid input. Please enter a single key (1-9 or Q/W/E/A/S/D/Z/X/C).\n";
            continue;
        }

        char ch = input[0];
        choice = 0;  // reset each loop

        // Case 1: actual digit '1'–'9'
        if (ch >= '1' && ch <= '9') {
            choice = ch - '0';
        } else {
            // SECRET Case 2: letter mapping (QWE / ASD / ZXC)
            char lower = static_cast<char>(
                std::tolower(static_cast<unsigned char>(ch))
            );

            switch (lower) {
                case 'q': choice = 7; break; // top-left
                case 'w': choice = 8; break; // top-middle
                case 'e': choice = 9; break; // top-right
                case 'a': choice = 4; break; // middle-left
                case 's': choice = 5; break; // center
                case 'd': choice = 6; break; // middle-right
                case 'z': choice = 1; break; // bottom-left
                case 'x': choice = 2; break; // bottom-middle
                case 'c': choice = 3; break; // bottom-right
                default:
                    // Not a recognized key
                    std::cout << "Invalid input. Please use 1-9 or Q/W/E/A/S/D/Z/X/C.\n";
                    continue;
            }
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
