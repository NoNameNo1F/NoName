#pragma once
#include <iostream>
using namespace std;
void generatePair(int** &hand);

void generateTwoPairs(int** &hand);

void generateThreeOfAKind(int** &hand);

void generateStraight(int** &hand);

void generateFlush(int** &hand);

void generateFullHouse(int** &hand);

void generateFourOfAKind(int** &hand);

void generateStraightFlush(int** &hand);

int** generateFakeDeck(int status); 
