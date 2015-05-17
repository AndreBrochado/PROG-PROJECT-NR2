#ifndef BOMB_H_
#define BOMB_H_

#include "Utilities.h"

class Bomb
{
public:
	Bomb(PositionChar targetPosition);
	PositionChar getTargetPosition() const;
	void show() const; // shows the attributes of the bomb (for debugging)
<<<<<<< HEAD
	int getTargetLineInt() const;
	int getTargetColumnInt() const;
=======
	int getTargetColumnInt() const;
	int getTargetLineInt() const;
>>>>>>> 3e0d94d20bccc9960d6fcbda265cc8a14efadaab

private:
	char targetLine, targetColumn;
};

#endif // BOMB_H_
