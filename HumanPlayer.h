//
// Created by lib_laptop on 11/26/2025.
//

#ifndef FINALPROJECT_HUMANPLAYER_H
#define FINALPROJECT_HUMANPLAYER_H

#include "Player.h"
#include "Board.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(char symbol, const std::string& name);
    void makeMove(Board& board) override;
};


#endif //FINALPROJECT_HUMANPLAYER_H