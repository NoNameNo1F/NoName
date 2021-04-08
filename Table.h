#pragma once
#include "Player.h"
#include "FakeDeck.h"
#include <iostream>

using namespace std;

class Table{
private:
    int numberOfPlayers;
    Player** players;
    Dealer* dealer;
public:
    Table() : numberOfPlayers(1), players(NULL) {
        dealer = new Dealer();
    };
    ~Table(){
        for (int i = 0; i < numberOfPlayers; i++){
            delete (players + i);

        }
        delete[] players;
        delete dealer;
    }

    void setNumberOfPlayers();

    int NumberOfPlayer();

    void createPlayers();

    void playGame();
};