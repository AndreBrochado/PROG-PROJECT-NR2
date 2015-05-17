#include "Bomb.h"

#include <iostream>
#include <cstdlib>

Bomb::Bomb(PositionChar targetPosition) {
	targetLine = targetPosition.line + rand()%3 -1;
	targetColumn = targetPosition.column + rand()%3 - 1;
}


PositionChar Bomb::getTargetPosition() const {
	PositionChar temp;
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

