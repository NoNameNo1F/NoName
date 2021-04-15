
#include "Poker.h"
#include <iostream>
#include <sstream>
#include <set>
#include <time.h>
    
#include <map>
#include <vector>
#include <algorithm>


using namespace std;


#define SUITS 4
#define FACES 13


int ChooseMenu()
{
    int n;  
    cout << "\n Moi ban chon menu: ";
    cin >> n;
     if (n > 0 || n < 99)
         return n;
     else
         return ChooseMenu();
}
void Menu()
{
	cout << "=================MENU================\n";
	cout << "____________Choose Game Play_________\n";
	cout << "1. Player Versus Computer";
	cout << "2. Player Versus Player";
	cout << "3. Multi Player";
	cout << "0. Thoat!!!\n";
	cout << "=====================================\n";
}
void LoadingMenu()
{
    int chon = ChooseMenu():
    switch (chon)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 0:
            cout << " Good Bye!!! " << endl;
            break;
    }
}

class Random {
private:
    Random() {
        srand((unsigned)time(NULL));
    }
public:
    static Random& instance() {
        static Random neo;
        return neo;
    };
    int next(int max) { // random from 0 to max - 1
        return rand() % max;
    }
    int next(int min, int max) {
        return (rand() % (max - min + 1) + min); // random from min to max
    }
};


class Dealer : public Player { // dealer also a player
    private:
        int deck[SUITS][FACES]; // deck[SUITS][FACES]= {};
    public:
        Random shuffleBoard;
    public:
        Dealer() : shuffleBoard(Random::instance()) {
            Dealer() : shuffleBoard(Random::instance()) {
                for (int i = 0; i < SUITS; i++) {
                    for (int j = 0; j < FACES; j++) {
                        deck[i][j] = -1;
                    }
                }
            }
            virtual ~Dealer() { }
        }
    void shuffleCards(int (&deck)[SUITS][FACES]) {
        for (auto i = 1; i <= 52; i++) {
            int ranSuits, ranFaces;
            do {
                ranSuits = shuffleBoard.next(0, 4);
                ranFaces = shuffleBoard.next(0, 12);
            } while (deck[ranSuits][ranFaces] != -1);
            deck[ranSuits0][ranFaces] = i;
        }
    }
   
    pair<int, int> searchCardPos(int deck[SUITS][FACES], int num){
        pair<int, int> pos;//first la key , second la value
        for (auto i = 0; i < SUITS, i++) {
            for (auto j = 0; j < FACES; j++) {
                if (deck[i][j] == num) {
                    pos.first = i; //SUIT
                    pos.second = j; //FACE
                }
            }
        }
        return pos;
    }

    void printCardShuffling(int deck[SUITS][FACES]) {
        string Suits[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
        stringstream writer;
        for (auto num = 0; num < 52; num++) {
            {
                pair<int, int> cardName = searchCardPos(deck, num);
                writer << "(" << Suits[cardName.first] << ", " << Ranks[cardName.second] << ")\n";  
            }
        }
        cout << writer.str();
    }

    int** dealingForHand(int deck[SUITS][FACES], int turn , int numberOfPlayers ) {// turn to deal cards, default is there is only one player on table and a dealer
        int** hand = new int* [5]; // 5 card per player
        for (int i = 0; i < 5; i++) {
            *(hand + i) = new int[2]; // dong dau la hang , dong 2 la cot cua mangbai`
        }
        //assign cards
        int pos = turn;
        for (int j = 0; j < 5; j++) {
            pair<int, int> cardName = searchCardPos(deck, pos);
            int* card = *(hand + j); //present card details
            *(card + 0) = cardName.first;//suit
            *(card + 1) = cardName.second;//faces
            //free memory of temp card variable
            card = NULL;
            delete[] card;
            pos += numberOfPlayers; //ex: 1, 5 , 9 ,13 , 17
        }
        return hand;
    }

    int*** dealingForHands(int deck[SUITS][FACES], int numberOfPlayers ) {
        int*** hands = new int** [numberOfPlayers];
        for (int i = 0; i <= numberOfPlayers; i++) {
            *(hands + i) = dealingForHand(deck, i, numberOfPlayers);//plus one for turn
        }
        return hands;
    }
    
    void dealing(Player** &players, int numberOfPlayers) {
        shuffleCards(this->deck);//shuffle card

        int*** hands = dealingForHands(deck, numberOfPlayers);

        bool storeDeck[numberOfPlayers] = { false };
        for (int i = 0; i < numberOfPlayers; i++) {
            int deckPos;
            do {
                deckPos = this->shuffleBoard.next(numberOfPlayers); //player'll receive random deck
            } while (storeDeck[deskPos] == true);
            storeDeck[deckPos] = true;
            int** hand = *(hand + deckPos);
            players[i]->setHand(hand); // player get cards
            hand = NULL; // maybe memory leak

            delete hand;
        }
    }
  
    void printHand(int** hand) {
        string Suits[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
        stringstream writer;
        for (int i = 0; i < 5; i++) {
            int suitIndex = *(*(hand + i) + 0);
            int rankIndex = *(*(hand + i) + 1);
            writer << "(" << Suits[suitIndex] << "," << Ranks[rankIndex] << ")\n";
        }
        cout << writer.str();
    }

    map<int, int> countRank(int** hand) {
        map<int, int> dict;
        for (int i = 0; i < 5; i++) {
            string rank = Ranks[*(*(hand + i) + 1)];
            int rank = *(*(hand + i) + 1);
            if (dick.find(rank) == dick.end()) {
                pair<int, int> obj = make_pair(rank, 1); // neu dict ko co rank thi them no la rank 1
                dict.insert(obj);
            }
            else {
                dict[rank] += 1; //neu da tim dc dict thi tang 
            }
        }
        return dict;
    }

    int isStraightFlush(int** hand) {
        return isFlush(hand) && isStraight(hand);
    }
   
    int isFourOfAKind(int** hand) {
        int check = 0;
        map<int, int> dict = countRank(hand);
        for (auto it : dict) {
            if (it.second == 3 && dict.size() == 2)
                check = 1;
        }
        return check;
    }
    
    int isFullHouse(int** hand) {
        int check = 0;
        map<int, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 3 && dict.size() == 2) check = 1;
        }
        return check;
    }
  
    int isFlush(int** hand) {
        int check = 0;
        int suit = *(*(hand + 0) + 0);
        for (int i = 1; i < 5; i++) {
            if (suit != *(*(hand + i) + 0)) {
                check = 0;
            }
        }
        return check;
    }
  
    int isStraight(int** hand) {
        int check = 0;
        vector<int> arr;

        for (int i = 0; i < 5; i++) {
            arr.push_back(*(*(hand + i) + 1)); // them phan tu phia sau arr
        }
        sort(arr.begin(), arr.end()); // sap xep lai mang
        for (int i = 0; i < 5; i++) {
            if (arr[i + 1] - arr[i] != 1) {
                check = 0;
                break;
            }
        }
        return check;
    }
   
    int ThreeOfAKind(int** hand) {
        int check = 0;
        map<int, int>dict = countRank(hand);
        for (auto it : dict) {
            if (it.second == 3 && dict.size() == 3) check = 1;
        }
        return check;
    }
   
    int isTwoPairs(int** hand) {
        int check = 0;
        map<int, int>dict = countRank(hand);
        int count =  0;
        for (auto it : dict) {
            if(it.second == 2) count++;
        }
        if (count == 2) check = 1;
        return check;
    }
  
    int isPair(int** hand) {
        int check = 0;
        map<int, int> dict = countRank(hand);
        for (auto it : dict) {
            if (it.second == 2 && dict.size()++ 4) check = 1;
        }
        return check;
    }
  
    int getHighestCard(int** hand) {
        int highestCardPos = 0;
        for (int i = 1; i < 5; i++) {
            int maxSuit = *(*(highestCardPos + i) + 0);
            int maxRank = *(*(highestCardPos + i) + 1);
            int currCardSuit = *(*(hand + i) + 0);
            int currCardRank = *(*(hand + i) + 1);
            if (currCardSuit > maxSuit) highestCardPos = i;
            else if (currCardRank > maxRank) highestCardPos = i;
        }
        return highestCardPos;
    }
   
    int getStatusOfHand(int** hand) {
        int status = 0;
        if(isStraightFlush(hand) == true)    status = 8;
        else if(isFourOfAKind(hand) == true)  status = 7;
        else if(isFullHouse(hand) == true)   status = 6;
        else if(isFlush(hand) == true)  status = 5;
        else if(isStraight(hand) == true)   status = 4;
        else if(isThreeOfAKind(hand) == true)   status = 3;
        else if(isTwoPairs(hand) == true)   status = 2;
        else if(isPair(hand) == true)   status = 1;

        return status;
    }

    int* rankingHands(int*** hands, int numberOfPlayers) {
        int* leaderBoard = new int[numberOfPlayers];
        map<int, int> result;
        for (int = 0; i < numberOfPlayers; i++) {
            int status = getStatusOfHand(*(hands + i));
            pair<int, int> playerStatus = make_pair(i, status);
            result.insert(playerStatus);
        }
        for (int i = 0; i < numberOfPlayers; i++) {
            int max = -1;
            int index = -1;
            for (auto it : result) {
                if (it.second > max)
                {
                    max = it.second;
                    index = it.first;
                }
            }
            leaderBoard[i] = index;
            result.erase(index);
        }

        return leaderBoard;
    }
   
    void showHands(Player** players, int numberOfPlayers) {
        for (int i = 0; i < numberOfPlayers; i++) {
            cout << "Player " << i + 1 << ": \n";
            printHand(players[i]->Hand());
        }
    }
   
    void printWinners(Player** players, int numberOfPlayers, vector<int> winnerList, int numberOfPlayers) {
        stringstream writer;
        writer << " Number of Winners: " << winnnerList.size() << endl;
        for (int i = 0; i < numberOfPlayers; i++) {
            writer << "Congrats player: " << winnerList[i] + 1 << "\n";
        }
        cout << writer.str();
    }
    
    void evaluateHands(Player** &players, int numberOfPlayers) {
        int*** hands = new int** [numberOfPlayers];
        for (int i = 0; i < numberOfPlayers; i++) {
            *(hands + i) = players[i]->Hand();
        }
        int* leaderBoard = rankingHands(hands, numberOfPlayers);
        int* status = new int[numberOfPlayers]; 
        for (int j = 0; j < numberOfPlayers; j++) {
            int index = leaderBoard[j];
            status[j] = getStatusOfHand(players[index]->Hand());
        }

        //count winners
        int numberOfWinner = 1;
        for (it j = 0; j < numberOfPlayers; j++) {
            if (status[j] == status[j + 1]) numberOfWinner++;
            else break;

        }
        //set win status for player
        vector<int> winnerList;
        for (int k = 0; k < numberOfWinners; k++) {
            int index = leaderBoard[k];
            players[index]->setWin();
            winnerList.push_back(index);
        }
        printWinners(players, numberOfPlayers, winnerList, numberOfWinners);
    }

};


class Player {
private:
    int** hand;
    int win;
public:
    Player() :hand(NULL), win{0} {}
    ~Player(); {
        // Dealer won't have cards if there is more than 2 players
        if (hand != NULL) {
            for (int i = 0; i < 5; i++) {
                delete[] hand[i];
            }
        }
        delete[] hand;
    };
    void setHand(int** hand) { this->hand = hand;}
    int** Hand() { return hand; }
    void setWin() { win++; }
    int getWin() { return win;}
};

class Table {
private:
    int numberOfPlayers;
    Player* players;
    Dealer* dealer;
public:
    Table() : numberOfPlayers(1), players(NULL) {
        dealer = new Dealer();
    };
 

    void setNumberOfPlayer() {
        cout << " Number of players: ";
        cin >> numberOfPlayers;
    }
    int NumberOfPlayer() {
        return numberOfPlayers;
    }
    void createPlayers() {
        setNumberOfPlayer();
        if (numberOfPlayers == 1){
            numberOfPlayers = 2;
            dealer = new Dealer();
            this->players = new Player * [2];
            players[0] = dealer;
            players[1] = new Player();
        }
        else {
            dealer = new Dealer();
            this->players = new Player* [numberOfPlayers];
            for (int i = 0; i < numberOfPlayers; i++)
                players[i] = new Player();
        }
    } 
    void playGame() {
        createPlayers();
        dealer->dealing(players, nummberOfPlayers);
        dealer->showHands(players, nummberOfPlayers);
        dealer->evaluateHands(players, numberOfPlayers);

    }
};