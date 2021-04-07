#pragma once
#include <iostream>
#include <sstream>
#include <set>
#include <map>
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

class Player{
private:
    int** hand;
public:
    Player() : hand(NULL) {}
    ~Player(){
        for (int i = 0; i < 5; i++){
            delete[] (hand + i);
        }
        delete[] hand;
    };

    void setHand(int** hand){ this->hand = hand;}
    int** Hand(){return hand;}
};

class Dealer{ //dealer also a player
private:
    Random shuffleBoard;
    const char* Suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char* Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen" "King" };
    int deck[SUITS][FACES]; // deck[SUITS][FACES]= {};
public:
    Dealer() : shuffleBoard(Random::instance()), deck({}) {} // generate array fill with zero
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

    pair<int, int> searchCardPos(int deck[SUITS][FACES], int num){
        pair<int, int> pos;
        for (auto i = 0; i < SUITS; i++){
            for (auto j = 0; j < FACES; j++){
                if (deck[i][j] == num) {
                    pos.first = i; // SUIT
                    pos.second = j; // FACE
                }
            }
        }
        return pos;
    }

    void printCardShuffling(int deck[SUITS][FACES]){   
        stringstream writer; 
        for (int num = 0; num < 52; num++){
            pair <int, int> cardName = searchCardPos(deck, num); 
            writer << "(" << Suits[cardName.first] << ", " << Ranks[cardName.second] << ")\n"; 
        }
        cout << writer.str();
    }

    int** dealingForHand(int deck[SUITS][FACES], int turn = 1, int numberOfPlayers = 1){ // turn to deal cards, default is there is only one player on table
        int** hand = new int*[5]; // 5 card per player
        for (int i = 0; i < 5; i++){
            *(hand + i) = new int[2]; // first col present row of the matrix, second one present column of the matrix 
        }
        //assign cards
        int pos = turn;
        for (int j = 0; j < 5; j++){ // hand will have 5 cards
            pair <int, int> cardName = searchCardPos(deck, pos);
            int* card = *(hand + j); // present card details
            *(card + 0) = cardName.first; // suit
            *(card + 1) = cardName.second; // faces
            // free memory of temp card variable
            card = NULL;
            delete[] card;
            pos += numberOfPlayers; // Ex: 1, 5, 9, 13, 17
        }
        return hand;
    }

    void Dealing(Player players[], int numberOfPlayers){
        shuffleCards(this->deck); //shuffle card
        for (int i = 1; i <= numberOfPlayers; i++){
            int** hand = dealingForHand(deck, i, numberOfPlayers); //dealing for each player
            players[i].setHand(hand); //player get cards
        }
    }

    void printHand(int** hand){
        stringstream writer;
        for (int i = 0; i < 5; i++){
            writer << "(" << Suits[*( *(hand + i) + 0 )] /*suit*/ << ", " << Ranks[*( *(hand + i) + 1 )] /*rank*/ << ")\n";
        }
        cout << writer.str();
    }

    void printCardFromPlayer(Player p){
        printHand(p.Hand()); // get hand from player then print
    }

    map<string, int> countRank(int** hand){
        map<string, int> dict;
        for(int i = 0; i < 5; i++){
            string rank = Ranks[*( *(hand + i) + 1 )];
            if (dict.find(rank) == dict.end()){
                pair<string, int> obj = make_pair(rank, 1); // if dict doesn't have that rank, add that rank with num is 1
            }
            else{
                dict[rank] += 1; // if found in dict then increase number
            }
        }
        return dict;
    }

    bool isFourOfAKind(int** hand){
        bool check = false;
        map<string, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 4 && dict.size() == 2) check = true;
            //two type of ranks, but one type has 4 cards then others will be one different rank
        }
        return check;
    }

    bool isFullHouse(int** hand){
        bool check = false;
        map<string, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 3 && dict.size() == 2) check = true; 
            //two type of ranks, but one type has 3 cards then others will be one different rank has 2 cards same rank
        }
        return check;
    }

    bool isFlush(int** hand){
        bool check = false;
        string suit = Suits[* ( *(hand + 0) + 0 )]; //get suit of first card to check
        for (int i = 1; i < 5; i++) { // don't have to chekc first suit
            if (suit == Suits[* ( *(hand + i) + 0 )]){
                check = true;
            }
        }
        return check;
    }

    bool isStraight(int** hand){
        bool check = false;
        int count = 0;
        int indexRank = * ( *(hand + 0) + 1 ); // we only need index of rank from Ranks variable, we don't need its name
        // Ex: rank "Ace" has index 0, we need 0 to check if that is sequential rank
        for (int i = 1; i < 5; i++){
            if (* ( *(hand + i) + 1 ) - indexRank == 1) { // sequential rank
                indexRank = * ( *(hand + i) + 1 ); // then set indexRank to current Rank for next calculation
                count++;
            }
            else break; // if not sequential rank then break
        }
        if (count == 4) check = true; // De xet 5 la co rank tang dan, thi minh xet 4 cap xem no co hon nhau 1 don vi khong
        return check;
    }

    bool isStraigntFLush (int** hand){
        return isFlush(hand) && isStraight(hand);
    }

    bool isThreeOfAKind(int** hand){
        bool check = false;
        map<string, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 3 && dict.size() == 3) check = true; 
            //three type of ranks, but one type has 3 cards then others will be two different ranks
        }
        return check;
    }

    bool isTwoPairs(int** hand){
        bool check = false;
        map<string, int> dict = countRank(hand);
        int count = 0;
        for (auto it : dict){
            if (it.second == 2) count++; 
        }
        if (count == 2) check = true;
        // if count equal 2 then there are 2 pairs of the same rank
        return check;
    }

    bool isPair(int** hand){
        bool check = false;
        map<string, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 2 && dict.size() == 4) check = true; 
            //four type of ranks, but one type has 2 cards then others will be three different ranks
        }
        return check;
    }

    int getHighestCard(int** hand){}

};