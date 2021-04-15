#include "Poker_FakeName.h"

string generateFakeName(){
    vector<string> store = {"Vinh", "Quan", "Quynh", "An", "Hoang", "Huy", "Chuong", "Loc", "Lan", "Thinh", "Nien", "Tuan", "Phuc", "Phong"};
    Random rng = Random::instance();
    return store[rng.next(store.size())];
}
