#include <generate_data.hpp>
#include <iostream>
#include <random>

using namespace std;

void GenerateData::AddOrder(double price, int quantity, const string& type) {
    orders.push_back({price, quantity, type});
}

void GenerateData::Generate() {
    cout << "Generating data..." << endl;

    // Random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> priceDist(90.0, 110.0);  // Prices between 90 and 110
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

void GenerateData::SaveToCSV() {
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
