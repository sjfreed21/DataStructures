#include <fstream>
#include <iostream>

using namespace std;

int main() {
    char str[10];
    ifstream iFile ("test.txt");
    iFile >> str;
    cout << str;
    cin.get();
    iFile.close();
}