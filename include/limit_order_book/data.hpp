#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <limit_order_book/order.hpp>

using namespace std;


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

