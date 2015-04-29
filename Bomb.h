#ifndef BOMB_H_
#define BOMB_H_

#include "Utilities.h"

class Bomb
{
public:
	Bomb(PositionChar targetPosition);
	PositionChar getTargetPosition() const;
	void show() const; // shows the attributes of the bomb (for debugging)
private:
	char targetLine, targetColumn;
};

#endif // BOMB_H_
