#pragma once
#include <vector>
#include <map>
#include <deque>
#include <limit_order_book/order.hpp>
#include <cstdint>

using namespace std;

// Structure to record trades
struct Trade {
    double price;
    int quantity;
    uint64_t buyOrderId;
    uint64_t sellOrderId;
};

// Improved LOB structure
struct LOBData {
    // map keeps prices automatically sorted (O(log n))
    // rbegin()/begin() give direct access to best bid/ask
    map<double, deque<Order>> bids;   // Descending
    map<double, deque<Order>> asks;   // Ascending
};

class Lob
{
private:
    LOBData lob;
    vector<Trade> trades;
    uint64_t orderIdCounter = 0;

public:
    // Insert order with automatic matching
    void AddOrder(const Order& order);
    
    // Best bid/ask getters (O(1) access)
    double GetBestBid() const;
    double GetBestAsk() const;
    int GetBidQuantityAtPrice(double price) const;
    int GetAskQuantityAtPrice(double price) const;
    
    // Inspect the book
    void PrintLOB() const;
    
    // Retrieve executed trades
    const vector<Trade>& GetTrades() const;
    size_t GetTradeCount() const;
};

