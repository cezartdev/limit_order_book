#include <iostream>
#include <limit_order_book/data.hpp>
#include <limit_order_book/lob.hpp>
#include <internal/constants.hpp>
#include <thread>
#include <chrono>

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
            cout << endl;
            cout << PURPLE << "Simulation started..." << RESET << endl;
            cout << endl;
            
            const int waitingTime = 3;
            int count = 1;
            Lob lob;

            for (const Order& order : data.GetOrders()) {
                #ifdef _WIN32
                    system("cls");
                #else
                    cout << "\x1B[2J\x1B[H";
                    cout.flush();
                #endif
                cout << CYAN << "Order counter: " << count << CYAN << endl;
                count++;

                cout
                << PURPLE 
                << "Price: " << order.price 
                << " | Qty: " << order.quantity 
                << " | Type: " << order.type
                << RESET << endl;
                lob.AddOrder(order);
                lob.PrintLOB();
                lob.GetTrades();
                this_thread::sleep_for(chrono::seconds(waitingTime));
            }
        }
        break;
    }
    case 3:{
        cout << "" << endl;
    }
    default:
        break;
    }

    return 0;
}