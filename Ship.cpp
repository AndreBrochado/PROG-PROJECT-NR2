//
// Created by Ansore on 10-05-2015.
//

#include <stdlib.h>
#include "Ship.h"

Ship::Ship(char symbol, PositionChar position, char orientation, unsigned int size, unsigned int color) {
    this->symbol = symbol;
    this->position.line = (unsigned int) position.line - 'A';
    this->position.column = (unsigned int) position.column - 'a';
    this->orientation = orientation;
    this->size = size;
    this->color = color;
    status = std::string(symbol, size);
}

bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax,
                unsigned int columnMax) {
    PositionInt newPosition;
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
            return false;
    }

    if ((orientation == 'V' && !rotate) || (orientation == 'H' && rotate)) if (newPosition.line + size <= lineMax &&
                                                                               newPosition.line >= lineMin &&
                                                                               newPosition.column <= columnMax
                                                                               && newPosition.column >= columnMin) {
        position.line = newPosition.line;
        position.column = newPosition.column;
        return true;
    }
    else if ((orientation == 'H' && !rotate) || (orientation == 'V' && rotate)) if (newPosition.line >= lineMin &&
                                                                                    newPosition.line <= lineMax &&
                                                                                    newPosition.column + size <=
                                                                                    columnMax
                                                                                    &&
                                                                                    newPosition.column >= columnMin) {
        position.line = newPosition.line;
        position.column = newPosition.column;
        return true;
    }

    return false;


}

bool Ship::moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax) {
    int direction = rand() % 5;
    bool rotate;
    if (rand() % 2 == 0)
        rotate = true;
    else
        rotate = false;
    switch (direction) {
        case 1:
            return move('N', rotate, lineMin, columnMin, lineMax, columnMax);
        case 2:
            return move('S', rotate, lineMin, columnMin, lineMax, columnMax);
        case 3:
            return move('E', rotate, lineMin, columnMin, lineMax, columnMax);
        case 4:
            return move('W', rotate, lineMin, columnMin, lineMax, columnMax);
        default:
            return false;
    }

}

bool Ship::attack(size_t partNumber) {
    if (partNumber > size - 1)
        return false;
    else {
        status[partNumber] = (char) tolower(status[partNumber]);
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
    if(lower>=upper)
        return true;
    else
        return false;
}

char getOrientation(){
    return orientation;
}

void Ship::show() const{
    std::cout<<"Boat Symbol: "<<symbol<<std::endl
             <<"Boat Position: Line - "<<position.line<<" Column - "<<position.column
             <<" Orientation - "<< orientation <<std::endl << "Size: "<< size << std::endl
             << "Color: " << color << std::endl << "Status: "<< status<< std::endl;
}

