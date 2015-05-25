/*
 * Utilities.h
 *
 *  Created on: 29/04/2015
 *      Author: up201403057
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <windows.h>



template<class T>
struct Position{
	T line, column;
};


// Set text color & background
void setColor(unsigned int color, unsigned int background_color);

// Set text color
void setColor(unsigned int color);



#endif /* UTILITIES_H_ */
