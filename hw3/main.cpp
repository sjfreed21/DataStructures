/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
    int input = 0, flag = 0;
    CountryNetwork CountryNet;
    while(!flag){
        displayMenu();
        cin >> input;
        switch(input) {
            case 1: {
                CountryNet.loadDefaultSetup();
                CountryNet.printPath();
                break;
            }
            case 2: {
                CountryNet.printPath();
                break;
            }
            case 3: {
                string rec, msg;
                getchar();              // newline stuck in buffer
                cout << "Enter name of the country to receive the message:" << endl;
                getline(cin,rec);
                cout << "Enter the message to send:" << endl;
                getline(cin,msg);
                cout << endl;
                CountryNet.transmitMsg(rec,msg);
                break;
            }
            case 4: {
                string newCountry, previous;
                int flag2 = 0;
                cout << "Enter a new country name: " << endl;
                getchar();          // newline stuck in buffer
                getline(cin,newCountry);
                cout << "Enter the previous country name (or First): " << endl;
                getline(cin,previous);
                newCountry[0] = toupper(newCountry[0]);     // toupper found on https://stackoverflow.com/questions/8530529
                previous[0] = toupper(previous[0]);
                if(previous == "First") CountryNet.insertCountry(NULL,newCountry);
                else {
                    while(!flag2) {
                        Country * temp = CountryNet.searchNetwork(previous);
                        if(!temp) {
                            cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
                            getline(cin,previous);
                        }
                        else {
                            CountryNet.insertCountry(temp,newCountry);
                            flag2 = 1;
                        }
                    }
                }
                CountryNet.printPath();
                break;
            }
            case 5: {
                cout << "Quitting... " << endl;
                flag = 1;
                break;
            }
            default: {
                cout << "Invalid Input" << endl;
                break;
            }
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
