#include <limit_order_book/data.hpp>
#include <internal/constants.hpp>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;
using namespace Colors;

void Data::AddOrder(double price, int quantity, const string& type) {
    orders.push_back({price, quantity, type});
}

void Data::Generate() {
    cout << "Generating data..." << endl;

    // Random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> priceDist(50.0, 110.0);  // Prices between 50 and 110
    uniform_int_distribution<> quantityDist(1, 100);     // Quantities between 1 and 100
    uniform_int_distribution<> typeDist(0, 1);           // 0 = buy, 1 = sell

    // Generate sample orders
    for (int i = 0; i < 100000; i++) {
        double price = priceDist(gen);
        int quantity = quantityDist(gen);
        string type = typeDist(gen) == 0 ? "buy" : "sell";
        AddOrder(price, quantity, type);
    }

    SaveToCSV();
    cout << "Data generated successfully! (" << orders.size() << " orders)" << endl;
}

void Data::SaveToCSV() {
    ofstream file(outputPath);
    
    if (!file.is_open()) {
        cerr << "Error: Could not create file " << outputPath << endl;
        return;
    }

    // Header
    file << "price,quantity,type\n";

    // Data
    for (const auto& order : orders) {
        file << order.price << "," << order.quantity << "," << order.type << "\n";
    }

    file.close();
    cout << "CSV saved to: " << outputPath << endl;
}

bool Data::LoadFromCSV(const string& path) {
    ifstream file(path);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << path << endl;
        return false;
    }

    orders.clear();
    string line;
    
    // Skip header
    getline(file, line);

    // Read data
    while (getline(file, line)) {
        stringstream ss(line);
        string priceStr, quantityStr, type;
        
        getline(ss, priceStr, ',');
        getline(ss, quantityStr, ',');
        getline(ss, type, ',');

        Order order;
        order.price = stod(priceStr);
        order.quantity = stoi(quantityStr);
        order.type = type;
        
        orders.push_back(order);
    }

    file.close();
    cout << endl;
    cout << GREEN << "Loaded " << orders.size() << " orders from " << path << RESET << endl;
    return true;
}

vector<Order>& Data::GetOrders() {
    return orders;
}

size_t Data::GetOrderCount() {
    return orders.size();
}
