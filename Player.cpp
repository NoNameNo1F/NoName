#include "Player.h"

/// Player

Player::Player(const Player& other){
    win = other.win;
    money = other.money;
    name = other.name;
    for (int i = 0; i < 5; i++){
        hand[i] = other.hand[i];
    }
}

Player& Player::operator=(const Player& other){
    win = other.win;
    money = other.money;
    name = other.name;
    for (int i = 0; i < 5; i++){
        hand[i] = other.hand[i];
    }
    return *this;
}

bool Player::operator== (const Player& other){
    bool check = true;
    if (win != other.win) check = false;
    if (money != other.money) check = false;
    if (name != other.name) check = false;
    for (int i = 0; i < 5; i++){
        if (hand[i] = other.hand[i]) check = false;
    }
    return check;
}

void Player::setHand(int** hand){ this->hand = hand;}

int** Player::Hand(){return hand;}

void Player::setWin(){win++;}

int Player::getWin(){return win;}

void Player:: setMoney(int money){this->money = money;}

int Player::Money(){return money;}

string Player::Name(){return name;}

int Player::HandStatus() {return handStatus;}
    
void Player::setHandStatus(int status){handStatus = status;}

///Dealer

int Dealer::betMoneyPlayers(Player** players, int numberOfPlayers){
    int pot = 0;
    for (int i = 0; i < numberOfPlayers; i++){
        int money;
        cout << "Player " << players[i]->Name() << ": How much money do you want to bet?: ";
        if (players[i]->Money() > 0) cout << "(You are having " <<  players[i]->Money() << ") ";
        cin >> money;
        int playerMoney = players[i]->Money();
        players[i]->setMoney(playerMoney - money);
        pot += money;
    }
    return pot;
}

void Dealer::shuffleCards(){
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

void Dealer::resetCards(){
    for (int i = 0; i < SUITS; i++){ // generate array fill with zero
        for (int j = 0; j < FACES; j++){
            deck[i][j] = -1;
        }
    }
}

pair<int, int> Dealer::searchCardPos(int deck[SUITS][FACES], int num){
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
void Dealer::printCardShuffling(int deck[SUITS][FACES]){   
    string Suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    stringstream writer; 
    for (int num = 0; num < 52; num++){
        pair <int, int> cardName = searchCardPos(deck, num); 
        writer << "(" << Suits[cardName.first] << ", " << Ranks[cardName.second] << ")\n"; 
    }
    cout << writer.str();
}
int** Dealer::dealingForHand(int deck[SUITS][FACES], int turn, int numberOfPlayers){ // turn to deal cards, default is there is only one player on table and a dealer
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
int*** Dealer::dealingForHands(int deck[SUITS][FACES], int numberOfPlayers){
    int*** hands = new int**[numberOfPlayers];
    for (int i = 0; i <= numberOfPlayers; i++){
        *(hands + i) = dealingForHand(deck, i + 1, numberOfPlayers); // plus one for turn 
    }
    return hands;
}
void Dealer::dealing(Player** &players, int numberOfPlayers){
    shuffleCards(); //shuffle card
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
string Dealer::printHand(int** hand){
    string Suits[SUITS] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string Ranks[FACES] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    stringstream writer;
    for (int i = 0; i < 5; i++){
        int suitIndex = *(*(hand + i) + 0);
        int rankIndex = *(*(hand + i) + 1);
        writer << "|(" << Suits[suitIndex] /*suit*/ << ", " << Ranks[rankIndex] /*rank*/ << ")|";      
    }
    writer << endl;
    return writer.str();
}

string Dealer::showHands(Player** players, int numberOfPlayers){
    stringstream writer;
    for (int i = 0; i < numberOfPlayers; i++){
        writer << "Player " << players[i]->Name() << ": \n";
        writer << printHand(players[i]->Hand());
    }
    return writer.str();
}

map<int, int> Dealer::countRank(int** hand){
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
bool Dealer::isFourOfAKind(int** hand){
    bool check = false;
    map<int, int> dict = countRank(hand);
    for (auto it : dict){
        if (it.second == 4 && dict.size() == 2) check = true;
        //two type of ranks, but one type has 4 cards then others will be one different rank
    }
    return check;
}
bool Dealer::isFullHouse(int** hand){
    bool check = false;
    map<int, int> dict = countRank(hand);
    for (auto it : dict){
        if (it.second == 3 && dict.size() == 2) check = true; 
        //two type of ranks, but one type has 3 cards then others will be one different rank has 2 cards same rank
    }
    return check;
}
bool Dealer::isFlush(int** hand){
    bool check = false;
    int count = 0;
    int suit = * ( *(hand + 0) + 0 ); //get suit of first card to check
    for (int i = 1; i < 5; i++) { // don't have to chekc first suit
        if (suit == * ( *(hand + i) + 0 )){
            count++;
        }
        else break;
    }
    if (count == 4) check = true;
    return check;
}
bool Dealer::isStraight(int** hand){
    bool check = false;
    int count = 0;
    vector<int> arr; 
    for (int i = 0; i < 5; i++){
        arr.push_back(* ( *(hand + i) + 1) );
    }
    sort(arr.begin(), arr.end());
    for (int i = 0; i < 5; i++){
        if (arr[i + 1] - arr[i] == 1) {
            count++;
        }
        else break;
    }
    if (count == 4) check = true;
    return check;
}
bool Dealer::isStraigntFLush (int** hand){
    return isFlush(hand) && isStraight(hand);
}
bool Dealer::isThreeOfAKind(int** hand){
    bool check = false;
    map<int, int> dict = countRank(hand);
    for (auto it : dict){
        if (it.second == 3 && dict.size() == 3) check = true; 
        //three type of ranks, but one type has 3 cards then others will be two different ranks
    }
    return check;
}
bool Dealer::isTwoPairs(int** hand){
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
bool Dealer::isPair(int** hand){
    bool check = false;
    map<int, int> dict = countRank(hand);
    for (auto it : dict){
        if (it.second == 2 && dict.size() == 4) check = true; 
        //four type of ranks, but one type has 2 cards then others will be three different ranks
    }
    return check;
}
int Dealer::getHighestCard(int** hand){
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
int Dealer::getStatusOfHand(int** hand){
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
int* Dealer::rankingHands(int*** hands, int numberOfPlayers){
    int* leaderBoard = new int [numberOfPlayers];
    map<int, int> result;
    for (int i = 0; i < numberOfPlayers; i++){
        int status = getStatusOfHand(*(hands + i));
        pair<int, int> playerStatus = make_pair(i, status);

        // cout << i << " " << status << "\n";
        

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

vector<int> Dealer::evaluateHands(Player** &players, int numberOfPlayers, int pot){
    int*** hands = new int**[numberOfPlayers];
    for (int i = 0; i < numberOfPlayers; i++){
        *(hands + i) = players[i]->Hand(); 
    }
    int* leaderBoard = rankingHands(hands, numberOfPlayers);
    for (int j = 0; j < numberOfPlayers; j++){
        int status = getStatusOfHand(players[j]->Hand());
        players[j]->setHandStatus(status);

        // cout << j << " " << status << " - " << players[j]->HandStatus() << "\n";
        // for check status
    }
    //count winners
    int numberOfWinners = 1;
    for (int j = 0; j < numberOfPlayers - 1; j++){ // compare numberOfPlayers - 1 pairs
        if (players[leaderBoard[j]]->HandStatus() == players[leaderBoard[j + 1]]->HandStatus()) numberOfWinners++;
        else break;
    }
    // set win status for player
    vector<int> winnerList;
    int winMoney = pot / numberOfWinners;
    for(int k = 0; k < numberOfWinners; k++){
        int index = leaderBoard[k];
        players[index]->setWin();
        int playerMoney = players[index]->Money();
        players[index]->setMoney(playerMoney + winMoney);
        winnerList.push_back(index);
    }

    return winnerList;
}