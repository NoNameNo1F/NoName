#include "Table.h"



void Table::setNumberOfPlayers() {
    cout << "Number of players: ";
    cin >> _numberOfPlayers;
    while (_numberOfPlayers <= 0 || _numberOfPlayers >= 11) {
        cout << " Retry a number > 0 and < 11: ";
        cin >> _numberOfPlayers;
    }
}
int Table::NumberOfPlayer() { return _numberOfPlayers; }

void Table::setPot(unsigned int _money) { _pot = _money; }

unsigned int Table::Pot() { return _pot; }


void Table::setDefaultBet(unsigned int _money) { _defaultBet = _money; }

unsigned int Table::DefaultBet() { return _defaultBet; }

void Table::setRound(int rounds) { _round = rounds; }

int Table::Round() { return _round; }

void Table::setTableDefaultBet() {
    int _defaultBet;
    cout << "Default Bet: ";
    cin >> _defaultBet;
    while (_defaultBet <= 0) {
        cout << "Retry number Default Bet > 0: ";
        cin >> _defaultBet;
    }
    if (_defaultBet > 0) {
        setDefaultBet(_defaultBet);
    }
 
        
}


void Table::createPlayers() {
    setNumberOfPlayers();
    if (_numberOfPlayers == 1) {
        cout << "\n Playing with dealer... \n";
        _numberOfPlayers = 2; //include dealer
        _dealer = new Dealer();
        this->_players = new Player * [2];
        _players[0] = _dealer;
        _players[1] = new Player();
    }
    else {
        _dealer = new Dealer();
        this->_players = new Player * [_numberOfPlayers];
        for (int i = 0; i < _numberOfPlayers; i++) {
            _players[i] = new Player();
        }
    }
}

void Table::createPlayers(vector<Player*> continuePlayersList) {
    setNumberOfPlayers();
    this->_players = new Player * [_numberOfPlayers + continuePlayersList.size()];
    if (_numberOfPlayers == 0 && continuePlayersList.size() == 1) {
        cout << "\n Playing with dealer... \n";
        *(_players + 0) = _dealer; // we already have dealer
        _numberOfPlayers++;
    }
    for (int i = 0; i < _numberOfPlayers + continuePlayersList.size(); i++) {
        if (*(_players + i) == _dealer) { continue; } // already assgin a dealer to play
        if (i < _numberOfPlayers) {
            _players[i] = new Player();
        }
        else {
            _players[i] = *(&continuePlayersList[i - _numberOfPlayers]);
            // Ex: 3 new players, 2 old players, when assign old number, i is begin from 3 to 4
            // then index to continuePlayersList is 3 - 3 = 0 for first old player, 4 - 3 = 1 for second old player
        }
    }
    _numberOfPlayers += continuePlayersList.size();
}

void Table::printPlayersName() {
    stringstream writer;
    writer << _dealer->Name() << " (dealer)\n";
    for (int i = 0; i < _numberOfPlayers; i++) {
        writer << _players[i]->Name() << " ";
    }
    writer << "entered: \n";
    cout << writer.str();
}

void Table::setMoneyPlayers() {
    for (int i = 0; i < _numberOfPlayers; i++) {
        if (_players[i]->Money() == 0) {
            int _money;
            cout << "Player " << _players[i]->Name() << ": \"How much money do you have?\": ";
            cin >> _money;
            if (_money < 1) {
                while (_money >= 1) {
                    cout << "Player " << _players[i]->Name() << ": Please insert number greater than 0!!!";
                    cin >> _money;
                }
            }
            _players[i]->setMoney(_money);
        }
    }
}

void Table::setGameRound() {
    int _round = 0;
    cout << "How many rounds do you want to play?: ";
    cin >> _round;
    if (_round < 1) {
        while (_round >= 1) {
            cout << "Please insert number greater than 0!!!";
            cin >> _round;
        }
    }
    setRound(_round);
}

string Table::printWinners(vector<int> winnerList) {
    vector<string> statusName = { "", "Pair", "TwoPairs", "ThreeOfAKind", "Straight", "Flush", "FullHouse", "FourOfAKind", "StraightFlush" };
    stringstream writer;
    writer << "Number of Winners: " << winnerList.size() << endl;
    for (int i = 0; i < winnerList.size(); i++) {
        int winMoney = _pot / winnerList.size();
        writer << "Congrats player " << _players[winnerList[i]]->Name() << " got " << statusName[_players[i]->HandStatus()] << ", win " << winMoney << "\n";
    }
    return writer.str();
}

string Table::printPlayersMoney() {
    stringstream writer;
    for (int i = 0; i < _numberOfPlayers; i++) {
        writer << "Player " << _players[i]->Name() << ": " << _players[i]->Money();
        if (_players[i]->Money() <= 0) {
            writer << " (Kicked)";
        }
        writer << endl;
    }
    return writer.str();
}

void Table::logging(vector<int> winnerList) {
    fstream file("history.txt", ios::out | ios::app);
    if (file.fail()) { cout << "Can't open file \n"; }
    else {
        file << _dealer->showHands(_players, _numberOfPlayers);
        file << printWinners(winnerList);
        file << printPlayersMoney();
    }
    file.close();
}

void Table::kickPlayers() {
    vector<Player*> storeDeletePlayers;
    for (int i = 0; i < _numberOfPlayers; i++) {
        if (_players[i]->Money() <= 0) {
            if (_players[i] == _dealer) {
                continue; // can't kick dealer
            }
            else {
                storeDeletePlayers.push_back(*(&_players[i]));
            }
        }
    }
    for (int j = 0; j < _numberOfPlayers; j++) {
        if (_players[j]->Money() > 0) {
            _players = (_players + j);
            break;
        }
    }
    _numberOfPlayers -= storeDeletePlayers.size(); // re-adjust number of players
    for (auto it : storeDeletePlayers) {
        it = NULL;
        delete it;
    }
}

vector<Player*> Table::savePlayersAndResetTable() {
    vector<Player*> continuePlayersList;
    vector<Player*> storeDeletePlayers;
    for (int i = 0; i < _numberOfPlayers; i++) {
        if (_players[i] == _dealer) continue;
        string answer;
        cout << "Player " << _players[i]->Name() << " Do you want to continue?(yes/no): ";
        cin >> answer;
        if (answer == "yes") {
            continuePlayersList.push_back(_players[i]);
        }
        else if (answer == "no") {
            storeDeletePlayers.push_back(*(&_players[i]));
        }
        else {
            cout << "Please input \"yes\" or \"no\"!!!\n";
            i--; // decrease i for players to reinput
        }
    }
    for (auto it : storeDeletePlayers) {
        it = NULL;
        delete it;
    }
    return continuePlayersList;
}

void Table::playGame() {
    vector<Player*> continuePlayersList;
    setTableDefaultBet();
    do {
        if (continuePlayersList.size() > 0) {
            createPlayers(continuePlayersList);
        }
        else createPlayers();
        printPlayersName();
        setGameRound();
        setMoneyPlayers();
        
        int _round = Round();
        _dealer->shuffleCards();
        _dealer->printCardShuffling(_dealer->deck);

        for (int i = 0; i < _round; i++) {
            cout << " \n\t\t\t\t\t\t\t\t\t\t\t --NEW ROUND-- \n";
            if (DefaultBet() > 0) {
                setPot(_dealer->setMoneyBetWithDefaultBet(_players, _numberOfPlayers, DefaultBet())); //pot will carry default
            }
            else {
                setPot(_dealer->setMoneyBet(_players, _numberOfPlayers));
            }
            _dealer->dealing(_players, _numberOfPlayers);
            _dealer->setHand(generateFakeDeck(4));
            // Test rankingHands fucntion, input number of player = 1 then dealer will have card to play
            cout << _dealer->showHands(_players, _numberOfPlayers);
            vector<int> winnerList = _dealer->evaluateHands(_players, _numberOfPlayers, _pot);
            cout << printWinners(winnerList);
            cout << printPlayersMoney();
            cout << " \n --END ROUND-- \n";
            logging(winnerList);
            kickPlayers();
            _dealer->resetCards();
            setPot(0);
            if (_numberOfPlayers == 1) break;
        }
        cout << "\n --END GAME-- \n";
        continuePlayersList = savePlayersAndResetTable();
        //delete[] * (&players);
        // free memory for pointer which point to array of players because we create a new one each game. We don't have to 
        // worry about players's memory because if we stored continue players and freed memory those who chose 
        // didn't want to continue
    } while (continuePlayersList.size() > 0);
    cout << "\n GAME ENDED DUE TO NO PLAYER LEFT ON THE TABLE\n";
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, 0);
}