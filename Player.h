//
<<<<<<< HEAD
// Created by Ansore on 17-05-2015.
=======
// Created by up201403057 on 17-05-2015.
>>>>>>> 3e0d94d20bccc9960d6fcbda265cc8a14efadaab
//

#ifndef PROGPROJECTNR2_PLAYER_H
#define PROGPROJECTNR2_PLAYER_H

<<<<<<< HEAD
#include "Board.h"
#include <string>

class Player {
public:

    Player(std::string playerName, std::string boardFilename);
=======

class Player {
public:
    Player(string playerName, string boardFilename);
>>>>>>> 3e0d94d20bccc9960d6fcbda265cc8a14efadaab

    void showBoard() const; // shows the player’s board
    Bomb getBomb() const; // asks bomb target coordinates and creates the bomb
    void attackBoard(const Bomb &b); // "receives" a bomb from the opponent;
<<<<<<< HEAD
// updates own board taking into account the damages
// caused by the bomb; BEFORE THAT… moves the ships
private:
    std::string name; // name of the player
    Board* board; // board of the player
=======
    // updates own board taking into account the damages
    // caused by the bomb; BEFORE THAT… moves the ships
private:
    string name; // name of the player
    Board board; // board of the player

>>>>>>> 3e0d94d20bccc9960d6fcbda265cc8a14efadaab
};


#endif //PROGPROJECTNR2_PLAYER_H
<<<<<<< HEAD
=======

>>>>>>> 3e0d94d20bccc9960d6fcbda265cc8a14efadaab
