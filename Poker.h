
#ifndef _POKER_H_
#define _POKER_H_
void ChooseMenu();
int Menu();
void LoadingMenu();

// Game play for one Player
void printCardsShuffling(int deck[][], char* suits[], char* faces[]);

int** dealingForHand(int deck[SUITS][FACES]);

void printHand(int** hand, char* suits[], char* faces[]);

int** createHandTest(int deck[SUITS][FACES]), int a[]);

int isFourOfAKind(int** hand);

int isFullHouse(int** hand);

int isFlush(int** hand);

int isStraight(int** hand);

int isStraightFlush(int** hand);

int isThreeOfAKind(int** hand);

int isTwoPairs(int** hand);

int isPair(int** hand);

int getHighestCard(int** hand);

// Game Play n Player
int*** dealingForHands(int deck[SUITS][FACES], int n);

int getStatusOfHand(int** hand);

int* rankingHands(int*** hands, int n);

int* evaluateHands(...);

/*3.? Write a poker game for dealer side.The dealer also receives five cards,
yet he may additionally draw one, two or three cards to replace some old
cards(new cards are continuously drawn from the current deck).
The replacement of one, two, or three cards from the set of five cards can
be decided following(1) random replacement or (2) replace to get better
situation.

4.??? Write a program that lets a player and the dealer compete with each
other.The player may decide whether to additionally draw one, two or
three cards or not.

5.???? Replace the decision making algorithm of the dealer to have different
game levels(easy, medium and hard)*/
#endif