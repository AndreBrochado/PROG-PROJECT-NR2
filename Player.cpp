//
// Created by up201403057 on 17-05-2015.
//

#include "Player.h"

Player::Player(string playerName, std::string boardFilename) {
    name=playerName;
    board=Board(boardFilename);
}

