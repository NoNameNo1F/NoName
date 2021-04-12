#include "Table.h"

void Table::setNumberOfPlayers(){
    cout << "Number of players: ";
    cin >> numberOfPlayers;
}
int Table::NumberOfPlayer(){return numberOfPlayers;}

void Table::setPot(int money){pot = money;}

int Table::Pot() {return pot;}

void Table::setDefaultBet(int money){defaultBet = money;}

int Table::DefaultBet(){return defaultBet;}

void Table::setRound(int rounds) {round = rounds;}

int Table::Round() {return round;}

void Table::setTableDefaultBet(){
    int defaultBet;
    cout << "Default Bet: ";
    cin >> defaultBet;
    if (defaultBet > 0){
        setDefaultBet(defaultBet);
    }
}

void Table::createPlayers(){
    setNumberOfPlayers();
    if (numberOfPlayers == 1) {
        cout << "\n Playing with dealer... \n";
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

void Table::createPlayers(vector<Player*> continuePlayersList){
    setNumberOfPlayers();        
    this->players = new Player*[numberOfPlayers + continuePlayersList.size()];
    if (numberOfPlayers == 0 && continuePlayersList.size() == 1){
        cout << "\n Playing with dealer... \n";
        *(players + 0) = dealer; // we already have dealer
        numberOfPlayers++;
    }
    for (int i = 0; i < numberOfPlayers + continuePlayersList.size(); i++){
        if (*(players + i) == dealer) {continue;} // already assgin a dealer to play
        if (i < numberOfPlayers){
            players[i] = new Player();
        }
        else {
            players[i] = *(&continuePlayersList[i - numberOfPlayers]); 
            // Ex: 3 new players, 2 old players, when assign old number, i is begin from 3 to 4
            // then index to continuePlayersList is 3 - 3 = 0 for first old player, 4 - 3 = 1 for second old player
        }
    }
    numberOfPlayers += continuePlayersList.size();
}

void Table::printPlayersName(){
    stringstream writer;
    writer << dealer->Name() << " (dealer)\n";
    for (int i = 0; i < numberOfPlayers; i++){
        writer << players[i]->Name() << " ";
    }
    writer << "entered\n";
    cout << writer.str();
}

void Table::setMoneyPlayers(){
    for (int i = 0; i < numberOfPlayers; i++){
        if (players[i]->Money() == 0){
            int money;
            cout << "Player " << players[i]->Name() << ": \"How much money do you have?\": ";
            cin >> money;
            if (money < 1){
                while(money >= 1){
                    cout << "Player " << players[i]->Name() << ": Please insert number greater than 0!!!";
                    cin >> money;
                }
            }
            players[i]->setMoney(money);
        }
    }
}

void Table::setGameRound(){
    int round = 0;
    cout << "How many rounds do you want to play?: ";
    cin >> round;
    if (round < 1){
        while(round >= 1){
            cout << "Please insert number greater than 0!!!";
            cin >> round;
        }
    }
    setRound(round);
}

string Table::printWinners(vector<int> winnerList){
    vector<string> statusName = {"normal Cards", "Pair", "TwoPairs", "ThreeOfAKind", "Straight", "Flush", "FullHouse", "FourOfAKind", "StraightFlush"};
    stringstream writer;
    writer << "Number of Winners: " << winnerList.size() << endl;
    for (int i = 0; i < winnerList.size(); i++){
        int winMoney = pot / winnerList.size();
        writer << "Congrats player " << players[winnerList[i]]->Name() << " got " << statusName[players[i]->HandStatus()] << ", win " << winMoney << "\n";
    }
    return writer.str();
}

string Table::printPlayersMoney(){
    stringstream writer;
    for (int i = 0; i < numberOfPlayers; i++){
        writer << "Player " << players[i]->Name() << ": " << players[i]->Money();
        if (players[i]->Money() <= 0) {
            writer << " (Kicked)";
        }
        writer << endl;
    } 
    return writer.str();
}

void Table::logging(vector<int> winnerList){
    fstream file ("history.txt", ios::out | ios::app);
    if (file.fail()){cout << "Can't open file \n";}
    else {
        file << dealer->showHands(players, numberOfPlayers);
        file << printWinners(winnerList);
        file << printPlayersMoney();
    }
    file.close();
}

void Table::kickPlayers(){
    vector<Player*> storeDeletePlayers;
    for (int i = 0; i < numberOfPlayers; i++){
        if (players[i]->Money() <= 0){
            if (players[i] == dealer) {
                continue; // can't kick dealer
            }
            else {
                storeDeletePlayers.push_back(*(&players[i]));
            }
        }
    }
    for (int j = 0; j < numberOfPlayers; j++){
        if (players[j]->Money() > 0){
            players = (players + j);
            break;
        }
    }
    numberOfPlayers -= storeDeletePlayers.size(); // re-adjust number of players
    for (auto it : storeDeletePlayers){
        it = NULL;
        delete it;
    }
}

vector<Player*> Table::savePlayersAndResetTable(){
    vector<Player*> continuePlayersList;
    vector<Player*> storeDeletePlayers;
    for(int i = 0; i < numberOfPlayers; i++){
        if (players[i] == dealer) continue;
        string answer;
        cout << "Player " << players[i]->Name() << " Do you want to continue?(yes/no): ";
        cin >> answer;
        if (answer == "yes"){
            continuePlayersList.push_back(players[i]);
        }
        else if (answer == "no"){
            storeDeletePlayers.push_back(*(&players[i]));
        }
        else {
            cout << "Please input \"yes\" or \"no\"!!!\n";
            i--; // decrease i for players to reinput
        }
    }
    for (auto it : storeDeletePlayers){
        it = NULL;
        delete it;
    }
    return continuePlayersList;
}

void Table::playGame(){
    vector<Player*> continuePlayersList;
    setTableDefaultBet();
    do {
        if (continuePlayersList.size() > 0){
            createPlayers(continuePlayersList);
        }
        else createPlayers();
        printPlayersName();
        setGameRound();
        setMoneyPlayers();
        int round = Round();
        for (int i = 0; i < round; i++){
            cout << " \n --NEW ROUND-- \n";
            if (DefaultBet() > 0){
                setPot(dealer->setMoneyBetWithDefaultBet(players, numberOfPlayers, DefaultBet())); //pot will carry default
            }
            else {
                setPot(dealer->setMoneyBet(players, numberOfPlayers));
            }
            dealer->dealing(players, numberOfPlayers);
            // dealer->setHand(generateFakeDeck(3));
            // Test rankingHands fucntion, input number of player = 1 then dealer will have card to play
            cout << dealer->showHands(players, numberOfPlayers);
            vector<int> winnerList = dealer->evaluateHands(players, numberOfPlayers, pot);
            cout << printWinners(winnerList);
            cout << printPlayersMoney();
            cout << " \n --END ROUND-- \n";
            logging(winnerList);
            kickPlayers();
            dealer->resetCards();
            setPot(0);
            if (numberOfPlayers == 1) break;
        }
        cout << "\n --END GAME-- \n";
        continuePlayersList = savePlayersAndResetTable();
        // delete[] *(&players); 
        // free memory for pointer which point to array of players because we create a new one each game. We don't have to 
        // worry about players's memory because if we stored continue players and freed memory those who chose 
        // didn't want to continue
    }
    while(continuePlayersList.size() > 0);
    cout << "\n GAME ENDED DUE TO NO PLAYER LEFT ON THE TABLE\n";
}