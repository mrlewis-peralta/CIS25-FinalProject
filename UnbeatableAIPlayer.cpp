// UnbeatableAIPlayer.cpp
//
// Unbeatable Tic-Tac-Toe AI using the 8-step perfect-play strategy:
//
// 1) Win immediately if possible
// 2) Block opponent's immediate win
// 3) SPECIAL CASE: if we have center and opponent has opposite corners,
//      we must take an EDGE (not a corner)
// 4) Create a fork
// 5) Block opponent's fork
// 6) Take center
// 7) Take opposite corner
// 8) Take any empty corner
// 9) Take any empty side
//
// This version also prints which rule it used each time it moves,
// so we can see why it chooses particular moves in tests.

#include "UnbeatableAIPlayer.h"
#include "Board.h"
#include <iostream>  // for debug output

UnbeatableAIPlayer::UnbeatableAIPlayer(char symbol)
    : AIPlayer(symbol, "Unbeatable AI") {}

// ----------------- Public makeMove (strategy) -----------------

void UnbeatableAIPlayer::makeMove(Board& board) {
    char me  = symbol;
    char opp = opponentSymbol();

    int r = -1;
    int c = -1;

    // std::cout << "\n[Unbeatable AI (" << me << ")] --- deciding move ---\n";

    // 1) Win immediately if possible (parent helper applies the move)
    if (tryWinningMove(board)) {
        // std::cout << "[Unbeatable AI] Rule 1: winning move.\n";
        return;
    }

    // 2) Block opponent's immediate win
    if (tryBlockingMove(board)) {
        // std::cout << "[Unbeatable AI] Rule 2: block opponent's winning move.\n";
        return;
    }

    // 3) SPECIAL CASE:
    // If we have the center AND the opponent has opposite corners,
    // we MUST play an EDGE, not a corner.
    //
    // Pattern (before our move):
    //   - We (me) occupy (1,1)
    //   - Opponent occupies (0,0) and (2,2), OR (0,2) and (2,0)
    //
    // Correct response: choose any available edge:
    //   (0,1), (1,0), (1,2), (2,1)
    //
    if (board.getCellValue(1, 1) == me &&
        (
            (board.getCellValue(0, 0) == opp && board.getCellValue(2, 2) == opp) ||
            (board.getCellValue(0, 2) == opp && board.getCellValue(2, 0) == opp)
        )
    ) {
        // std::cout << "[Unbeatable AI] Rule 3 (special): center + opponent opposite corners -> take edge.\n";

        const int edges[4][2] = {
            {0, 1}, // top edge
            {1, 0}, // left edge
            {1, 2}, // right edge
            {2, 1}  // bottom edge
        };

        for (const auto& e : edges) {
            int er = e[0];
            int ec = e[1];
            if (board.isValidMove(er, ec)) {
                // std::cout << "[Unbeatable AI] Rule 3 (special): choosing edge (" << er << ", " << ec << ").\n";
                board.applyMove(er, ec, me);
                return;
            }
        }
        // std::cout << "[Unbeatable AI] Rule 3 (special): no edges available, falling through.\n";
        // If somehow no edges are free, fall through to general logic.
    }

    // 4) Create a fork (a move that gives us 2+ winning moves next turn)
    if (findForkMove(board, me, r, c)) {
        // std::cout << "[Unbeatable AI] Rule 4: create fork at (" << r << ", " << c << ").\n";
        board.applyMove(r, c, me);
        return;
    }

    // 5) Block opponent's fork
    if (blockOpponentFork(board, me, opp, r, c)) {
        // std::cout << "[Unbeatable AI] Rule 5: block opponent's fork at (" << r << ", " << c << ").\n";
        board.applyMove(r, c, me);
        return;
    }

    // 6) Take center if free
    if (tryTakeCenter(board)) {
        // std::cout << "[Unbeatable AI] Rule 6: take center.\n";
        return;
    }

    // 7) Take opposite corner
    if (takeOppositeCorner(board, opp, r, c)) {
        // std::cout << "[Unbeatable AI] Rule 7: take opposite corner at (" << r << ", " << c << ").\n";
        board.applyMove(r, c, me);
        return;
    }

    // 8) Take any empty corner (parent helper)
    if (tryTakeCorner(board)) {
        // std::cout << "[Unbeatable AI] Rule 8: take empty corner.\n";
        return;
    }

    // 9) Take any empty side (parent helper)
    if (tryTakeEdge(board)) {
        // std::cout << "[Unbeatable AI] Rule 9: take empty side.\n";
        return;
    }

    // Failsafe: random valid move (parent helper)
    // std::cout << "[Unbeatable AI] Failsafe: play random valid move.\n";
    playRandomMove(board);
}

// ----------------- Private helpers (only what parent DOESN'T have) -----------------

char UnbeatableAIPlayer::opponentSymbol() const {
    return (symbol == 'X') ? 'O' : 'X';
}

// Count how many distinct immediate winning moves `player` has
// on the given board.
int UnbeatableAIPlayer::countImmediateWinningMoves(Board& board,
                                                   char player) const {
    int count = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (!board.isValidMove(r, c)) {
                continue;
            }
            // wouldWinIfPlayed is defined in AIPlayer (protected)
            if (wouldWinIfPlayed(board, r, c, player)) {
                ++count;
            }
        }
    }
    return count;
}

// Is placing `player` at (r,c) a *fork*? (creates >= 2 immediate winning moves)
bool UnbeatableAIPlayer::isForkMove(Board& board,
                                    char player,
                                    int r,
                                    int c) const {
    if (!board.isValidMove(r, c)) {
        return false;
    }

    Board temp = board;           // copy
    temp.applyMove(r, c, player); // pretend player moves here

    int wins = countImmediateWinningMoves(temp, player);
    return wins >= 2;
}

// Step: Find any fork move for `player`
bool UnbeatableAIPlayer::findForkMove(Board& board,
                                      char player,
                                      int& outRow,
                                      int& outCol) const {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (isForkMove(board, player, r, c)) {
                outRow = r;
                outCol = c;
                return true;
            }
        }
    }
    return false;
}

// Step: Block opponent's fork (general logic)
bool UnbeatableAIPlayer::blockOpponentFork(Board& board,
                                           char me,
                                           char opp,
                                           int& outRow,
                                           int& outCol) const {
    bool opponentHasFork = false;

    // First, see if there is *any* fork available to the opponent
    for (int r = 0; r < 3 && !opponentHasFork; ++r) {
        for (int c = 0; c < 3 && !opponentHasFork; ++c) {
            if (isForkMove(board, opp, r, c)) {
                opponentHasFork = true;
            }
        }
    }

    if (!opponentHasFork) {
        return false;  // nothing to block
    }

    // Try moves for us that leave opponent with NO fork
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (!board.isValidMove(r, c)) {
                continue;
            }

            Board temp = board;
            temp.applyMove(r, c, me);

            bool oppCanForkAfter = false;
            for (int rr = 0; rr < 3 && !oppCanForkAfter; ++rr) {
                for (int cc = 0; cc < 3 && !oppCanForkAfter; ++cc) {
                    if (isForkMove(temp, opp, rr, cc)) {
                        oppCanForkAfter = true;
                    }
                }
            }

            if (!oppCanForkAfter) {
                outRow = r;
                outCol = c;
                return true;
            }
        }
    }

    // Fallback: directly occupy one of the fork squares
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (isForkMove(board, opp, r, c)) {
                if (board.isValidMove(r, c)) {
                    outRow = r;
                    outCol = c;
                    return true;
                }
            }
        }
    }

    return false;
}

// Step: Opposite corner
bool UnbeatableAIPlayer::takeOppositeCorner(Board& board,
                                            char opp,
                                            int& outRow,
                                            int& outCol) const {
    struct CornerPair {
        int r1, c1;
        int r2, c2;
    };

    CornerPair pairs[] = {
        {0, 0, 2, 2},
        {2, 2, 0, 0},
        {0, 2, 2, 0},
        {2, 0, 0, 2}
    };

    for (const auto& p : pairs) {
        if (board.getCellValue(p.r1, p.c1) == opp &&
            board.isValidMove(p.r2, p.c2)) {
            outRow = p.r2;
            outCol = p.c2;
            return true;
        }
    }

    return false;
}
