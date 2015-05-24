#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <algorithm>
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
    cout << activePlayer.getName() << "'s turn:" << endl;
    cout << "Your opponent's board: " << endl;
    cout << passivePlayer.getBoard();
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
            getline(oldScores, tempLine.playerName, ':');
            if (!(tempLine.playerName == "")) {
                oldScores >> dummy >> tempLine.score >> tempLine.numLines >> dummy >> tempLine.numColumns >>
                tempLine.shipArea;
            }
            else
                break;
        }
            scoresList.push_back(tempLine);
    }
    oldScores.close();
    newScores.open("Top10 Scores.txt");
    for (int i = 0; i < min((int)scoresList.size(), 10); i++) {
        newScores << scoresList[i].playerName << ": " << scoresList[i].score << " " << scoresList[i].numLines << "x" <<
        scoresList[i].numColumns << " " << scoresList[i].shipArea << endl;
    }
    newScores.close();
}

void createTextFile(string fileName) {
    ofstream outputStream;
    outputStream.open(fileName);
}

void printHighscores() {
    ifstream scores;
    string line;
    scores.open("Top10 Scores.txt");
    cout << endl;
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
        getline(highScoresFile, dummyString, ':');
        if (dummyString=="")
            return i;
        else {
            highScoresFile >> oldScore >> dummyString >> dummyString;
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
    char showScores;
    int player;
    Player winningPlayer, losingPlayer;
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
    score = winningPlayer.getPlayTime() * (float) winningPlayer.getShipArea() / (float) winningPlayer.getBoardArea();
    if (scorePlace(score) != -1) {
        cout << "Congratulations, " << winningPlayer.getName() << "! You won and your score was one of the top10! " <<
        endl;
        saveHighScore(winningPlayer, losingPlayer, score, scorePlace(score));
    }
    else
        cout << "Congratulations, " << winningPlayer.getName() <<
        ", you won! But, sadly, you didn't make it to top10 score! :(" << endl;
    cout << "Do you wish to see the top10 scores? <Y for yes, N for no> ";
    cin >> showScores;
    if(showScores == 'Y')
        printHighscores();

    system("pause");

    return 0;
}
