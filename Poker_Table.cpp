#include "Poker_Table.h"

void Table::setNumberOfPlayers(){
    cout << "Number of players: ";
    cin >> numberOfPlayers;
}
int Table::NumberOfPlayer(){return numberOfPlayers;}

void Table::setPot(int money){pot = money;}

int Table::Pot() {return pot;}

void Table::setRound(int rounds) {round = rounds;}

int Table::Round() {return round;}

void Table::createPlayers(){
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

void Table::printPlayersName(){
    stringstream writer;
    for (int i = 0; i < numberOfPlayers; i++){
        writer << players[i]->Name() << " ";
    }
    writer << "entered\n";
    cout << writer.str();
}

void Table::setMoneyPlayers(){
    for (int i = 0; i < numberOfPlayers; i++){
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

void Table::kickPlayers(){
    for (int i = 0; i < numberOfPlayers; i++){
        if (players[i]->Money() <= 0){
            Player* temp = players[i];
            if (*players == *(players + i)){
                players = (players + i + 1);
            }
            temp = NULL;
            delete temp;
            numberOfPlayers--; // readjust number of players
        }
    }
}

void Table::playGame(){
    createPlayers();
    printPlayersName();
    setGameRound();
    setMoneyPlayers();
    int round = Round();
    for (int i = 0; i < round; i++){
        setPot(dealer->betMoneyPlayers(players, numberOfPlayers));
        dealer->dealing(players, numberOfPlayers);
        // dealer->setHand(generateFakeDeck(1));
        // Test rankingHands fucntion, input number of player = 1 then dealer will have card to play
        dealer->showHands(players, numberOfPlayers);
        dealer->evaluateHands(players, numberOfPlayers, pot);
        kickPlayers();
        dealer->resetCards();
        setPot(0);
    }
}
