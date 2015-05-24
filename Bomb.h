#ifndef BOMB_H_
#define BOMB_H_

#include "Utilities.h"

class Bomb
{
public:
	Bomb(Position<char> targetPosition);
	Position<char> getTargetPosition() const;
	void show() const; // shows the attributes of the bomb (for debugging)
	int getTargetLineInt() const;
	int getTargetColumnInt() const;

private:
	char targetLine, targetColumn;
};

#endif // BOMB_H_
