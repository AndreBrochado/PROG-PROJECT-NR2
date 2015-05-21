//
// Created by Ansore on 17-05-2015.
// Created by up201403057 on 17-05-2015.
//

#include "Player.h"

Player::Player(std::string playerName, std::string boardFilename) {
    board = Board(boardFilename);
    name = playerName;
}

void Player::showBoard() const {
    board.show();
}

Bomb Player::getBomb() const {
    PositionChar targetPosition;
    std::cout << "Insert bomb coordinates(line: A.." << (char) 'A' + board.getNumLines() - 1 << " column: a.." <<
    (char) 'a' + board.getNumColumns() - 1<<", i.e: Aa)";
    std::cin>>targetPosition.line>>targetPosition.column;
    //check for errors
    return Bomb(targetPosition);
}

void Player::attackBoard(const Bomb &bomb) {
    board.moveShips();
    board.attack(bomb);
}

std::string Player::getName() const {
    return name;
}

Board Player::getBoard() const {
	return board;
}