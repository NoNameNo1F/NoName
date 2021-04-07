#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
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

class Player{
private:
    int** hand;
    int win;
public:
    Player() : hand(NULL), win(0) {}
    // ~Player(){ // for later fix
    //     for (int i = 0; i < 5; i++){
    //         delete[] hand[i];
    //     }
    //     delete[] hand;
    // };

    void setHand(int** hand){ this->hand = hand;}
    int** Hand(){return hand;}
    void setWin(){win++;}
    int getWin(){return win;}
};

class Dealer : public Player { //dealer also a player
private:
    int deck[SUITS][FACES];
public:
    Random shuffleBoard;
public:
    Dealer() : shuffleBoard(Random::instance()){
        for (int i = 0; i < SUITS; i++){ // generate array fill with zero
            for (int j = 0; j < FACES; j++){
                deck[i][j] = -1;
            }
        }
    }
    virtual ~Dealer(){}

    void shuffleCards(int (&deck)[SUITS][FACES]){
        for(auto i = 1; i <= 52; i++){
            int ranSuits, ranFaces;
            do{
            ranSuits = shuffleBoard.next(0, 4);
            ranFaces = shuffleBoard.next(0, 12);
            }
            while(deck[ranSuits][ranFaces] != -1);
            deck[ranSuits][ranFaces] = i;
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
        string Suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
        stringstream writer; 
        for (int num = 0; num < 52; num++){
            pair <int, int> cardName = searchCardPos(deck, num); 
            writer << "(" << Suits[cardName.first] << ", " << Ranks[cardName.second] << ")\n"; 
        }
        cout << writer.str();
    }

    int** dealingForHand(int deck[SUITS][FACES], int turn = 1, int numberOfPlayers = 2){ // turn to deal cards, default is there is only one player on table and a dealer
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

    int*** dealingForHands(int deck[SUITS][FACES], int numberOfPlayers = 3){
        int*** hands = new int**[numberOfPlayers];
        for (int i = 0; i <= numberOfPlayers; i++){
            *(hands + i) = dealingForHand(deck, i + 1, numberOfPlayers); // plus one for turn 
        }
        return hands;
    }

    void dealing(Player** &players, int numberOfPlayers){
        shuffleCards(this->deck); //shuffle card

        int*** hands = dealingForHands(deck, numberOfPlayers);

        bool storeDeck[numberOfPlayers] = {false};
        for (int i = 0; i < numberOfPlayers; i++){
            int deckPos;
            do{
                deckPos = this->shuffleBoard.next(numberOfPlayers); // player will receive random deck
            }while(storeDeck[deckPos] == true);
            storeDeck[deckPos] = true;
            int** hand = *(hands + deckPos);
            players[i]->setHand(hand); //player get cards

            hand = NULL; // maybe memory leak ???
            delete hand;
        } 
    }

    void printHand(int** hand){
        string Suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
        stringstream writer;
        for (int i = 0; i < 5; i++){
            int suitIndex = *(*(hand + i) + 0);
            int rankIndex = *(*(hand + i) + 1);
            writer << "(" << Suits[suitIndex] /*suit*/ << ", " << Ranks[rankIndex] /*rank*/ << ")\n";
        }
        cout << writer.str();
    }

    map<int, int> countRank(int** hand){
        map<int, int> dict;
        for(int i = 0; i < 5; i++){
            int rank = *( *(hand + i) + 1 );
            if (dict.find(rank) == dict.end()){
                pair<int, int> obj = make_pair(rank, 1); // if dict doesn't have that rank, add that rank with num is 1
                dict.insert(obj);
            }
            else{
                dict[rank] += 1; // if found in dict then increase number
            }
        }
        return dict;
    }

    bool isFourOfAKind(int** hand){
        bool check = false;
        map<int, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 4 && dict.size() == 2) check = true;
            //two type of ranks, but one type has 4 cards then others will be one different rank
        }
        return check;
    }

    bool isFullHouse(int** hand){
        bool check = false;
        map<int, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 3 && dict.size() == 2) check = true; 
            //two type of ranks, but one type has 3 cards then others will be one different rank has 2 cards same rank
        }
        return check;
    }

    bool isFlush(int** hand){
        bool check = false;
        int suit = * ( *(hand + 0) + 0 ); //get suit of first card to check
        for (int i = 1; i < 5; i++) { // don't have to chekc first suit
            if (suit != * ( *(hand + i) + 0 )){
                check = false;
                break;
            }
        }
        return check;
    }

    bool isStraight(int** hand){
        bool check = false;
        vector<int> arr; 
        for (int i = 0; i < 5; i++){
            arr.push_back(* ( *(hand + i) + 1) );
        }
        sort(arr.begin(), arr.end());
        for (int i = 0; i < 5; i++){
            if (arr[i + 1] - arr[i] != 1) {
                check = false;
                break;
            }
        }
        return check;
    }

    bool isStraigntFLush (int** hand){
        return isFlush(hand) && isStraight(hand);
    }

    bool isThreeOfAKind(int** hand){
        bool check = false;
        map<int, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 3 && dict.size() == 3) check = true; 
            //three type of ranks, but one type has 3 cards then others will be two different ranks
        }
        return check;
    }

    bool isTwoPairs(int** hand){
        bool check = false;
        map<int, int> dict = countRank(hand);
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
        map<int, int> dict = countRank(hand);
        for (auto it : dict){
            if (it.second == 2 && dict.size() == 4) check = true; 
            //four type of ranks, but one type has 2 cards then others will be three different ranks
        }
        return check;
    }

    int getHighestCard(int** hand){
        int highestCardPos = 0;
        for (int i = 1; i < 5; i++){
            int maxSuit = * ( *(hand + highestCardPos) + 0);
            int maxRank = * ( *(hand + highestCardPos) + 1);
            int currCardSuit = * ( *(hand + i) + 0);
            int currCardRank = * ( *(hand + i) + 1);
            if (currCardSuit > maxSuit) {
                highestCardPos = i;
            }
            else if (currCardRank > maxRank){
                highestCardPos = i;
            }
        }
        return highestCardPos;
    }

    int getStatusOfHand(int** hand){
        /*
        1. Pair
        2. TwoPairs
        3. ThreeOfAKind
        4. Straight
        5. Flush
        6. FullHouse
        7. FourOfAKind
        8. StraightFlush
        0. None of above
        */
       int status = 0;
       if (isStraigntFLush(hand) == true){
           status = 8;
       }
       else if (isFourOfAKind(hand) == true){
           status = 7;
       }
       else if (isFullHouse(hand) == true){
           status = 6;
       }
       else if (isFlush(hand) == true){
           status = 5;
       }
       else if (isStraight(hand) == true){
           status = 4;
       }
       else if (isThreeOfAKind(hand) == true){
           status = 3;
       }
       else if (isTwoPairs(hand) == true){
           status = 2;
       }
       else if (isPair(hand) == true){
           status = 1;
       }
       return status;
    }

    int* rankingHands(int*** hands, int numberOfPlayers){
        int* leaderBoard = new int [numberOfPlayers];
        map<int, int> result;
        for (int i = 0; i < numberOfPlayers; i++){
            int status = getStatusOfHand(*(hands + i));
            pair<int, int> playerStatus = make_pair(i, status);
            result.insert(playerStatus);
        }
        
        /// INTERCHANGE SORT
        // We will pop out max element instead of swap it with first element

        for (int i = 0; i < numberOfPlayers; i++){ // because we pop out elements so we have to run i to n instead of i to n-1
            int max = -1; //get this status of first element of result
            int index = -1;
            for (auto it : result){
                if (it.second > max) {
                    max = it.second;
                    index = it.first;
                }
            }
            leaderBoard[i] = index;
            result.erase(index);
        }
        ///

        return leaderBoard;
    }

    void showHands(Player** players, int numberOfPlayers){
        for (int i = 0; i < numberOfPlayers; i++){
            cout << "Player " << i + 1 << ": \n";
            printHand(players[i]->Hand());
        }
    }

    void printWinners(Player** players, int numberOfPlayers, vector<int> winnerList, int numberOfWinners){
        stringstream writer;
        writer << "Number of Winners: " << winnerList.size() << endl;
        for (int i = 0; i < numberOfWinners; i++){
            writer << "Congrats player " << winnerList[i] + 1 << "\n";
        }
        cout << writer.str();
    }

    void evaluateHands(Player** &players, int numberOfPlayers){
        int*** hands = new int**[numberOfPlayers];
        for (int i = 0; i < numberOfPlayers; i++){
            *(hands + i) = players[i]->Hand(); 
        }
        int* leaderBoard = rankingHands(hands, numberOfPlayers);

        int* status = new int [numberOfPlayers];// get status to check equal to split pot
        for (int j = 0; j < numberOfPlayers; j++){
            int index = leaderBoard[j];
            status[j] = getStatusOfHand(players[index]->Hand());
            // cout << j + 1 << ":" << status[j] << "|"; 
            // for check status
        }

        //count winners
        int numberOfWinners = 1;
        for (int j = 0; j < numberOfPlayers - 1; j++){
            if (status[j] == status[j + 1]) numberOfWinners++;
            else break;
        }

        // set win status for player
        vector<int> winnerList;
        for(int k = 0; k < numberOfWinners; k++){
            int index = leaderBoard[k];
            players[index]->setWin();
            winnerList.push_back(index);
        }

        printWinners(players, numberOfPlayers, winnerList, numberOfWinners);
    }

};

class Table{
private:
    int numberOfPlayers;
    Player** players;
    Dealer* dealer;
public:
    Table() : numberOfPlayers(1), players(NULL) {
        dealer = new Dealer();
    }
    // ~Table(){
    //     for (int i = 0; i < numberOfPlayers; i++){
    //         delete (players + i);
    //         delete[] players;
    //         delete dealer;
    //     }
    // }

    void setNumberOfPlayers(){
        cout << "Number of players: ";
        cin >> numberOfPlayers;
    }
    int NumberOfPlayer(){return numberOfPlayers;}

    void createPlayers(){
        setNumberOfPlayers();
        if (numberOfPlayers == 1) {
            numberOfPlayers = 2; //include dealer
            dealer = new Dealer();
            this->players = new Player*[2];
            players[0] = dealer; 
            players[1] = new Player();
        }
        else {
            dealer = new Dealer();          
            this->players = new Player*[numberOfPlayers];
            for (int i = 0; i < numberOfPlayers; i++){
                players[i] = new Player();
            }
        }
    }

    void playGame(){
        createPlayers();
        dealer->dealing(players, numberOfPlayers);
        dealer->showHands(players, numberOfPlayers);
        dealer->evaluateHands(players, numberOfPlayers);
    }
};  

int main(){
    Table t1;
    t1.playGame();
    return 0;
}