#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Order {
    double price;
    int quantity;
    string type;  // "buy" or "sell"
};

class Data {
private:
    vector<Order> orders;
    string outputPath = "data/orders.csv";
public:
    void AddOrder(double price, int quantity, const string& type);
    void Generate();
    void SaveToCSV();
    

    bool LoadFromCSV(const string& path = "data/orders.csv");
    vector<Order>& GetOrders();
    size_t GetOrderCount();
};

