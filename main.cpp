#include <iostream>
#include "input.h"
#include "stat.h"
#include "debug.h"

using namespace std;

int main() {
    variant<int, dbData> output = getCsv("example.csv");

    if (holds_alternative<int>(output)) {
        int isSuccess = get<int>(output);
        cout << "Returned value: " << isSuccess << endl;
    } else {
        cout << "Received data" << endl;
        printdbData(get<dbData>(output));
    }

     // Create a custom dbData object
    // dbData customData;

    // // Set the headers
    // customData.headers = {"Name", "Class Number", "Score 1", "Score 2", "Score 3"};

    // // Set the max scores
    // customData.maxScore = {100.0, 10.0, 20.0, 30.0, 40.0};

    // // Set the weightings
    // customData.weighting = {0.8, 0.2, 0.5, 0.3, 0.4};

    // // Create and add sample Data objects to the result vector
    // Data data1;
    // data1.name = "John Doe";
    // data1.classNum = 1;
    // data1.scores = {90.0, 8.0, 15.0, 25.0, 35.0};

    // Data data2;
    // data2.name = "Jane Smith";
    // data2.classNum = 2;
    // data2.scores = {8.0, 1.0, 1.0, 2.0, 3.0};

    // customData.result.push_back(data1);
    // customData.result.push_back(data2);

    // customData = dbSort(0,customData);
    // for (const Data& data : customData.result) {
    //     cout << data.name << endl;
    // }

    // customData = dbSort(1,customData);
    // for (const Data& data : customData.result) {
    //     cout << data.name << endl;
    // }

    // customData = dbSort(2,customData);
    // for (const Data& data : customData.result) {
    //     cout << data.name << endl;
    // }

    // customData = dbSort(3,customData);
    // for (const Data& data : customData.result) {
    //     cout << data.name << endl;
    // }

    return 0;
}