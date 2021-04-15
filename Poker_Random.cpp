#include "Poker_Random.h"

int Random::next(int max){ // random from 0 to max - 1 
    return rand() % max; 
}

int Random::next(int min, int max){
        return
