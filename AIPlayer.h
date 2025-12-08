//
// Created by lib_laptop on 11/26/2025.
//

#ifndef FINALPROJECT_AIPLAYER_H
#define FINALPROJECT_AIPLAYER_H

#include "Player.h"
#include <vector>
#include <utility>

// Forward declaration to avoid circular includes
class Board;

/**
 * AIPlayer is an abstract base class for all computer-controlled players.
 *
 * It provides shared helper functions that child AI classes (RegularAIPlayer,
 * UnbeatableAIPlayer, MiniMaxAIPlayer) can use to implement their strategies.
 */
class AIPlayer : public Player {
public:
    AIPlayer(char symbol, const std::string& name);
    virtual ~AIPlayer() = default;

protected:
    // === Shared AI helper functions ===

    // Try to find and play a winning move for this AI's symbol.
    // Returns true if it found and applied a winning move.
    bool tryWinningMove(Board& board);

    // Try to find and block the opponent's winning move.
    // Returns true if it found and applied a blocking move.
    bool tryBlockingMove(Board& board);

    // Try to take the center square (1,1). Returns true if a move was made.
    bool tryTakeCenter(Board& board);
    bool tryTakeCorner(Board& board);
    bool tryTakeEdge(Board& board);

    // Play a random valid move. Returns true if it played a move,
    // False only if there were no valid moves (should never happen).
    bool playRandomMove(Board& board);

    bool wouldWinIfPlayed(Board& board, int row, int col, char testSymbol) const;

    // Convenience: get the opponent's symbol ('X' <-> 'O')
    char getOpponentSymbol() const;

private:
    // Helper used internally by tryWinningMove / tryBlockingMove:
    // looks for a move that would make three-in-a-row for testSymbol.
    // If found, writes the row/col into outRow/outCol and returns true.
    bool findWinningMove(Board& board, char testSymbol, int& outRow, int& outCol) const;
};

#endif //FINALPROJECT_AIPLAYER_H