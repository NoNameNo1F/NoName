#include "FakeName.h"

string generateFakeName() {
    vector<string> store = { "Vinh", "Quan", "Quynh", "An", "Hoang", "Huy", "Chuong",
    "Loc", "Lan", "Thinh", "Nien", "Tuan", "Phuc", "Phong","Vu","Cuong","Truong","Hao","Phat" };
    Random rng = Random::instance();
    return store[rng.next(store.size())];
}