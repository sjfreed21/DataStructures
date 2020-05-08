#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Park {
    string parkname;
    string state;
    int area;
};

void addPark(Park parks[], string parkname, string state, int area, int length) {
    Park temp;
    temp.parkname = parkname;
    temp.state = state;
    temp.area = area;
    parks[length] = temp;
    length++;
}

void printList(const Park parks[], int length) {
    for(int i = 0; i < length; i++) {
        Park park = parks[i];
        cout << park.parkname << " [" << park.state << "] area: " << park.area << endl;
    }
}

int main(int argc, char * argv[]) {
    string line, parkname, state, area;
    ifstream iFile;
    iFile.open(argv[1]);
    ofstream oFile;
    oFile.open(argv[2]);
    int lowerArea = stoi(argv[3]);
    int upperArea = stoi(argv[4]);
    int read = 0;
    Park parks[60];
    while(getline(iFile, line)){
        stringstream strm(line);
        getline(strm,parkname,',');
        getline(strm,state,',');
        getline(strm,area,'\n');
        addPark(parks, parkname, state, stoi(area), read);
        read++;
    }
    printList(parks, read);
    for(int i = 0; i <= read; i++) {
        if(parks[i].area > lowerArea && parks[i].area < upperArea) {
            oFile << parks[i].parkname << "," << parks[i].state << "," << parks[i].area << endl;
        }
    }
    iFile.close();
    oFile.close();
}