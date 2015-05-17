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
static void setColor(unsigned int color, unsigned int background_color) {
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == 0)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
									  BACKGROUND_RED);
}

// Set text color
static void setColor(unsigned int color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

#endif /* UTILITIES_H_ */
