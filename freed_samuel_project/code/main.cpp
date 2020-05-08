#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include "bst.hpp"
#include "hash.hpp"
#include "llist.hpp"

using namespace std;

int main(int argc, char** argv) {

    // Initialization of variables & input file
    int testData[40000];
    float insert[400];
    float search[400];
    int iCollide[400];
    int sCollide[400];

    ifstream iFile;
    string data;

    if(argc != 2) {
        cerr << argv[0] << " input invalid, no input file specified" << endl;
        return -1;
    }

    iFile.open(argv[1]);

    if (!iFile.is_open()) {
        cout << "Could not open " << argv[1] << endl;
        return -1;
    }

    // Reading from input file
    int i = 0;
    while(getline(iFile,data,',')) {
        string sData;
        stringstream strm(data);
        getline(strm,sData);
        testData[i] = stoi(sData);
        i++;
    }

    // Top Level Menu
    bool quit = false;
    while(!quit) {
        string input;
        int option;

        cout << "MENU: Select an option, or input any other character to quit." << endl;
        cout << "1: Linked List" << endl << "2: BST" << endl << "3: Hash Table" << endl;
        
        // Reading from terminal for menu selection
        getline(cin, input);
		if (input.length() != 1 || input[0] < '1' || input[0] > '3') {
            quit = true;
            break;
		}

        option = stoi(input);
        int trial;

        // Switch to determine data type
        switch (option) {

            // Linked List case
            case 1: {
                LinkedList list;

                // 400 trials of 100 values each
                for(trial = 0; trial < 400; trial++) {
                    int begin = trial * 100;
                    int end = (trial * 100) + 99;

                    // Linked List insert & timing
                    auto iStart = chrono::steady_clock::now();
                    for(int i = begin; i <= end; i++) list.insert(testData[i]);
                    auto iFinish = chrono::steady_clock::now();
                    insert[trial] = chrono::duration_cast<chrono::nanoseconds>(iFinish-iStart).count() / 100;

                    // Linked List search and timing
                    int random[100];
                    for(int i = 0; i < 100; i++) random[i] = testData[rand()%end];
                    auto sStart = chrono::steady_clock::now();
                    for(int i = 0; i <= 100; i++) LLNode * find = list.search(random[i]);
                    auto sFinish = chrono::steady_clock::now();
                    search[trial] = chrono::duration_cast<chrono::nanoseconds>(sFinish-sStart).count() / 100;
                }

                // Output file initialization
                ofstream oFile;
                string name = "../report/LL_insert_search_";
                name = name + argv[1][7] + ".csv";
                oFile.open(name);
                
                // Output file filling
                for(int i = 0; i < 400; i++){
                    oFile << insert[i] << ",";
                }
                oFile << endl;
                for(int i = 0; i < 400; i++){
                    oFile << search[i] << ",";
                }
                
                // File creation terminal output
                cout << "Created " << name << endl << endl;
                break;
            }

            // Binary Search Tree case
            case 2: {
                BST tree;

                // 400 trials of 100 values each
                for(trial = 0; trial < 400; trial++) {
                    int begin = trial * 100;
                    int end = trial * 100 + 99;

                    // BST insert & timing
                    auto iStart = chrono::steady_clock::now();
                    for(int i = begin; i <= end; i++) tree.insert(testData[i]);
                    auto iFinish = chrono::steady_clock::now();
                    insert[trial] = chrono::duration_cast<chrono::nanoseconds>(iFinish-iStart).count() / 100;

                    // BST search & timing
                    int random[100];
                    for(int i = 0; i < 100; i++) random[i] = testData[rand()%end];
                    auto sStart = chrono::steady_clock::now();
                    for(int i = 0; i < 100; i++) BSTNode * find = tree.search(random[i]);
                    auto sFinish = chrono::steady_clock::now();
                    search[trial] = chrono::duration_cast<chrono::nanoseconds>(sFinish-sStart).count() / 100;
                }

                // Output file initialization
                ofstream oFile;
                string name = "../report/BST_insert_search_";
                name = name + argv[1][7] + ".csv";
                oFile.open(name);

                // Output file filling
                for(int i = 0; i < 400; i++){
                    oFile << insert[i] << ",";
                }
                oFile << endl;
                for(int i = 0; i < 400; i++){
                    oFile << search[i] << ",";
                }
                
                // File creation terminal output
                cout << "Created " << name << endl << endl;
                break;                
            }

            // Hash Table case
            case 3: {

                // Hash table collision resolution menu
                cout << endl << "MENU: Select a collision resolution method, or input any other character to quit." << endl;
                cout << "1: Linear" << endl << "2: Quadratic" << endl << "3: Chaining" << endl;
        
                getline(cin, input);
		        if (input.length() != 1 || input[0] < '1' || input[0] > '3') {
                    quit = true;
                    break;
		        }

                option = stoi(input);
                Hash table(40009);

                // 400 trials of 100 values each
                for(trial = 0; trial < 400; trial++) {
                    int begin = trial * 100;
                    int end = trial * 100 + 99;

                    // Hash table insert & timing
                    auto iStart = chrono::steady_clock::now();
                    for(int i = begin; i <= end; i++) table.insert(testData[i], option);
                    auto iFinish = chrono::steady_clock::now();
                    insert[trial] = chrono::duration_cast<chrono::nanoseconds>(iFinish-iStart).count() / 100;
                    iCollide[trial] = table.getCollisionsReset();

                    // Hash table search & timing
                    int random[100];
                    for(int i = 0; i < 100; i++) random[i] = testData[rand()%end];
                    auto sStart = chrono::steady_clock::now();
                    for(int i = 0; i < 100; i++) HashNode * find = table.search(random[i]);
                    auto sFinish = chrono::steady_clock::now();
                    search[trial] = chrono::duration_cast<chrono::nanoseconds>(sFinish-sStart).count() / 100;
                    sCollide[trial] = table.getCollisionsReset();
                }
                
                // Output file initialization
                ofstream oFile;
                string mode;

                string name = "../report/Hash_insert_search_";
                switch (option) {
                    case 1: {mode = "_linear"; break;}
                    case 2: {mode = "_quad"; break;}
                    case 3: {mode = "_chain"; break;}
                }
                name = name + argv[1][7] + mode + ".csv";
                oFile.open(name);
                
                // Output file filling
                for(int i = 0; i < 400; i++) oFile << insert[i] << ",";
                oFile << endl;
                for(int i = 0; i < 400; i++) oFile << search[i] << ",";
                oFile << endl;
                for(int i = 0; i < 400; i++) oFile << iCollide[i] << ",";
                oFile << endl;
                for(int i = 0; i < 400; i++) oFile << sCollide[i] << ",";
                
                // File creation terminal output
                cout << "Created " << name << endl << endl;
                break;
            }
        }
        cout << endl; 
    }

    // Exit statement
    cout << endl << "Goodbye!" << endl;
    return 0;
}