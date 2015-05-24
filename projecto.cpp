#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "Player.h"

using namespace std;

void makePlay(Player &activePlayer, Player &passivePlayer) {
    cout << activePlayer.getName() << "'s turn:" << endl;
    cout << "Your opponent's board: " << endl;
    passivePlayer.getBoard().display();
    passivePlayer.attackBoard(activePlayer.getBomb());
    cout << passivePlayer.getBoard();
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
        if (!result)
            cout << "Invalid/Not-existant file name, please insert a valid one!" << endl;
    } while (!result);
    return true;
}

string numToString(float number) {
    ostringstream convert;   // stream used for the conversion
    convert << number;      // insert the textual representation of 'Number' in the characters in the stream
    return convert.str();
}

void saveHighScore(Player &winner, float score, int scorePlace) {
    ifstream oldScores;
    string scoreSaver = "";
    ofstream newScores;
    oldScores.open("Top10 Scores.txt");
    for (int i = 0; i < 10; i++) {
        if (i == scorePlace)
            scoreSaver +=
                    winner.getName() + " " + numToString(score) + " " + numToString(winner.getBoard().getNumLines()) + "x" +
                    numToString(winner.getBoard().getNumColumns()) + numToString(winner.getShipArea()) + "\n";
        else
            getline(oldScores, scoreSaver);
    }
    oldScores.close();
    newScores.open("Top10 Scores.txt");
    newScores<<scoreSaver;
    newScores.close();
}

void createTextFile(string fileName) {
    ofstream outputStream;
    outputStream.open(fileName);
}

void printHighscores(){
    ifstream scores;
    scores.open("Top10 Scores.txt");
    cout<<endl<<scores;
}

int scorePlace(float score) {
    fstream highScoresFile;
    string dummyString;
    float oldScore;
    highScoresFile.open("Top10 Scores.txt", ios::in);
    if (!highScoresFile.is_open()) {
        createTextFile("Top10 Scores.txt");
        highScoresFile.open("Top10 Scores.txt", ios::in);
    }
    for (int i = 0; i < 10; i++) {
        if (highScoresFile.eof())
            return i;
        highScoresFile >> dummyString >> oldScore >> dummyString >> dummyString;
        if (score > oldScore)
            return i;
    }
    return -1;
}

int main() {
    srand(time(NULL));
    time_t initTime, finalTime, gameTime;
    int player;
    Player winningPlayer;
    float score;
    std::string playerName, fileName;

    getPlayerData(playerName, fileName);
    Player Player1(playerName, fileName);
    getPlayerData(playerName, fileName);
    Player Player2(playerName, fileName);

    cout << "Let's see who plays first:" << endl;
    player = rand() % 2;
    if (player == 0) {
        cout << Player1.getName() << " wins the coin toss and plays first!" << endl;
    }
    else
        cout << Player2.getName() << " wins the coin toss and plays first!" << endl;

    initTime = time(NULL);
    while (!Player1.wonGame(Player2) || !Player2.wonGame(Player1)) {
        if (player == 0)
            makePlay(Player1, Player2);
        else
            makePlay(Player2, Player1);
        player = (player + 1) % 2;
    }
    finalTime = time(NULL);
    Player1.wonGame(Player2) ? winningPlayer = Player1 : winningPlayer = Player2;
    gameTime = finalTime - initTime;
    score = gameTime * Player1.getShipArea() / Player1.getBoardArea();
    if(scorePlace(score)!=-1) {
        cout<<"Congratulations, "<< winningPlayer.getName() <<"! You won and your score was one of the top10! "<<endl;
        saveHighScore(winningPlayer, score, scorePlace(score));
    }
    else
        cout<<"Congratulations, "<<winningPlayer.getName() <<", you won! But, sadly, you didn't make it to top10 score! :("<<endl;
    cout<<"Do you wish to see the top10 scores? <Y for yes, N for no> ";
    if(getchar()=='Y')
        printHighscores();

    system("pause");

    return 0;
}
