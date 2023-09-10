// Input file code

#include "input.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

variant<int, dbData> getCsv(string filename) {
    /*
    parameter:
    filename - name of the csv
    
    error code list: 
    0 - File not exist
    1 - File is not csv
    2 - Invalid data contained 
    3 - Not integer
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

    dbData output;

    // read data
    while (getline(file, input)) {
        if (count(input.begin(), input.end(), ',') != headers.size() - 1) {
            return 2; // Invalid data contained
        }

        stringstream inputStream(input);
        string name;
        vector<float> values, maxScore(headers.size()-4),weighting(headers.size()-4);
        float value;
        int classNum;
        char comma;
        string subject;
        string Class;
        string form;

        // cout << input << "\n";
        getline(inputStream, name, ',');

        fill(maxScore.begin(), maxScore.end(), 100);
        fill(weighting.begin(), weighting.end(), 100);

        output.maxScore = maxScore;
        output.weighting = weighting;

        getline(inputStream, subject, ',');
        getline(inputStream, form, ',');
        getline(inputStream, Class, ',');

        for (int i = 3; i < headers.size(); i++) {
            string Svalue;
            getline(inputStream, Svalue, ',');

            try{
                if(Svalue != "")value = stoi(Svalue);
                else value = 0; // handle empty data
            }catch(exception e){
                return 3;
            }

            if(i == 3){
                classNum = value;
                continue;
            }

            values.emplace_back(value);
        } 

        result.emplace_back(Data{name,classNum,form,Class,subject,values});
    }    
    
    output.headers = headers;
    output.result = result;

    return output;
}