#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "Player.h"

using namespace std;

bool makePlay(Player &activePlayer, Player &passivePlayer){
	cout << activePlayer.getName() << "'s turn:" << endl;
	cout << "Your opponent's board: " << endl;
	cout << passivePlayer.getBoard().display;
	passivePlayer.attackBoard(activePlayer.getBomb());
	
	
}


bool readString(const string &prompt, string &returnString) {
    string testString;
    cout << prompt;
    getline(cin, testString);
    cout << endl;
    if (cin.fail()) {
        if (!cin.eof())
            cin.ignore(1000, '\n');
        cin.clear();
        return false;
    }
    returnString = testString;
    return true;
}

bool getPlayerData(string &playerName, string &fileName) {
    fstream testFile;
    bool result = false; // just for code changing security
    do {
        result = readString("Insert your name: ", playerName);
    } while (!result);

    result = false; // just for code changing security

    do {
        do {
            result = readString("Insert your file name: ", fileName);
        } while (!result);

        if (fileName.find('.') == string::npos)
            //This will add
            fileName += ".txt"; //the .txt extension if the user didn't include one.

        testFile.open(fileName);
        result = testFile.is_open();
        if(!result)
            cout<<"Invalid/Not-existant file name, please insert a valid one!"<<endl;
    }while(!result);
}

int main() {
    srand(time(NULL));
    time_t initTime = time(NULL);
    int player;
    std::string playerName, fileName;

    getPlayerData(playerName, fileName);
    Player Player1(playerName, fileName);
    getPlayerData(playerName, fileName);
    Player Player2(playerName, fileName);

    cout<<"Let's see who plays first!"<< endl;
    player=rand()%2;
    if(player == 0) {
        cout << Player1.getName() << " wins the coin toss and plays first!" << endl;
    }
    else
        cout<<Player2.getName()<<" wins the coin toss and plays first!"<<endl;





    system("pause");

    return 0;
}
