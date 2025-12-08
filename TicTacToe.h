#ifndef FINALPROJECT_TICTACTOE_H
#define FINALPROJECT_TICTACTOE_H

#include <string>

#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "RegularAIPlayer.h"
#include "UnbeatableAIPlayer.h"
#include "MiniMaxAIPlayer.h"

/**
 * TicTacToe class coordinates the entire TicTacToe program.
 *
 * Responsibilities:
 *  - Display a menu and allow players to choose their player types
 *  - Create player1 and player2 (Human, Regular AI, Unbeatable AI, Minimax AI)
 *  - Run a full TicTacToe game (turn switching, board display, win/tie detection)
 *  - Allow the user to replay games without restarting the program
 */
class TicTacToe {
public:
    TicTacToe();

    // Starts the whole program: menu, chooses players, and plays games
    void run();

private:
    Board board;

    Player* player1;   // Always uses symbol 'X'
    Player* player2;   // Always uses symbol 'O'
    Player* currentPlayer;   // Whose turn it is

    // === Main Flow ===

    // Prints the main menu (Play or Quit)
    void showMainMenu() const;

    // Allows user to choose types for player1 and player2
    void choosePlayers();

    // Runs one full game until win or tie
    void playSingleGame();

    // === Player Creation ===

    // Creates a player of a chosen type (1 = Human, 2 = Regular AI, 3 = Unbeatable, 4 = Minimax)
    Player* createPlayer(int type, char symbol);

    // === Helpers ===

    // Clears the board and resets game state
    void resetBoard();

    // Switches current player between player1 and player2
    void switchPlayer();

    // Announces winner or tie
    void announceResult(char winner) const;

    // Deletes player1 and player2 (used between games or when quitting)
    void cleanupPlayers();
};

#endif // FINALPROJECT_TICTACTOE_H