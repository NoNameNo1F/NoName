#pragma once
#include "Random.h"
#include "FakeName.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define SUITS 4
#define FACES 13

class Player{
private:
    int** hand;
    int win;
    int money;
    string name;
    int handStatus;
public:
    Player() : hand(NULL), win(0), money(0), name(generateFakeName()), handStatus(-1) {}
    ~Player(){ 
        if (hand != NULL){ 
            // Dealer won't have cards if there is more than 2 players
            for (int i = 0; i < 5; i++){
                delete[] hand[i];
            }
            delete[] hand;
        }
    };
    Player(const Player& other);
    Player& operator= (const Player& other);
    bool operator== (const Player& other);

    void setHand(int** hand);
    int** Hand();
    void setWin();
    int getWin();
    void setMoney(int money);
    int Money();
    string Name();
    int HandStatus();
    void setHandStatus(int status);
};

class Dealer : public Player { //dealer also a player
private:
    int deck[SUITS][FACES];
public:
    Random shuffleBoard;
public:
    Dealer() : shuffleBoard(Random::instance()){
        setMoney(100000000);
        for (int i = 0; i < SUITS; i++){ // generate array fill with zero
            for (int j = 0; j < FACES; j++){
                deck[i][j] = -1;
            }
        }
    }
    virtual ~Dealer(){}

    int setMoneyBet(Player** players, int numberOfPlayers);

    int setMoneyBetWithDefaultBet(Player** players, int numberOfPlayers, int defaultBet);

    void shuffleCards();

    void resetCards();

    pair<int, int> searchCardPos(int deck[SUITS][FACES], int num);

    void printCardShuffling(int deck[SUITS][FACES]);

    int** dealingForHand(int deck[SUITS][FACES], int turn = 1, int numberOfPlayers = 2);

    int*** dealingForHands(int deck[SUITS][FACES], int numberOfPlayers = 3);

    void dealing(Player** &players, int numberOfPlayers);

    string printHand(int** hand);

    map<int, int> countRank(int** hand);

    bool isFourOfAKind(int** hand);

    bool isFullHouse(int** hand);

    bool isFlush(int** hand);

    bool isStraight(int** hand);

    bool isStraigntFLush (int** hand);

    bool isThreeOfAKind(int** hand);

    bool isTwoPairs(int** hand);

    bool isPair(int** hand);

    int getHighestCard(int** hand);

    int getStatusOfHand(int** hand);

    int* rankingHands(int*** hands, int numberOfPlayers);

    string showHands(Player** players, int numberOfPlayers);

    vector<int> evaluateHands(Player** &players, int numberOfPlayers, int pot);

};