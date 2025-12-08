//
// Created by lib_laptop on 11/26/2025.
//

#include "AIPlayer.h"
#include "Board.h"
#include <random>

// Constructor
// =====================

AIPlayer::AIPlayer(char symbol, const std::string& name)
    : Player(symbol, name) {
    // Nothing else needed here
}

// Protected helpers
// =====================

bool AIPlayer::tryWinningMove(Board& board) {
    int row = -1;
    int col = -1;

    if (findWinningMove(board, symbol, row, col)) {
        board.applyMove(row, col, symbol);
        return true;
    }
    return false;
}

bool AIPlayer::tryBlockingMove(Board& board) {
    int row = -1;
    int col = -1;
    char opponent = getOpponentSymbol();

    if (findWinningMove(board, opponent, row, col)) {
        board.applyMove(row, col, symbol);  // we play *our* symbol to block
        return true;
    }
    return false;
}

bool AIPlayer::tryTakeCenter(Board& board) {
    // Center is (1,1) on a 3x3 board
    if (board.isValidMove(1, 1)) {
        board.applyMove(1, 1, symbol);
        return true;
    }
    return false;
}

bool AIPlayer::tryTakeCorner(Board& board) {
    // The four corner positions: (0,0), (0,2), (2,0), (2,2)
    const int corners[4][2] = {
        {0, 0},
        {0, 2},
        {2, 0},
        {2, 2}
    };

    for (int i = 0; i < 4; ++i) {
        int r = corners[i][0];
        int c = corners[i][1];

        if (board.isValidMove(r, c)) {
            board.applyMove(r, c, symbol);
            return true;
        }
    }

    return false;  // no available corner
}

bool AIPlayer::tryTakeEdge(Board& board) {
    // The four edge (side) positions: (0,1), (1,0), (1,2), (2,1)
    const int edges[4][2] = {
        {0, 1},
        {1, 0},
        {1, 2},
        {2, 1}
    };

    for (int i = 0; i < 4; ++i) {
        int r = edges[i][0];
        int c = edges[i][1];

        if (board.isValidMove(r, c)) {
            board.applyMove(r, c, symbol);
            return true;
        }
    }

    return false;  // no available edge
}

bool AIPlayer::playRandomMove(Board& board) {
    std::vector<std::pair<int, int>> validMoves;

    // Collect all valid moves
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board.isValidMove(r, c)) {
                validMoves.emplace_back(r, c);
            }
        }
    }

    // Safety: if somehow there are no valid moves, just return.
    // In normal game flow, this shouldn't happen because tie/win is checked before calling makeMove.
    if (validMoves.empty()) {
        return false;
    }

    // Randomly select one of the valid moves.
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0,
        static_cast<int>(validMoves.size()) - 1);

    // Apply said move.
    const auto& choice = validMoves[dist(rng)];
    int row = choice.first;
    int col = choice.second;

    board.applyMove(row, col, symbol);
    return true;
}

char AIPlayer::getOpponentSymbol() const {
    if (symbol == 'X') {
        return 'O';
    } else if (symbol == 'O') {
        return 'X';
    }
    // Fallback; in TicTacToe we should only ever have 'X' or 'O'
    return 'O';
}

bool AIPlayer::wouldWinIfPlayed(Board& board, int row, int col, char s) const {
    // If we can't play there, it can't be a winning move
    if (!board.isValidMove(row, col)) {return false;}

    else {
        // Copy the board and try the move
        Board temp = board;
        temp.applyMove(row, col, s);

        // Check if that hypothetical move wins
        return temp.winCheck(s);
    }
}

// Private helper
// =====================

bool AIPlayer::findWinningMove(Board& board, char testSymbol, int& outRow, int& outCol) const {
    // Try every empty cell and see if placing testSymbol there
    // would create a 3-in-a-row for testSymbol.
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {

            // We can only play on valid (empty) cells
            if (!board.isValidMove(r, c)) {
                continue;
            }

            bool win = false;

            // --- Check row r ---
            {
                bool rowWin = true;
                for (int cc = 0; cc < 3; ++cc) {
                    char value = (cc == c)
                                 ? testSymbol
                                 : board.getCellValue(r, cc);

                    if (value != testSymbol) {
                        rowWin = false;
                        break;
                    }
                }
                if (rowWin) {
                    win = true;
                }
            }

            // --- Check column c ---
            if (!win) {
                bool colWin = true;
                for (int rr = 0; rr < 3; ++rr) {
                    char value = (rr == r)
                                 ? testSymbol
                                 : board.getCellValue(rr, c);

                    if (value != testSymbol) {
                        colWin = false;
                        break;
                    }
                }
                if (colWin) {
                    win = true;
                }
            }

            // --- Check main diagonal (0,0)-(1,1)-(2,2) ---
            if (!win && r == c) {
                bool diagWin = true;
                for (int i = 0; i < 3; ++i) {
                    char value = (r == i && c == i)
                                 ? testSymbol
                                 : board.getCellValue(i, i);

                    if (value != testSymbol) {
                        diagWin = false;
                        break;
                    }
                }
                if (diagWin) {
                    win = true;
                }
            }

            // --- Check anti-diagonal (0,2)-(1,1)-(2,0) ---
            if (!win && (r + c == 2)) {
                bool diagWin = true;
                for (int i = 0; i < 3; ++i) {
                    int rr = i;
                    int cc = 2 - i;
                    char value = (r == rr && c == cc)
                                 ? testSymbol
                                 : board.getCellValue(rr, cc);

                    if (value != testSymbol) {
                        diagWin = false;
                        break;
                    }
                }
                if (diagWin) {
                    win = true;
                }
            }

            if (win) {
                outRow = r;
                outCol = c;
                return true;
            }
        }
    }

    // No winning move found for testSymbol
    return false;
}