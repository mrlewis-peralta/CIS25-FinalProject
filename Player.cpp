//
// Created by lib_laptop on 11/26/2025.
//

#include "Player.h"

Player::Player(char symbol, const std::string& name) : symbol(symbol), name(name) {}

char Player::getSymbol() const {return symbol;}

const std::string& Player::getName() const {return name;}