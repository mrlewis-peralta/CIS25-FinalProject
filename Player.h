//
// Created by lib_laptop on 11/26/2025.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H
#include <string>

class Board;

class Player {
public:
    Player(char symbol, const std::string& name);
    virtual ~Player() = default;
    char getSymbol() const;
    const std::string& getName() const;
    virtual void makeMove(Board& board) = 0;
protected:
    char symbol;
    std::string name;

};

#endif //FINALPROJECT_PLAYER_H