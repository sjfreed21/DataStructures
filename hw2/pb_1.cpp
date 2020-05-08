#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct wordItem{
    string word;
    int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]){
    ifstream igFile;
    igFile.open(ignoreWordFileName);
    if(igFile.fail()) {
        cout << "Failed to open " << ignoreWordFileName << endl;
    }
    int i = 0;
    string word;
    while(getline(igFile,word)){
        ignoreWords[i] = word;
        i++;
    }
    igFile.close();
}

bool isStopWord(string word, string ignoreWords[]) {
    for (int i = 0; i < 50; i++) {
        if (word == ignoreWords[i]) return 1;
    }
    return 0;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) sum += uniqueWords[i].count;
    return sum;
}

// Bubble sort code based on code from https://www.geeksforgeeks.org/bubble-sort/

void arraySort(wordItem uniqueWords[], int length) {
    for (int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++){
            if(uniqueWords[j].count < uniqueWords[j+1].count) {
                wordItem temp = uniqueWords[j];
                uniqueWords[j] = uniqueWords[j+1];
                uniqueWords[j+1] = temp;
            }
        }
    }
}

void printNext10(wordItem wordItemList[], int startRank, int totalWords)
{
    float prob;
    for (int i = startRank; i < startRank+10; i++) {
        prob = (float) wordItemList[i].count/totalWords;
        cout << fixed << setprecision(4) << prob << " - " << wordItemList[i].word << endl;
    }
}

int main(int argc, char * argv[]){
    string word;
    ifstream iFile;
    string ignore[50];
    getStopWords(argv[3],ignore);
    wordItem * array;
    int i = 0, unique = 0, size = 100, doub = 0, flag = 0;
    array = new wordItem[size];
    int rank = stoi(argv[1]);
    iFile.open(argv[2]);
    if(iFile.fail()) cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
    while(iFile >> word) {
        if(isStopWord(word,ignore)) unique = unique;
        else {
            flag = 0;
            for(int j = 0; j < size; j++) {
                if(array[j].word == word) {
                    array[j].count++;
                    flag = 1;
                    break;
                }  
            }
            if(flag == 0) {
                if(i == size) {                         // Array Doubling
                    wordItem * temp;
                    temp = new wordItem[2*size];
                    for(int k = 0; k < i; k++) {
                        temp[k].word = array[k].word;
                        temp[k].count = array[k].count;
                    }
                    delete [] array;
                    array = temp;
                    size = 2*size;
                    doub++;
                }
                array[i].word = word;
                array[i].count = 1;
                i++;
                unique++;
            }
        }
    }
    arraySort(array,i);
    int total = getTotalNumberNonStopWords(array,size);
    cout << "Array doubled: " << doub << endl << "#" << endl;
    cout << "Unique non-common words: " << unique << endl << "#" << endl;
    cout << "Total non-common words: " << total << endl << "#" << endl;
    cout << "Probability of next 10 words from rank " << rank << endl << "---------------------------------------" << endl;
    printNext10(array,rank,total);
    delete [] array;
    iFile.close();
    return 0;
}