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
        cout << "Form: " << data.form << "\n";
        cout << "Class: " << data.Class << "\n";
        cout << "Class Number: " << data.classNum << "\n";
        cout << "Subject: " << data.subject << "\n";
        cout << "Scores: ";
        for (float score : data.scores) {
            cout << score << " ";
        }
        cout << "\n\n";
    }
}

// print all stats
void printdbStats(unordered_map<string,float>stat){
    for (const auto& pair : stat) {
        cout << pair.first << ": " << pair.second << "\n";
    }
    cout << "\n\n";
}

// print data
void printData(vector<Data> customData){
    for (const Data& data : customData) {
        cout << "Name: " << data.name << "\n";
        cout << "Form: " << data.form << "\n";
        cout << "Class: " << data.Class << "\n";
        cout << "Class Number: " << data.classNum << "\n";
        cout << "Subject: " << data.subject << "\n";
        cout << "Scores: ";
        for (float score : data.scores) {
            cout << score << " ";
        }
        cout << "\n\n";
    }
}