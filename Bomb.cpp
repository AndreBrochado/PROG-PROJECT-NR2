#include "Bomb.h"

#include <iostream>
#include <cstdlib>

Bomb::Bomb(Position<char> targetPosition) {
	targetLine = (char) (targetPosition.line + rand()%3 -1);
	targetColumn = (char)  (targetPosition.column + rand()%3 - 1);
}

Position<char> Bomb::getTargetPosition() const {
	Position<char> temp;
	temp.line = targetLine;
	temp.column = targetColumn;
	return temp;
}

void Bomb::show() const{
	std::cout<<"line: "<<targetLine<<" column: "<<targetColumn<<std::endl;
}

int Bomb::getTargetLineInt() const {
	return targetLine-'A';
}

int Bomb::getTargetColumnInt() const {
	return targetColumn-'a';
}