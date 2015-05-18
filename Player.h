//
// Created by Ansore on 17-05-2015.
// Created by up201403057 on 17-05-2015.
//

#ifndef PROGPROJECTNR2_PLAYER_H
#define PROGPROJECTNR2_PLAYER_H

#include "Board.h"
#include <string>

class Player {
public:

    Player(std::string playerName, std::string boardFilename);
    void showBoard() const; // shows the player’s board
    Bomb getBomb() const; // asks bomb target coordinates and creates the bomb
    void attackBoard(const Bomb &b); // "receives" a bomb from the opponent;
// updates own board taking into account the damages
// caused by the bomb; BEFORE THAT… moves the ships
private:
    std::string name; // name of the player
    Board* board; // board of the player
    // updates own board taking into account the damages
    // caused by the bomb; BEFORE THAT… moves the ships
};


#endif //PROGPROJECTNR2_PLAYER_H