//
// Created by lib_laptop on 11/26/2025.
//

#ifndef FINALPROJECT_UNBEATABLEAIPLAYER_H
#define FINALPROJECT_UNBEATABLEAIPLAYER_H

#include "AIPlayer.h"

class Board;

/**
 * UnbeatableAIPlayer:
 *  - Uses the classic 8-step perfect Tic-Tac-Toe strategy:
 *    1) Win
 *    2) Block
 *    3) Fork
 *    4) Block opponent's fork
 *    5) Take center
 *    6) Take opposite corner
 *    7) Take empty corner
 *    8) Take empty side
 */
class UnbeatableAIPlayer final : public AIPlayer {
public:
    explicit UnbeatableAIPlayer(char symbol);

    // Main decision function: applies the best move to the board.
    void makeMove(Board& board) override;

private:
    // Helper: return opponent symbol ('X' -> 'O', 'O' -> 'X')
    char opponentSymbol() const;

    // Count how many distinct immediate winning moves `player` has
    // on the given board.
    int countImmediateWinningMoves(Board& board, char player) const;

    // True if placing `player` at (row, col) creates a fork
    // (i.e., at least 2 immediate winning moves next turn).
    bool isForkMove(Board& board,
                    char player,
                    int row,
                    int col) const;

    // Step 3: find a fork move for `player`.
    bool findForkMove(Board& board,
                      char player,
                      int& outRow,
                      int& outCol) const;

    // Step 4: block opponent's fork according to the description:
    //  - If there is exactly one fork square, occupy it.
    //  - Otherwise, try to play a move that both:
    //       (a) creates an immediate threat (two-in-a-row),
    //       (b) leaves the opponent with no fork.
    //  - If that fails, fall back to occupying one of the fork squares.
    bool blockOpponentFork(Board& board,
                           char me,
                           char opp,
                           int& outRow,
                           int& outCol) const;

    // Step 6: take the corner opposite an opponent's corner, if available.
    bool takeOppositeCorner(Board& board,
                            char opp,
                            int& outRow,
                            int& outCol) const;
};

#endif // FINALPROJECT_UNBEATABLEAIPLAYER_H