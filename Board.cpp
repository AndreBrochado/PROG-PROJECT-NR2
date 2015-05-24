//
// Created by Ansore on 10-05-2015.
//

#include "Board.h"
#include <fstream>
#include <iomanip>
#include <math.h>

Board::Board() {
	numColumns = numLines = 0;
}

Board::Board(const std::string &filename) {
    std::ifstream inputFile;
    char dummy;
    char symbol, line, column, orientation;
    Position<char> tempPosition;
    unsigned int size, color;
    inputFile.open(filename);
	inputFile>>numLines>>dummy>>numColumns;

    while(!inputFile.eof()) {
        inputFile >> symbol >> size >> line >> column
        >> orientation >> color;
        tempPosition.line = line;
        tempPosition.column = column;
        ships.push_back(Ship(symbol, tempPosition, orientation, size, color));
    }
    inputFile.close();
    std::vector <std::vector <int> > table(this->numLines, std::vector<int>(this->numColumns, -1));

    for(size_t i=0; i<ships.size(); i++){
    	for(size_t j = 0; j<ships[i].getSize(); j++){
        if(ships[i].getOrientation()== 'V')
        	table[ships[i].getPosition().line+j][ships[i].getPosition().column] = i;
        else
        	table[ships[i].getPosition().line][ships[i].getPosition().column+j] = i;
        }
    }
	board = table;
}

bool Board::isValidPosition(const Ship ship) {
	if (ship.getPosition().column > numColumns || ship.getPosition().line > numLines)
		return false;
	if (!(ship.getOrientation() == 'V' || ship.getOrientation() == 'H'))
		return false;
	if (ship.getOrientation() == 'V') {
		if (ship.getPosition().line + ship.getSize() > numLines)
			return false;
		else {
			for (size_t i = 0; i < ship.getSize(); i++) {
				if (board[ship.getPosition().line+i][ship.getPosition().column] != -1)
					return false;
			}
		}
	}
	if (ship.getOrientation() == 'H') {
		if (ship.getPosition().column + ship.getSize() > numColumns)
			return false;
		else {
			for (size_t i = 0; i < ship.getSize(); i++) {
				if (board[ship.getPosition().line][ship.getPosition().column+i] != -1)
					return false;
			}
		}
	};
	return true;
}

bool Board::putShip(const Ship &ship, unsigned int index){ // fix
	if(isValidPosition(ship)){
		ships.push_back(ship);
		if (ship.getOrientation() == 'V')
			for (int i = ship.getPosition().line; i < ship.getPosition().line + ship.getSize(); i++) {
				board[i][ship.getPosition().column] = index; //index of the recently added ship
			}
		else
			for (int i = ship.getPosition().column; i < ship.getPosition().column + ship.getSize(); i++) {
				board[ship.getPosition().line][i] = index; //index of the recently added ship
			}
		return true;
	}
	else
		return false;
}

Ship Board::removeShip(size_t index) { //fix
	for(size_t j = 0; j<ships[index].getSize(); j++){ //for(size_t j = 0; index<ships[index].getSize(); j++){
		if(ships[index].getOrientation()== 'V')
			board[ships[index].getPosition().line+j][ships[index].getPosition().column] = -1;
		else
			board[ships[index].getPosition().line][ships[index].getPosition().column+j] = -1;
	}
		Ship removedShip = ships[index];
		ships.erase(ships.begin()+index);
	return removedShip;
}

void Board::moveShips(){ //fix
	for(size_t i = 0; i< ships.size(); i++){
		Ship originalShip = removeShip(0);
		Ship testShip = originalShip;
		testShip.moveRand(0, 0, numLines-1, numColumns-1);
		if(!putShip(testShip, i))
			putShip(originalShip, i);
	}
}

void Board::display() const {
	std::cout << " ";
	setColor(15, 0);
	for (size_t k = 0; k < numLines	; k++) {
		std::cout << std::setw(2) << char('a' + k);
	}
	std::cout << std::endl;

	for (size_t i = 0; i < numLines; i++) {
		for (size_t j = 0; j < numColumns; j++) {
			if (j == 0) {
				setColor(15, 0);
				std::cout << char('A' + i);
			}
			if (board[i][j] == -1) {
				setColor(9, 7);
				std::cout << std::setw(2) << '.';
			}
			else {
				setColor(ships[board[i][j]].getColor(), 7);
				std::cout << std::setw(2) << ships[board[i][j]].getStatus()[getShipPart(ships[board[i][j]], i, j)];
			}
		}
		std::cout << std::endl;
	}
	setColor(15, 0);
}

void Board::show() const {
	std::cout<<"Board size: "<<numLines<<"x"<<numColumns<<" (LxC)"<<std::endl; //TO BE CONTINUED
	}

bool Board::attack(const Bomb &bomb) {
	if (bomb.getTargetLineInt() > numLines - 1 || bomb.getTargetColumnInt() > numColumns - 1)
		return false;
	else if (board[bomb.getTargetLineInt()][bomb.getTargetColumnInt()] != -1) {
		Ship* hitShip = &ships[board[bomb.getTargetLineInt()][bomb.getTargetColumnInt()]];
		std::cout<<"You hit on: "<<bomb.getTargetPosition().line<<bomb.getTargetPosition().column<<std::endl;
		return hitShip->attack(getShipPart(*hitShip, bomb.getTargetLineInt(), bomb.getTargetColumnInt()));
	}
		std::cout<<"You failed, your bomb hit: "<<bomb.getTargetPosition().line<<bomb.getTargetPosition().column<<std::endl; //DEBUG
		return false;
}

unsigned int Board::getShipPart(Ship ship, int line, int column) const {
	int xDif, yDif;
	yDif=line-ship.getPosition().line;
	xDif=column-ship.getPosition().column; //One of the differences will always be 0 (as the bomb hits the ship, only one coordinate will change from the original position)
	return (unsigned int) (sqrt(xDif*xDif+yDif*yDif)); // so the distance will always be equal to the coordinate that is different from 0
}

unsigned int Board::getNumLines() const {
	return numLines;
}

unsigned int Board::getNumColumns() const {
	return numColumns;
}

std::vector<Ship> Board::getShipList() const{
	return ships;
}

std::vector<std::vector<int>> Board::getBoard() {
	return board;
}

std::ostream& operator<<(std::ostream& outputStream, const Board& board){
	outputStream << " ";
	setColor(15, 0);
	for (size_t k = 0; k < board.numLines	; k++) {
		outputStream << std::setw(2) << char ('a' + k);
	}
	outputStream << std::endl;

	for (size_t i = 0; i < board.numLines; i++) {
		for (size_t j = 0; j < board.numColumns; j++) {
			if (j == 0) {
				setColor(15, 0);
				outputStream << char ('A' + i);
			}
			if (board.board[i][j] == -1) {
				setColor(9, 7);
				outputStream << std::setw(2) << '.';
			}
			else {
				setColor(board.ships[board.board[i][j]].getColor(), 7);
				outputStream << std::setw(2) << board.ships[board.board[i][j]].getStatus()[board.getShipPart(board.ships[board.board[i][j]], i, j)];
			}
		}
		outputStream << std::endl;
	}
	setColor(15, 0);
	return outputStream;
}
