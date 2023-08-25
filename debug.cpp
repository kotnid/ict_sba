#include "debug.h"
#include <iostream>

using namespace std;

// print all information on dbData
void printdbData(dbData customData){
    cout << "Headers: ";
    for (const std::string& header : customData.headers) {
        cout << header << " ";
    }
    cout << "\n";

    cout << "Max Scores: ";
    for (float score : customData.maxScore) {
        cout << score << " ";
    }
    cout << "\n";

    // Print weightings
    cout << "Weightings: ";
    for (float weighting : customData.weighting) {
        cout << weighting << " ";
    }
    cout << "\n";

    // Print data entries
    cout << "Data Entries: " << "\n";
    for (const Data& data : customData.result) {
        cout << "Name: " << data.name << "\n";
        cout << "Class Number: " << data.classNum << "\n";
        cout << "Scores: ";
        for (float score : data.scores) {
            cout << score << " ";
        }
        cout << "\n" << "\n";
    }
}