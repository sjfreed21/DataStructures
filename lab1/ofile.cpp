#include <fstream>
#include <iostream>

using namespace std;

int main(){
    ofstream oFile ("test.txt");
    oFile << "Insert this text into test.txt";
    oFile.close();
}