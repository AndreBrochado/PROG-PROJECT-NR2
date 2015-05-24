//
// Created by Ansore on 17-05-2015.
// Created by up201403057 on 17-05-2015.
//

#include "Player.h"

Player::Player(std::string &playerName, std::string &boardFilename) {
    board = Board(boardFilename);
    name = playerName;
    boardArea = board.getNumLines() * board.getNumColumns();
    shipArea = 0;
    for(size_t i = 0; i<board.getShipList().size(); i++){
        shipArea += board.getShipList()[i].getSize();
    }
    playTime = 0;
}

void Player::showBoard() const {
    board.show();
}

Bomb Player::getBomb() const {
    Position<char> targetPosition;
    std::cout << "Insert bomb coordinates(line: A.." << char ('A' + board.getNumLines() - 1) << " column: a.." <<
    char ('a' + board.getNumColumns() - 1)<<", i.e: Aa)";
    std::cin>>targetPosition.line>>targetPosition.column;
    //check for errors
    return Bomb(targetPosition);
}

void Player::attackBoard(const Bomb &bomb) {
  //  board.moveShips();
    if (board.attack(bomb)) {
        int hitShipIndex = board.getBoard()[bomb.getTargetLineInt()][bomb.getTargetColumnInt()];
        if (board.getShipList()[hitShipIndex].isDestroyed()) {
            board.removeShip(
                    (unsigned int) board.getBoard()[board.getShipList()[hitShipIndex].getPosition().line][board.getShipList()[hitShipIndex].getPosition().column]);
            board.refreshBoard();
        }
    }
}

bool Player::wonGame(Player& opponent) {
    return opponent.board.getShipList().size()==0;
}

std::string Player::getName() const {
    return name;
}

Board Player::getBoard() const {
	return board;
}

int Player::getShipArea() const {
    return shipArea;
}

int Player::getBoardArea() const {
    return boardArea;
}

Player::Player() {

}

time_t Player::getPlayTime() const {
    return playTime;
}

void Player::incPlayTime(time_t increment) {
    playTime = playTime + increment;
}
