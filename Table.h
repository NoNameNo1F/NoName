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
    int _numberOfPlayers;
    int _round;
    Player** _players;
    Dealer* _dealer;
    unsigned int _pot;
    unsigned int _defaultBet;
public:
    Table() : _numberOfPlayers(1), _players(NULL), _pot(0), _defaultBet(0), _round(0) {
        _dealer = new Dealer();
    };
    ~Table() {
       /* for (int i = 0; i < numberOfPlayers; i++) {
            players[i] = NULL;
            delete (players + i);

        }
        delete[] players;
        delete dealer;*/
    }

    void setPot(unsigned int _money);

    unsigned int Pot();

    void setDefaultBet(unsigned int _money);

    unsigned int DefaultBet();


    void setRound(int _round);

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