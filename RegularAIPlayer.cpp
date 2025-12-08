//
// Created by lib_laptop on 11/26/2025.
//

#include "RegularAIPlayer.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <utility>
#include <random>

RegularAIPlayer::RegularAIPlayer(char symbol) : AIPlayer(symbol, "Regular AI") {}

void RegularAIPlayer::makeMove(Board& board) {
    // Priority:
    //  1) Play a winning move if available
    //  2) Block opponent's immediate win
    //  3) Take center if available
    //  4) Otherwise, play a random valid move

    if (tryWinningMove(board)) {return;}
    else if (tryBlockingMove(board)) {return;}
    else if (tryTakeCenter(board)) {return;}
    else {playRandomMove(board); return;}
}