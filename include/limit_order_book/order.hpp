#pragma once
#include <string>

using namespace std;

struct Order {
    double price;
    int quantity;
    string type;  // "buy" or "sell"
};