#include <iostream>
#include <limit_order_book/data.hpp>
#include <internal/constants.hpp>

using namespace std;
using namespace Colors;
using namespace Styles;

int main()
{

    /* Menu */
    cout << endl;
    cout << BOLD << "*----------------     Menu     ---------------*" << RESET << endl;
    cout << BOLD << GREEN << "*-------------- Limit Order Book --------------*" << RESET << endl;
    cout << endl;
    cout << "  " << CYAN << "1: Generate data" << "    " << "2: Simulation" << "    " << "3: Help" << RESET << endl;
    cout << endl;

    /* Select */
    int option;
    cout << "Option: ";
    cout << PURPLE;
    cin >> option;
    cout << RESET;
    cout << endl;

    switch (option)
    {
    case 1:
    {
        Data data;
        data.Generate();
        break;
    }
    case 2:
    {
        Data data;
        if (data.LoadFromCSV()) {
            cout << "Simulation started..." << endl;
            
            for (const Order& order : data.GetOrders()) {
                cout
                    << "Price: " << order.price 
                    << " | Qty: " << order.quantity 
                    << " | Type: " << order.type
                << endl;
            }
        }
        break;
    }
    default:
        break;
    }

    return 0;
}