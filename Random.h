#pragma once
#include <time.h>
#include <algorithm>
using namespace std;

class Random{
private:
    Random(){
        srand((unsigned)time(NULL));
    }
public:
    static Random& instance(){
        static Random neo;
        return neo;
    };
    int next(int max); // random from 0 to max - 1 
    int next(int min, int max); // random from min to max
};