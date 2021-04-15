#pragma once
#include "Player.h"
#include "FakeDeck.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <string>
#include <cstring>
#include "Interface.h"

using namespace std;

class Table {
private:
    int numberOfPlayers;
    int round;
    Player** players;
    Dealer* dealer;
    unsigned int pot;
    unsigned int defaultBet;
public:
    Table() : numberOfPlayers(1), players(NULL), pot(0), defaultBet(0), round(0) {
        dealer = new Dealer();
    };
    ~Table() {
       /* for (int i = 0; i < numberOfPlayers; i++) {
            players[i] = NULL;
            delete (players + i);

        }
        delete[] players;
        delete dealer;*/
    }

    void setPot(unsigned int money);

    unsigned int Pot();

    void setDefaultBet(unsigned int money);

    unsigned int DefaultBet();


    void setRound(int round);

    int Round();

    void setNumberOfPlayers();

    int NumberOfPlayer();

    void setTableDefaultBet();

    void createPlayers();

    void createPlayers(vector<Player*> continuePlayersList);

    void printPlayersName();

    void setMoneyPlayers();

    void setGameRound();

    void playGame();

    string printWinners(vector<int> winnerList);

    string printPlayersMoney();

    void logging(vector<int> winnerList);

    void kickPlayers();

    vector<Player*>  savePlayersAndResetTable();
};