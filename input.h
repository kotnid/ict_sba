// Header file for input

#include <string>
#include <vector>
#include <variant>

using namespace std;

struct Data {
    string name;
    vector<float> scores;
};

struct dbData{
    vector<string> headers;
    vector<Data> result;
};

variant<int, dbData> getCsv(string filename, float lowerBound, float higherBound);