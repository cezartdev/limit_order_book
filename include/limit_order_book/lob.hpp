#pragma once
#include <vector>
#include <map>
#include <deque>
#include <limit_order_book/order.hpp>
#include <cstdint>

using namespace std;

// Estructura para registrar transacciones
struct Trade {
    double price;
    int quantity;
    uint64_t buyOrderId;
    uint64_t sellOrderId;
};

// Estructura LOB mejorada
struct LOBData {
    // map mantiene precios ordenados automáticamente (O(log n))
    // rbegin() accede directamente al mejor bid/ask
    map<double, deque<Order>> bids;   // Ordenado de mayor a menor
    map<double, deque<Order>> asks;   // Ordenado de menor a mayor
};

class Lob
{
private:
    LOBData lob;
    vector<Trade> trades;
    uint64_t orderIdCounter = 0;

public:
    // Insertar orden (con matching automático)
    void AddOrder(const Order& order);
    
    // Getters para best bid/ask (acceso O(1))
    double GetBestBid() const;
    double GetBestAsk() const;
    int GetBidQuantityAtPrice(double price) const;
    int GetAskQuantityAtPrice(double price) const;
    
    // Consultar el libro
    void PrintLOB() const;
    
    // Obtener transacciones
    const vector<Trade>& GetTrades() const;
    size_t GetTradeCount() const;
};

