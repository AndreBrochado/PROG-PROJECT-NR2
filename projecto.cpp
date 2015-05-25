
#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include "Player.h"

using namespace std;

struct scoreLine {
    string playerName;
    float score;
    int numLines, numColumns;
    int shipArea;
};

void makePlay(Player &activePlayer, Player &passivePlayer) {
    time_t initTime, finalTime;
    time(&initTime);
    setColor(3);
    cout << activePlayer.getName();
    setColor(15,0);
    cout <<  "'s turn:" << endl;
    cout << endl;
    cout << "Your opponent's board: " << endl;
    cout << passivePlayer.getBoard();
    cout << endl;
    passivePlayer.attackBoard(activePlayer.getBomb());
    cout << passivePlayer.getBoard();
    time(&finalTime);

    activePlayer.incPlayTime(finalTime-initTime);
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

void saveHighScore(Player &winner, Player &loser, float score, int scorePlace) {
    char dummy;
    ifstream oldScores;
    scoreLine tempLine;
    vector<scoreLine> scoresList;
    ofstream newScores;
    oldScores.open("Top10 Scores.txt");
    for (int i = 0; i < 10; i++) {
        if (i == scorePlace) {
            tempLine.playerName = winner.getName();
            tempLine.score = score;
            tempLine.numLines = loser.getBoard().getNumLines();
            tempLine.numColumns = loser.getBoard().getNumColumns();
            tempLine.shipArea = loser.getShipArea();
        }
        else {
            tempLine.playerName = "";
            getline(oldScores, tempLine.playerName, ':');
            if (!(tempLine.playerName == "")) {
                oldScores >> tempLine.score >> tempLine.numLines >> dummy >> tempLine.numColumns >>
                tempLine.shipArea;
                oldScores.ignore(1000, '\n');
            }
            else
                break;
        }
            scoresList.push_back(tempLine);
    }
    oldScores.close();
    newScores.open("Top10 Scores.txt");
    for (int i = 0; i < min((int)scoresList.size(), 10); i++) {
        if(i!=0)
            newScores<<endl;
        newScores  << scoresList[i].playerName << ": " << scoresList[i].score << " " << scoresList[i].numLines << "x" <<
        scoresList[i].numColumns << " " << scoresList[i].shipArea;
    }
    newScores.close();
}

void createTextFile(string fileName) {
    ofstream outputStream;
    outputStream.open(fileName);
    outputStream.close();
}

void printHighscores() {
    ifstream scores;
    string line;
    scores.open("Top10 Scores.txt");
    cout << endl <<"(Name: Score Board Dim. Ships area)"<<endl;
    while(getline(scores, line)){
        cout<< line << endl;
    }
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
        dummyString = "";
        getline(highScoresFile, dummyString, ':');
        if (dummyString=="")
            return i;
        else {
            highScoresFile >> oldScore;
            highScoresFile.ignore(1000, '\n');
            if (score < oldScore)
                return i;
        }
    }
    highScoresFile.close();
    return -1;
}

int main() {
    srand(time(NULL));
    int player;
    Player winningPlayer, losingPlayer;
    float score;
    string playerName, fileName;
    string showScores;

    getPlayerData(playerName, fileName);
    Player Player1(playerName, fileName);
    getPlayerData(playerName, fileName);
    Player Player2(playerName, fileName);

    cout << "Let's see who plays first:" << endl;
    player = rand() % 2;
    if (player == 0) {
        setColor(3);
        cout << Player1.getName() ;
        setColor(15,0);
        cout << " wins the coin toss and plays first!" << endl;

    }
    else {
        cout << Player2.getName() << " wins the coin toss and plays first!" << endl;

    }


    while (!(Player1.wonGame(Player2) || Player2.wonGame(Player1))) {
        if (player == 0)
            makePlay(Player1, Player2);
        else
            makePlay(Player2, Player1);
        player = (player + 1) % 2;
    }
    if (Player1.wonGame(Player2)) {
            winningPlayer = Player1;
            losingPlayer = Player2;
    }
    else {
        winningPlayer = Player2;
        losingPlayer = Player1;
    }
    score = winningPlayer.getPlayTime() * (float) losingPlayer.getShipArea() / (float) losingPlayer.getBoardArea();
    if (scorePlace(score) != -1) {
        cout << "Congratulations, " << winningPlayer.getName() << "! You won and your score was one of the top10! " <<
        endl;
        saveHighScore(winningPlayer, losingPlayer, score, scorePlace(score));
    }
    else
        cout << "Congratulations, " << winningPlayer.getName() <<
        ", you won! But, sadly, you didn't make it to top10 score! :(" << endl;
    readString("Do you wish to see the top10 scores? <Y for yes, Any other key for No> ", showScores);
    if(showScores == "Y")
        printHighscores();
    system("pause");

    return 0;
}
