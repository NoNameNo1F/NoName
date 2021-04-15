#pragma once
#include <iostream>
using namespace std;
void generatePair(int** & _hand);

void generateTwoPairs(int** & _hand);

void generateThreeOfAKind(int** & _hand);

void generateStraight(int** & _hand);

void generateFlush(int** & _hand);

void generateFullHouse(int** & _hand);

void generateFourOfAKind(int** & _hand);

void generateStraightFlush(int** & _hand);

int** generateFakeDeck(int status); 
