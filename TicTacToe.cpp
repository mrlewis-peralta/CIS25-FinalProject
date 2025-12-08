//
// Created by lib_laptop on 11/26/2025.
//

#include "TicTacToe.h"
#include <iostream>
#include <limits>

// Constructor
TicTacToe::TicTacToe() : board(), player1(nullptr), player2(nullptr), currentPlayer(nullptr) {}
// Can add additional constructors to allow stuff like custom symbols

// Main program loop: show menu, play games, or quit
void TicTacToe::run() {
    bool running = true;

    while (running) {
        showMainMenu();

        int choice;
        std::cin >> choice;

        if (!std::cin) {
            // Basic input recovery (optional but nice)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            choosePlayers();
            playSingleGame();
            cleanupPlayers();   // delete players between games
        } else if (choice == 2) {
            std::cout << "Exiting TicTacToe. Goodbye!\n";
            running = false;
        } else {
            std::cout << "Invalid choice. Please select 1 or 2.\n";
        }
    }
}

// Prints the main menu (Play or Quit)
void TicTacToe::showMainMenu() const {
    std::cout << "\n=== TicTacToe ===\n";
    std::cout << "1. Play\n";
    std::cout << "2. Quit\n";
    std::cout << "Choice: ";
}

// Allows user to choose types for player1 (X) and player2 (O)
// Now supports Human, Regular AI, and Unbeatable AI.
// Minimax AI (4) is still not implemented.
void TicTacToe::choosePlayers() {
    // Just in case we are replaying a game
    cleanupPlayers();

    int type1 = 0;
    int type2 = 0;

    // --- Player 1 (X) ---
    while (true) {
        std::cout << "\nSelect type for Player 1 (X):\n"
                  << "  1. Human\n"
                  << "  2. Regular AI\n"
                  << "  3. Unbeatable AI\n"
                  << "  4. Minimax AI\n"
                  << "Choice: ";

        std::cin >> type1;

        if (!std::cin) {
            // handle inputs like 'a'
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number 1-4.\n";
            continue;
        }

        if (type1 >= 1 && type1 <= 4) {break;} // valid choice
        else {std::cout << "Invalid type. Please choose 1-4.\n";}
    }

    // --- Player 2 (O) ---
    while (true) {
        std::cout << "\nSelect type for Player 2 (O):\n"
                  << "  1. Human\n"
                  << "  2. Regular AI\n"
                  << "  3. Unbeatable AI\n"
                  << "  4. Minimax AI\n"
                  << "Choice: ";

        std::cin >> type2;

        if (!std::cin) {
            // handle inputs like 'a'
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number 1-4.\n";
            continue;
        }

        if (type2 >= 1 && type2 <= 4) {break;} // valid choice
        else {std::cout << "Invalid type. Please choose 1-4.\n";}
    }

    // Now actually create the players
    player1 = createPlayer(type1, 'X');
    player2 = createPlayer(type2, 'O');
    currentPlayer = player1;

    std::cout << "\nPlayers set up. Let the game begin!\n\n";
}


// Runs one full game until win or tie
void TicTacToe::playSingleGame() {
    resetBoard();
    currentPlayer = player1;
    char winner = '\0';

    bool gameOver = false;

    while (!gameOver) {
        board.display();

        std::cout << currentPlayer->getName()
                  << " (" << currentPlayer->getSymbol()
                  << ") - it's your move.\n";

        currentPlayer->makeMove(board);

        char symbol = currentPlayer->getSymbol();

        if (board.winCheck(symbol)) {
            winner = symbol;
            gameOver = true;
        } else if (board.tieCheck()) {
            gameOver = true;
        } else {
            switchPlayer();
        }
    }

    // Show final board and announce result
    board.display();
    announceResult(winner);
}

// Creates a player of a chosen type (1 = Human, 2 = Regular AI, 3 = Unbeatable, 4 = Minimax)
// For now, Minimax is not supported; we default to Human in that case.
Player* TicTacToe::createPlayer(int type, char symbol) {
    std::string baseName = (symbol == 'X') ? "Player 1" : "Player 2";

    switch (type) {
        case 1:
            // Human player
            return new HumanPlayer(symbol, baseName + " (Human)");

        case 2:
            // Regular AI
            return new RegularAIPlayer(symbol);

        case 3:
            // Unbeatable AI
            return new UnbeatableAIPlayer(symbol);

        case 4:
            return new MiniMaxAIPlayer(symbol);

        default:
            // Should not happen with our validation, but just in case:
            std::cout << "Invalid or unsupported player type. Defaulting to Human.\n";
            return new HumanPlayer(symbol, baseName + " (Human)");
    }
}

// Clears the board and resets game state
void TicTacToe::resetBoard() {
    board = Board(); // Rely on Board's constructor to clear grid & filledCells
    currentPlayer = player1;
}

// Switches current player between player1 and player2
void TicTacToe::switchPlayer() {
    if (currentPlayer == player1) {
        currentPlayer = player2;
    } else {
        currentPlayer = player1;
    }
}

// Announces winner or tie
void TicTacToe::announceResult(char winner) const {
    if (winner == 'X' || winner == 'O') {
        const Player* winnerPtr =
            (winner == player1->getSymbol()) ? player1 : player2;
        std::cout << winnerPtr->getName()
                  << " (" << winner << ") wins!\n";
    } else {
        std::cout << "It's a tie!\n";
    }
}

// Deletes player1 and player2 (used between games or when quitting)
void TicTacToe::cleanupPlayers() {
    if (player1 != nullptr) {
        delete player1;
        player1 = nullptr;
    }
    if (player2 != nullptr) {
        delete player2;
        player2 = nullptr;
    }
    currentPlayer = nullptr;
}