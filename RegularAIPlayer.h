//
// Created by lib_laptop on 11/26/2025.
//

#ifndef FINALPROJECT_REGULARAIPLAYER_H
#define FINALPROJECT_REGULARAIPLAYER_H

#include "AIPlayer.h"

class Board;

class RegularAIPlayer final : public AIPlayer {
public:
    explicit RegularAIPlayer(char symbol);
    void makeMove(Board& board) override;
};


#endif //FINALPROJECT_REGULARAIPLAYER_H