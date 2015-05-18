//just for old time sake
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "boardFileCreator.cpp"


void bottles(int number){
	for(int i=number; i>=0; i--) {
		if(i==0)
			printf("No more bottles of beer on the wall!");
		else
		printf("\n %d bottles of beer on the wall\n %d bottles of beer\n take one down, patch it around\n %d bottles of beer on the wall\n",
			   i,i, i - 1);
	}
}

int main() {
	createBoardFile(); //x2
	srand(time(NULL));
	bottles(99);
	system("pause");
	return 0;
}
