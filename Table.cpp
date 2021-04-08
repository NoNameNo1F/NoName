#include "Table.h"

void Table::setNumberOfPlayers(){
    cout << "Number of players: ";
    cin >> numberOfPlayers;
}
int Table::NumberOfPlayer(){return numberOfPlayers;}

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

void Table::playGame(){
    createPlayers();
    dealer->dealing(players, numberOfPlayers);
    // dealer->setHand(generateFakeDeck(1));
    // Test rankingHands fucntion, input number of player = 1 then dealer will have card to play
    dealer->showHands(players, numberOfPlayers);
    dealer->evaluateHands(players, numberOfPlayers);
}