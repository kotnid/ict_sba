#pragma once
#include <string>
#include <vector>

using namespace std;

struct Data {
    string name;
    int classNum;
    string form;
    string Class;
    string subject;
    vector<float> scores;
};

struct dbData{
    vector<string> headers;
    vector<float> maxScore;
    vector<float> weighting;
    vector<Data> result;
};