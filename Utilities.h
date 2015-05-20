/*
 * Utilities.h
 *
 *  Created on: 29/04/2015
 *      Author: up201403057
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <windows.h>

struct PositionChar // to store a board position in char format
{ // example: 'B','d'
	char line, column; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};

struct PositionInt // to store a board position in unsig. integer format
{ // example: 7,0
	unsigned int line, column; // ranges: lin - [0..26]; col - [0..26]
};

// Set text color & background
void setColor(unsigned int color, unsigned int background_color);

// Set text color
void setColor(unsigned int color);

#endif /* UTILITIES_H_ */
