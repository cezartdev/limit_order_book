#include <iostream>
#include <limit_order_book/lob.hpp>
#include <algorithm>

using namespace std;

void Lob::AddOrder(const Order& order) {
    orderIdCounter++;
    Order newOrder = order;
    
    if (order.type == "buy") {
        int remainingQuantity = order.quantity;

        // Siempre miramos el mejor ask disponible, evitando invalidar iteradores.
        while (remainingQuantity > 0 && !lob.asks.empty() && lob.asks.begin()->first <= order.price) {
            auto it = lob.asks.begin(); // mejor ask (menor precio)
            auto& priceLevel = it->second;

            while (remainingQuantity > 0 && !priceLevel.empty()) {
                Order& sellOrder = priceLevel.front();

                int tradeQty = min(remainingQuantity, sellOrder.quantity);

                // Registrar transacción (orden entrante = buy)
                trades.push_back({it->first, tradeQty, orderIdCounter, 0});

                remainingQuantity -= tradeQty;
                sellOrder.quantity -= tradeQty;

                if (sellOrder.quantity == 0) {
                    priceLevel.pop_front();
                }
            }

            // Si se vació el nivel de precio, eliminarlo con iterador válido
            if (priceLevel.empty()) {
                lob.asks.erase(it);
            }
        }

        // Si queda cantidad sin emparejar, agregar al lado de compras
        if (remainingQuantity > 0) {
            newOrder.quantity = remainingQuantity;
            lob.bids[order.price].push_back(newOrder);
        }

    } else {  // "sell"
        int remainingQuantity = order.quantity;

        // Procesar siempre el mejor bid disponible (precio más alto)
        while (remainingQuantity > 0 && !lob.bids.empty() && lob.bids.rbegin()->first >= order.price) {
            auto it = prev(lob.bids.end()); // iterador al mayor precio (mejor bid)
            auto& priceLevel = it->second;

            while (remainingQuantity > 0 && !priceLevel.empty()) {
                Order& buyOrder = priceLevel.front();

                int tradeQty = min(remainingQuantity, buyOrder.quantity);

                // Registrar transacción (orden entrante = sell)
                trades.push_back({it->first, tradeQty, 0, orderIdCounter});

                remainingQuantity -= tradeQty;
                buyOrder.quantity -= tradeQty;

                if (buyOrder.quantity == 0) {
                    priceLevel.pop_front();
                }
            }

            // Si se vació el nivel de precio, eliminarlo con iterador válido
            if (priceLevel.empty()) {
                lob.bids.erase(it);
            }
        }

        // Si queda cantidad sin emparejar, agregar al lado de ventas
        if (remainingQuantity > 0) {
            newOrder.quantity = remainingQuantity;
            lob.asks[order.price].push_back(newOrder);
        }
    }
}

double Lob::GetBestBid() const {
    if (lob.bids.empty()) return 0.0;
    return lob.bids.rbegin()->first;  // O(1)
}

double Lob::GetBestAsk() const {
    if (lob.asks.empty()) return 0.0;
    return lob.asks.begin()->first;  // O(1)
}

int Lob::GetBidQuantityAtPrice(double price) const {
    auto it = lob.bids.find(price);
    if (it == lob.bids.end()) return 0;
    
    int total = 0;
    for (const auto& order : it->second) {
        total += order.quantity;
    }
    return total;
}

int Lob::GetAskQuantityAtPrice(double price) const {
    auto it = lob.asks.find(price);
    if (it == lob.asks.end()) return 0;
    
    int total = 0;
    for (const auto& order : it->second) {
        total += order.quantity;
    }
    return total;
}

void Lob::PrintLOB() const {
    cout << "\n=== LIMIT ORDER BOOK ===" << endl;
    
    // Mostrar asks (de menor a mayor precio)
    cout << "\nASKS (Sell Orders):" << endl;
    for (const auto& [price, orders] : lob.asks) {
        int totalQty = 0;
        for (const auto& order : orders) {
            totalQty += order.quantity;
        }
        cout << "  $" << price << " x " << totalQty << endl;
    }
    
    cout << "\n--- SPREAD ---" << endl;
    cout << "Best Bid: $" << GetBestBid() << " | Best Ask: $" << GetBestAsk() << endl;
    
    // Mostrar bids (de mayor a menor precio)
    cout << "\nBIDS (Buy Orders):" << endl;
    for (auto it = lob.bids.rbegin(); it != lob.bids.rend(); ++it) {
        int totalQty = 0;
        for (const auto& order : it->second) {
            totalQty += order.quantity;
        }
        cout << "  $" << it->first << " x " << totalQty << endl;
    }

    // Mostrar trades ejecutados
    cout << "\nTRADES EXECUTED:" << endl;
    if (trades.empty()) {
        cout << "  (none)" << endl;
    } else {
        for (const auto& t : trades) {
            cout << "  $" << t.price << " x " << t.quantity
                 << " | buyId=" << t.buyOrderId
                 << " | sellId=" << t.sellOrderId << endl;
        }
    }
}

const vector<Trade>& Lob::GetTrades() const {
    return trades;
}

size_t Lob::GetTradeCount() const {
    return trades.size();
}