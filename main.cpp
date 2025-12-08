#include <iostream>
#include "TicTacToe.h"

/**
 * Entry point for the TicTacToe program.
 * For this stage of the project, we just construct a TicTacToe object
 * and call run(), which will eventually handle the main menu and game loop.
 */
int main() {
    std::cout << "=== TicTacToe AI ===" << std::endl;

    TicTacToe game;
    game.run();  // Will coordinate menu, player selection, and gameplay

    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}