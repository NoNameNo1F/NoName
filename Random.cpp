#include "Random.h"

int Random::next(int max) { // random from 0 to max - 1 
    return rand() % max;
}

int Random::next(int min, int max) {
    return (rand() % (max - min + 1) + min); // random from min to max
}