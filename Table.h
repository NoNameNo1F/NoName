#pragma once
#include <iostream>
#include <sstream>
#include <set>
#include <time.h>
using namespace std;

#define SUITS 4
#define FACES 13

class Random{
private:
    Random(){
        srand((unsigned)time(NULL));
    }
public:
    static Random& instance(){
        static Random neo;
        return neo;
    };
    int next(int max){ // random from 0 to max - 1
        return rand() % max; 
    }
    int next(int min, int max){
        return (rand() % (max - min + 1) + min); // random from min to max
    }
};


class Table{

};

class Dealer{
private:
    Random shuffleBoard;
    const char* Suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char* Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen" "King" };
    int deck[SUITS][FACES]; // deck[SUITS][FACES]= {};
public:
    Dealer() : shuffleBoard(Random::instance()), deck({}) {}
    ~Dealer(){
        delete Suits;
        delete Ranks;
    }

    void shuffleCards(int (&deck)[SUITS][FACES]){
        set<int> storeDealtCards;
        for (auto i = 0; i < SUITS; i++){
            for (auto j = 0; j < FACES; j++){
                int pos = 0;
                while (storeDealtCards.find(pos) != storeDealtCards.end()){
                    pos = shuffleBoard.next(1, 52);
                }
                deck[i][j] = pos;
                storeDealtCards.insert(pos);
            }
        }
    }

    void printCardShuffling(int deck[SUITS][FACES]){   
        stringstream writer; 
        for (auto num = 0; num < 52; num++){
            for (auto i = 0; i < SUITS; i++){
                for (auto j = 0; j < FACES; j++){
                    if (deck[i][j] = num) {
                        writer << "(" << Suits[i] << ", " << Ranks[j] << ")\n"; 
                    }
                }
            }
        }
        cout << writer.str();
    }

    int** dealingForHand(int deck[SUITS][FACES]){
        
    }  
};

class Player{
private:
    short int** cards;
public:
    Player(){}
    ~Player();
};