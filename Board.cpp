//
// Created by Ansore on 10-05-2015.
//

#include "Board.h"
#include <iostream>
#include <fstream>
#include <vector>

Board::Board(const std::string &filename) {
    std::ifstream inputFile;
    char dummy;
    char symbol, line, column, orientation;
    PositionChar tempPosition;
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
    std::vector <std::vector<int>> table(this->numLines, std::vector<int>(this->numColumns, 0));

    for(size_t i=0; i<ships.size(); i++){
        if(ships[i].getOrientation()== 'V'){  // CHECK TOMORROW - ppl say gets

        }
    }




}