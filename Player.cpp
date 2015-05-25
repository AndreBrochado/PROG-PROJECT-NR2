//
// Created by Ansore on 17-05-2015.
// Created by up201403057 on 17-05-2015.
//

#include "Player.h"

Player::Player() {

}

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

bool Player::getCoordinates (std::string &inputString, int numLines, int numColumns)const {
    std::string testString;
    getline(std::cin, testString);
    std::cout << std::endl;
    if (std::cin.fail()) {
        if (!std::cin.eof())
            std::cin.ignore(1000, '\n');
        std::cin.clear();
        return false;
    }
    else if(testString.size() != 2)
        return false;
    else{
        if(testString[0]<'A' || testString[0]>(char) ('A' + numLines) || testString[1]<'a' || testString[1]>(char) ('a'+numColumns))
            return false;
    }
    inputString = testString;
    return true;
}

Bomb Player::getBomb() const {
    Position<char> targetPosition;
    std::string lineGetter;
    bool result = false;
    do{
        std::cout << "Insert bomb coordinates(line: A.." << char ('A' + board.getNumLines() - 1) << " column: a.." <<
        char ('a' + board.getNumColumns() - 1)<<", i.e: Aa)";
        result = getCoordinates(lineGetter, board.getNumLines(), board.getNumColumns());
        if(!result)
            std::cout<< "Invalid coordinates/input ! Please insert a valid position!"<<std::endl;
    }while(!result);
    targetPosition.line=lineGetter[0];
    targetPosition.column=lineGetter[1];
    return Bomb(targetPosition);
}

void Player::attackBoard(const Bomb &bomb) {
    board.moveShips();
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

time_t Player::getPlayTime() const {
    return playTime;
}

void Player::incPlayTime(time_t increment) {
    playTime = playTime + increment;
}
