//
// Created by Ansore on 10-05-2015.
//

#include <stdlib.h>
#include "Ship.h"

Ship::Ship(char symbol, Position<char> position, char orientation, unsigned int size, unsigned int color) {
	this->symbol = symbol;
	this->position.line = (unsigned int) (position.line - 'A');
	this->position.column = (unsigned int) (position.column - 'a');
	this->orientation = orientation;
	this->size = size;
	this->color = color;
	status = std::string(size, symbol);
}

bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax,
		unsigned int columnMax) {
	Position<int> newPosition;
	newPosition.line = position.line;
	newPosition.column = position.column;
	switch (direction) {
	case 'N':
		newPosition.line--;
		break;
	case 'S':
		newPosition.line++;
		break;
	case 'W':
		newPosition.column--;
		break;
	case 'E':
		newPosition.column++;
		break;
	default:
		break;
	}

	if ((orientation == 'V' && !rotate) || (orientation == 'H' && rotate)){
		if (newPosition.line + size-1 <= lineMax && newPosition.line >= lineMin && newPosition.column <= columnMax
				&& newPosition.column >= columnMin) {
			position.line = newPosition.line;
			position.column = newPosition.column;
			orientation = 'V';
			return true;
		}
	}
	else
		if ((orientation == 'H' && !rotate) || (orientation == 'V' && rotate))
			if (newPosition.line >= lineMin && newPosition.line <= lineMax && newPosition.column + size-1 <= columnMax
				&& newPosition.column >= columnMin) {
			position.line = newPosition.line;
			position.column = newPosition.column;
			orientation = 'H';
			return true;
		}

	return false;


}

bool Ship::moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax) {
	bool rotate;
	if (rand() % 2 == 0)
		rotate = true;
	else
		rotate = false;
	switch (rand() % 5) {
	case 0:
		return move('0', rotate, lineMin, columnMin, lineMax, columnMax);
	case 1:
		return move('N', rotate, lineMin, columnMin, lineMax, columnMax);
	case 2:
		return move('S', rotate, lineMin, columnMin, lineMax, columnMax);
	case 3:
		return move('W', rotate, lineMin, columnMin, lineMax, columnMax);
	case 4:
		return move('E', rotate, lineMin, columnMin, lineMax, columnMax);
	default:
		return false;
	}
}

bool Ship::attack(size_t partNumber) {
	if (partNumber > size - 1)
		return false;
	else {
		status[partNumber] = char (tolower(status[partNumber]));
		return true;
	}
}

bool Ship::isDestroyed() const {
	unsigned int lower=0, upper=0;
	for(size_t i=0; i<status.size(); i++){
		if(islower(status[i]))
			lower++;
		else
			upper++;
	}
	return lower>=upper;
}

void Ship::show() const{
	std::cout<<"Boat Symbol: "<<symbol<<std::endl
			<<"Boat Position: Line - "<<position.line<<" Column - "<<position.column
			<<" Orientation - "<< orientation <<std::endl << "Size: "<< size << std::endl
			<< "Color: " << color << std::endl << "Status: "<< status<< std::endl;
}

unsigned int Ship::getColor() const {
	return color;
}

char Ship:: getOrientation() const {
	return orientation;
}

const Position<int> Ship::getPosition() const {
	return position;
}

unsigned int Ship::getSize() const {
	return size;
}

const std::string& Ship::getStatus() const {
	return status;
}

char Ship::getSymbol() const {
	return symbol;
}