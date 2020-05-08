#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int insertIntoSortedArray(float myArray[], int numEntries, float newValue) {
    if (numEntries > 100) return -1;
    numEntries++;
    if(numEntries == 1) {
        myArray[0] = newValue;
        return numEntries;
    }
    int neg = 0;
    if (neg == 0 && newValue<0) {
        myArray[numEntries-2] = newValue;
        neg = 1;
        return numEntries;
    }
    int i;
    for (i = 0; i < numEntries; i++) {
        if (myArray[i] < newValue) {
            float curr = myArray[i];
            myArray[i] = newValue;
            for(int j = i+1; j < numEntries; j++) {
                float next = myArray[j];
                myArray[j] = curr;
                curr = next;
            }
        return numEntries;
        }
    }
}

int main(int argc, char * argv[]) {
    string line;
    float array[100];
    ifstream iFile;
    iFile.open(argv[1]);
    if(iFile.fail()) {
        cout << "Failed to open the file." << endl;
    }
    int entries = 1;
    while(getline(iFile, line)){
        float num = stof(line);
        entries = insertIntoSortedArray(array, entries, num);
        int i;
        for (i = 0; i < entries - 2; i++) {
            cout << array[i] << ",";
        }
        cout << array[i] << endl;
    }
    iFile.close();
    return 0;
}