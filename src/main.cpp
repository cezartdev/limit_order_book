#include <iostream>
#include <generate_data.hpp>
#include <constants.hpp>

using namespace std;
using namespace Colors;
using namespace Styles;

int main() {


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

    switch (option) {
        case 1: {
            GenerateData data;

            data.Generate();


            break;
        }
        default:
            break;
    }

    return 0;
}