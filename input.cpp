// Input file code

#include "input.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;

variant<int, dbData> getCsv(string filename, float lowerBound, float higherBound) {
    /*
    parameter:
    filename - name of the csv
    lowerBound - lowest possible score
    higherBound - highest possible score

    error code list: 
    0 - File not exist
    1 - File is not csv
    2 - Invalid data contained 
    3 - Data out of range
    */

    // data validation
    if (!fs::exists(filename)) { // file does not exist
        return 0;
    }
    if (fs::path(filename).extension() != ".csv") { // file is not csv
        return 1;
    }

    // init read data
    ifstream file(filename);
    string input;
    vector<Data> result;

    // read header
    getline(file, input);
    stringstream inputStream(input);
    string data;
    vector<string> headers;
    while (getline(inputStream, data, ',')) {
        headers.push_back(data);
    }

    // read data
    while (getline(file, input)) {
        if (count(input.begin(), input.end(), ',') != headers.size() - 1) {
            return 2; // Invalid data contained
        }

        stringstream inputStream(input);
        string name;
        vector<float> values;
        float value;
        int classNum;
        char comma;
        cout << input << "\n";
        getline(inputStream, name, ',');

        for (int i = 1; i < headers.size(); i++) {
            string Svalue;
            getline(inputStream, Svalue, ',');
            if(Svalue != "")value = stoi(Svalue);
            else value = 0; // handle empty data
            
            if(i == 1){
                classNum = value;
                continue;
            }

            if (value < lowerBound || value > higherBound) {
                return 3; // data out of range
            }
            values.emplace_back(value);
        }

        result.emplace_back(Data{name,classNum,values});
    }    
    dbData output;
    output.headers = headers;
    output.result = result;

    return output;
}