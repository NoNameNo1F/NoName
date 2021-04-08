#include "FakeDeck.h"

void generatePair(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 2; hand[1][1] = 2;

    hand[2][0] = 1; hand[2][1] = 3;

    hand[3][0] = 3; hand[3][1] = 4;

    hand[4][0] = 0; hand[4][1] = 5;
}

void generateTwoPairs(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 2; hand[1][1] = 2;

    hand[2][0] = 1; hand[2][1] = 3;

    hand[3][0] = 3; hand[3][1] = 3;

    hand[4][0] = 0; hand[4][1] = 5;
}

void generateThreeOfAKind(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 2; hand[1][1] = 2;

    hand[2][0] = 1; hand[2][1] = 2;

    hand[3][0] = 3; hand[3][1] = 3;

    hand[4][0] = 0; hand[4][1] = 5;
}

void generateStraight(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 2; hand[1][1] = 3;

    hand[2][0] = 1; hand[2][1] = 4;

    hand[3][0] = 3; hand[3][1] = 5;

    hand[4][0] = 0; hand[4][1] = 6;
}

void generateFlush(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 0; hand[1][1] = 6;

    hand[2][0] = 0; hand[2][1] = 3;

    hand[3][0] = 0; hand[3][1] = 3;

    hand[4][0] = 0; hand[4][1] = 5;
}

void generateFullHouse(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 2; hand[1][1] = 2;

    hand[2][0] = 1; hand[2][1] = 3;

    hand[3][0] = 3; hand[3][1] = 3;

    hand[4][0] = 0; hand[4][1] = 3;
}

void generateFourOfAKind(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 2; hand[1][1] = 2;

    hand[2][0] = 1; hand[2][1] = 2;

    hand[3][0] = 3; hand[3][1] = 2;

    hand[4][0] = 0; hand[4][1] = 5;
}

void generateStraightFlush(int** &hand){
    hand[0][0] = 0; hand[0][1] = 2;

    hand[1][0] = 0; hand[1][1] = 3;

    hand[2][0] = 0; hand[2][1] = 4;

    hand[3][0] = 0; hand[3][1] = 5;

    hand[4][0] = 0; hand[4][1] = 6;
}

int** generateFakeDeck(int status){
    int** hand = new int* [5];
    for (int i = 0; i < 5; i++){
        *(hand + i) = new int[2];
    }

    switch(status){
        case 1:{
            generatePair(hand);
            break;
        }
        case 2:{
            generateTwoPairs(hand);
            break;
        }
        case 3:{
            generateThreeOfAKind(hand);
            break;
        }
        case 4:{
            generateStraight(hand);
            break;
        }
        case 5:{
            generateFlush(hand);
            break;
        }
        case 6:{
            generateFullHouse(hand);
            break;
        }
        case 7:{
            generateFourOfAKind(hand);
            break;
        }
        case 8:{
            generateStraightFlush(hand);
            break;
        }
    }

    return hand;
}