#include "Player.h"

/// Player

Player::Player(const Player& other) {
    _win = other._win;
    _money = other._money;
    _name = other._name;
    for (int i = 0; i < 5; i++) {
        _hand[i] = other._hand[i];
    }
}

Player& Player::operator=(const Player& other) {
    _win = other._win;
    _money = other._money;
    _name = other._name;
    for (int i = 0; i < 5; i++) {
        _hand[i] = other._hand[i];
    }
    return *this;
}

bool Player::operator== (const Player& other) {
    bool check = true;
    if (_win != other._win) check = false;
    if (_money != other._money) check = false;
    if (_name != other._name) check = false;
    for (int i = 0; i < 5; i++) {
        if (_hand[i] = other._hand[i]) check = false;
    }
    return check;
}

void Player::setHand(int** _hand) { this->_hand = _hand; }

int** Player::Hand() { return _hand; }

void Player::setWin() { _win++; }

int Player::getWin() { return _win; }

void Player::setMoney(unsigned int _money) { this->_money = _money; }

unsigned int Player::Money() { return _money; }

string Player::Name() { return _name; }

int Player::HandStatus() { return _handStatus; }

void Player::setHandStatus(int status) { _handStatus = status; }

///Dealer

int Dealer::setMoneyBet(Player** _players, int _numberOfPlayers) {
    int _pot = 0;
    for (int i = 0; i < _numberOfPlayers; i++) {
        if (_players[i] == this) continue; // dealer will bet the same as player
        unsigned int _money;
        cout << "Player " << _players[i]->Name() << ": How much money do you want to bet?: ";
        if (_players[i]->Money() > 0) cout << "(You are having " << _players[i]->Money() << ") ";
        cin >> _money;
        int playerMoney = _players[i]->Money();
        _players[i]->setMoney(playerMoney - _money);
        _pot += _money;
        if (_players[0] == this) {
            unsigned int playerMoney = _players[0]->Money(); // set dealer's money
            _players[0]->setMoney(playerMoney - _money);
            _pot += _money;
        }
    }
    return _pot;
}

int Dealer::setMoneyBetWithDefaultBet(Player** _players, int _numberOfPlayers, int _defaultBet) {
    int _pot = 0;
    for (int i = 0; i < _numberOfPlayers; i++) {
        if (_players[i] == this) continue; // dealer will bet the same as player
        unsigned int playerMoney = _players[i]->Money();
        _players[i]->setMoney(playerMoney - _defaultBet);
        _pot += _defaultBet;
        if (_players[0] == this) {
            unsigned int playerMoney = _players[0]->Money(); // set dealer's money
            _players[0]->setMoney(playerMoney - _defaultBet);
            _pot += _defaultBet;
        }
    }
    return _pot;
}

void Dealer::shuffleCards() {
    for (auto i = 1; i <= 52; i++) {
        int ranSuits, ranFaces;
        do {
            ranSuits = shuffleBoard.next(0, 4);
            ranFaces = shuffleBoard.next(0, 12);
        } while (deck[ranSuits][ranFaces] != -1);
        deck[ranSuits][ranFaces] = i;
    }
}

void Dealer::resetCards() {
    for (int i = 0; i < SUITS; i++) { // generate array fill with zero
        for (int j = 0; j < FACES; j++) {
            deck[i][j] = -1;
        }
    }
}

pair<int, int> Dealer::searchCardPos(int deck[SUITS][FACES], int num) {
    pair<int, int> pos;
    for (auto i = 0; i < SUITS; i++) {
        for (auto j = 0; j < FACES; j++) {
            if (deck[i][j] == num) {
                pos.first = i; // SUIT
                pos.second = j; // FACE
            }
        }
    }
    return pos;
}
void Dealer::printCardShuffling(int deck[SUITS][FACES]) {
    string Suits[SUITS] = { "Co", "Ro", "Chuon", "Bich" };
    string Ranks[FACES] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    stringstream writer;
    for (int num = 0; num < 52; num++) {

        pair <int, int> cardName = searchCardPos(deck, num);
        writer <<"La thu " << num + 1<<  " (" << Suits[cardName.first] << ", " << Ranks[cardName.second] << ")\n";
    }
    cout << writer.str();
}
int** Dealer::dealingForHand(int deck[SUITS][FACES], int turn, int _numberOfPlayers) { // turn to deal cards, default is there is only one player on table and a dealer
    int** _hand = new int* [5]; // 5 card per player
    for (int i = 0; i < 5; i++) {
        *(_hand + i) = new int[2]; // first col present row of the matrix, second one present column of the matrix 
    }
    //assign cards
    int pos = turn;
    for (int j = 0; j < 5; j++) { // hand will have 5 cards
        pair <int, int> cardName = searchCardPos(deck, pos);
        int* card = *(_hand + j); // present card details
        *(card + 0) = cardName.first; // suit
        *(card + 1) = cardName.second; // faces
        // free memory of temp card variable
        card = NULL;
        delete[] card;
        pos += _numberOfPlayers; // Ex: 1, 5, 9, 13, 17
    }
    return _hand;
}
int*** Dealer::dealingForHands(int deck[SUITS][FACES], int _numberOfPlayers) {
    int*** hands = new int** [_numberOfPlayers];
    for (int i = 0; i <= _numberOfPlayers; i++) {
        *(hands + i) = dealingForHand(deck, i + 1, _numberOfPlayers); // plus one for turn 
    }
    return hands;
}
void Dealer::dealing(Player**& _players, int _numberOfPlayers) {
    shuffleCards(); //shuffle card
    int*** hands = dealingForHands(deck, _numberOfPlayers);
    vector<bool> storeDeck(_numberOfPlayers, false );
    for (int i = 0; i < _numberOfPlayers; i++) {
        int deckPos;
        do {
            deckPos = this->shuffleBoard.next(_numberOfPlayers); // player will receive random deck
        } while (storeDeck[deckPos] == true);
        storeDeck[deckPos] = true;
        int** _hand = *(hands + deckPos);
        _players[i]->setHand(_hand); //player get cards
        _hand = NULL; // maybe memory leak ???
        delete _hand;
    }
}
string Dealer::printHand(int** _hand) {
    string Suits[SUITS] = { "Co", "Ro", "Chuon", "Bich" };
    string Ranks[FACES] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    stringstream writer;
    for (int i = 0; i < 5; i++) {
        int suitIndex = *(*(_hand + i) + 0);
        int rankIndex = *(*(_hand + i) + 1);
        writer << "|(" << Suits[suitIndex] /*suit*/ << ", " << Ranks[rankIndex] /*rank*/ << ")|";
    }
    writer << endl;
    return writer.str();
}

string Dealer::showHands(Player** _players, int _numberOfPlayers) {
    stringstream writer;
    for (int i = 0; i < _numberOfPlayers; i++) {
        writer << "Player " << _players[i]->Name() << ": \n";
        writer << printHand(_players[i]->Hand());
    }
    return writer.str();
}

map<int, int> Dealer::countRank(int** _hand) {
    map<int, int> dict;
    for (int i = 0; i < 5; i++) {
        int rank = *(*(_hand + i) + 1);
        if (dict.find(rank) == dict.end()) {
            pair<int, int> obj = make_pair(rank, 1); // if dict doesn't have that rank, add that rank with num is 1
            dict.insert(obj);
        }
        else {
            dict[rank] += 1; // if found in dict then increase number
        }
    }
    return dict;
}
bool Dealer::isFourOfAKind(int** _hand) {
    bool check = false;
    map<int, int> dict = countRank(_hand);
    for (auto it : dict) {
        if (it.first == 4 && dict.size() == 2) check = true;
        //two type of ranks, but one type has 4 cards then others will be one different rank
    }
    return check;
}
bool Dealer::isFullHouse(int** _hand) {
    bool check = false;
    map<int, int> dict = countRank(_hand);
    for (auto it : dict) {
        if (it.first == 3 && dict.size() == 2) check = true;
        //two type of ranks, but one type has 3 cards then others will be one different rank has 2 cards same rank
    }
    return check;
}
bool Dealer::isFlush(int** _hand) {
    bool check = false;
    int count = 0;
    int suit = *(*(_hand + 0) + 0); //get suit of first card to check
    for (int i = 1; i < 5; i++) { // don't have to chekc first suit
        if (suit == *(*(_hand + i) + 0)) {
            count++;
        }
        else break;
    }
    if (count == 4) check = true;
    return check;
}
bool Dealer::isStraight(int** _hand) {
    bool check = false;
    int count = 0;
    vector<int> arr;
    for (int i = 0; i < 5; i++) {
        arr.push_back(*(*(_hand + i) + 1));
    }
    sort(arr.begin(), arr.end());
    for (int i = 0; i < 5; i++) {
        if (arr[i + 1] - arr[i] == 1) {
            count++;
        }
        else break;
    }
    if (count == 4) check = true;
    return check;
}
bool Dealer::isStraightFLush(int** _hand) {
    return isFlush(_hand) && isStraight(_hand);
}
bool Dealer::isThreeOfAKind(int** _hand) {
    bool check = false;
    map<int, int> dict = countRank(_hand);
    for (auto it : dict) {
        if (it.first == 3 && dict.size() == 3) check = true;
        //three type of ranks, but one type has 3 cards then others will be two different ranks
    }
    return check;
}
bool Dealer::isTwoPairs(int** _hand) {
    bool check = false;
    map<int, int> dict = countRank(_hand);
    int count = 0;
    for (auto it : dict) {
        if (it.first == 2) count++;
    }
    if (count == 2) check = true;
    // if count equal 2 then there are 2 pairs of the same rank
    return check;
}
bool Dealer::isPair(int** _hand) {
    bool check = false;
    map<int, int> dict = countRank(_hand);
    for (auto it : dict) {
        if (it.first == 2 && dict.size() == 4) check = true;
        //four type of ranks, but one type has 2 cards then others will be three different ranks
    }
    return check;
}
int Dealer::getHighestCard(int** _hand) {
    int highestCardPos = 0;
    for (int i = 1; i < 5; i++) {
        int maxSuit = *(*(_hand + highestCardPos) + 0);
        int maxRank = *(*(_hand + highestCardPos) + 1);
        int currCardSuit = *(*(_hand + i) + 0);
        int currCardRank = *(*(_hand + i) + 1);
        if (currCardSuit > maxSuit) {
            highestCardPos = i;
        }
        else if (currCardRank > maxRank) {
            highestCardPos = i;
        }
    }
    return highestCardPos;
}
int Dealer::getStatusOfHand(int** _hand) {
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
    if (isStraightFLush(_hand) == true) {
        status = 8;
    }
    else if (isFourOfAKind(_hand) == true) {
        status = 7;
    }
    else if (isFullHouse(_hand) == true) {
        status = 6;
    }
    else if (isFlush(_hand) == true) {
        status = 5;
    }
    else if (isStraight(_hand) == true) {
        status = 4;
    }
    else if (isThreeOfAKind(_hand) == true) {
        status = 3;
    }
    else if (isTwoPairs(_hand) == true) {
        status = 2;
    }
    else if (isPair(_hand) == true) {
        status = 1;
    }
    return status;
}
int* Dealer::rankingHands(int*** hands, int _numberOfPlayers) {
    int* leaderBoard = new int[_numberOfPlayers];
    map<int, int> result;
    for (int i = 0; i < _numberOfPlayers; i++) {
        int status = getStatusOfHand(*(hands + i));
        pair<int, int> playerStatus = make_pair(i, status);

         //cout << i << " " << status << "\n";


        result.insert(playerStatus);
    }

    /// INTERCHANGE SORT
    // We will pop out max element instead of swap it with first element
    for (int i = 0; i < _numberOfPlayers; i++) { // because we pop out elements so we have to run i to n instead of i to n-1
        int max = -1; //get this status of first element of result
        int index = -1;
        for (auto it : result) {
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

vector<int> Dealer::evaluateHands(Player**& _players, int _numberOfPlayers, unsigned int _pot) {
    int*** hands = new int** [_numberOfPlayers];
    for (int i = 0; i < _numberOfPlayers; i++) {
        *(hands + i) = _players[i]->Hand();
    }
    int* leaderBoard = rankingHands(hands, _numberOfPlayers);
    for (int j = 0; j < _numberOfPlayers; j++) {
        int status = getStatusOfHand(_players[j]->Hand());
        _players[j]->setHandStatus(status);

        //cout << j << " " << status << " - " << players[j]->HandStatus() << "\n";
        //for check status
    }
    //count winners
    int numberOfWinners = 1;
    for (int j = 0; j < _numberOfPlayers - 1; j++) { // compare numberOfPlayers - 1 pairs
        if (_players[leaderBoard[j]]->HandStatus() == _players[leaderBoard[j + 1]]->HandStatus()) numberOfWinners++;
        else break;
    }
    // set win status for player
    vector<int> winnerList;
    unsigned int winMoney = _pot / numberOfWinners;
    for (int k = 0; k < numberOfWinners; k++) {
        int index = leaderBoard[k];
        _players[index]->setWin();
        unsigned int playerMoney = _players[index]->Money();
        _players[index]->setMoney(playerMoney + winMoney);
        winnerList.push_back(index);
    }

    return winnerList;
}