#include "FakeDeck.h"


void generatePair(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 2; _hand[1][1] = 2;

    _hand[2][0] = 1; _hand[2][1] = 3;

    _hand[3][0] = 3; _hand[3][1] = 4;

    _hand[4][0] = 0; _hand[4][1] = 5;
}

void generateTwoPairs(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 2; _hand[1][1] = 2;

    _hand[2][0] = 1; _hand[2][1] = 3;

    _hand[3][0] = 3; _hand[3][1] = 3;

    _hand[4][0] = 0; _hand[4][1] = 5;
}

void generateThreeOfAKind(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 2; _hand[1][1] = 2;

    _hand[2][0] = 1; _hand[2][1] = 2;

    _hand[3][0] = 3; _hand[3][1] = 3;

    _hand[4][0] = 0; _hand[4][1] = 5;
}

void generateStraight(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 2; _hand[1][1] = 3;

    _hand[2][0] = 1; _hand[2][1] = 4;

    _hand[3][0] = 3; _hand[3][1] = 5;

    _hand[4][0] = 0; _hand[4][1] = 6;
}

void generateFlush(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 0; _hand[1][1] = 6;

    _hand[2][0] = 0; _hand[2][1] = 3;

    _hand[3][0] = 0; _hand[3][1] = 3;

    _hand[4][0] = 0; _hand[4][1] = 5;
}

void generateFullHouse(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 2; _hand[1][1] = 2;

    _hand[2][0] = 1; _hand[2][1] = 3;

    _hand[3][0] = 3; _hand[3][1] = 3;

    _hand[4][0] = 0; _hand[4][1] = 3;
}

void generateFourOfAKind(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 2; _hand[1][1] = 2;

    _hand[2][0] = 1; _hand[2][1] = 2;

    _hand[3][0] = 3; _hand[3][1] = 2;

    _hand[4][0] = 0; _hand[4][1] = 5;
}

void generateStraightFlush(int**& _hand) {
    _hand[0][0] = 0; _hand[0][1] = 2;

    _hand[1][0] = 0; _hand[1][1] = 3;

    _hand[2][0] = 0; _hand[2][1] = 4;

    _hand[3][0] = 0; _hand[3][1] = 5;

    _hand[4][0] = 0; _hand[4][1] = 6;
}

int** generateFakeDeck(int status) {
    int** _hand = new int* [5];
    for (int i = 0; i < 5; i++) {
        *(_hand + i) = new int[2];
    }

    switch (status) {
    case 1: {
        generatePair(_hand);
        break;
    }
    case 2: {
        generateTwoPairs(_hand);
        break;
    }
    case 3: {
        generateThreeOfAKind(_hand);
        break;
    }
    case 4: {
        generateStraight(_hand);
        break;
    }
    case 5: {
        generateFlush(_hand);
        break;
    }
    case 6: {
        generateFullHouse(_hand);
        break;
    }
    case 7: {
        generateFourOfAKind(_hand);
        break;
    }
    case 8: {
        generateStraightFlush(_hand);
        break;
    }
    }

    return _hand;
}