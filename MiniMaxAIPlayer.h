#ifndef FINALPROJECT_MINIMAXAIPLAYER_H
#define FINALPROJECT_MINIMAXAIPLAYER_H

#include "AIPlayer.h"
#include <string>

class Board;  // forward declaration

class MiniMaxAIPlayer : public AIPlayer {
public:
    explicit MiniMaxAIPlayer(char symbol, const std::string& name = "Minimax AI");

    void makeMove(Board& board) override;

private:
    int miniMaxInternal(Board& board, bool isMaximizing);
    int evaluateBoard(const Board& board) const;
};

#endif // FINALPROJECT_MINIMAXAIPLAYER_H
