//
// Created by lib_laptop on 11/26/2025.
//

#include "MiniMaxAIPlayer.h"
#include "Board.h"
#include <iostream>

#include "MiniMaxAIPlayer.h"
#include "Board.h"
#include <limits>
#include <iostream>

MiniMaxAIPlayer::MiniMaxAIPlayer(char symbol, const std::string& name)
    : AIPlayer(symbol, name) {}

void MiniMaxAIPlayer::makeMove(Board& board) {
    int bestScore = std::numeric_limits<int>::min();
    int bestRow = -1;
    int bestCol = -1;

    // Try every possible move
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (!board.isValidMove(r, c)) {
                continue;
            }

            Board temp = board;
            temp.applyMove(r, c, symbol);

            // After we move, opponent tries to minimize our score
            int score = miniMaxInternal(temp, false);

            if (score > bestScore) {
                bestScore = score;
                bestRow = r;
                bestCol = c;
            }
        }
    }

    // Failsafe (shouldn't happen)
    if (bestRow == -1 || bestCol == -1) {
        playRandomMove(board);
        return;
    }

    board.applyMove(bestRow, bestCol, symbol);
}

int MiniMaxAIPlayer::miniMaxInternal(Board& board, bool isMaximizing) {
    int eval = evaluateBoard(board);

    // Terminal states
    if (eval == 10) {
        // Prefer earlier wins
        return 10 - board.filledCells;
    }
    if (eval == -10) {
        // Prefer later losses
        return -10 + board.filledCells;
    }
    if (board.tieCheck()) {
        return 0;
    }

    char opp = getOpponentSymbol();

    if (isMaximizing) {
        int best = std::numeric_limits<int>::min();

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (!board.isValidMove(r, c)) {
                    continue;
                }

                Board temp = board;
                temp.applyMove(r, c, symbol);

                int score = miniMaxInternal(temp, false);
                if (score > best) {
                    best = score;
                }
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();

        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (!board.isValidMove(r, c)) {
                    continue;
                }

                Board temp = board;
                temp.applyMove(r, c, opp);

                int score = miniMaxInternal(temp, true);
                if (score < best) {
                    best = score;
                }
            }
        }
        return best;
    }
}

int MiniMaxAIPlayer::evaluateBoard(const Board& board) const {
    char me = symbol;
    char opp = getOpponentSymbol();

    if (board.winCheck(me)) {
        return 10;
    }
    if (board.winCheck(opp)) {
        return -10;
    }
    return 0;
}