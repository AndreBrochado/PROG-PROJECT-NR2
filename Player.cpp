//
// Created by Ansore on 17-05-2015.
//

#include "Player.h"

Player::Player(std::string playerName, std::string boardFilename) {
    board->Board(boardFilename);
    name = playerName;
}
