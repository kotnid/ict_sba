// Header file for input

#include <string>
#include <vector>
#include <variant>
#include "data.h"

using namespace std;

variant<int, dbData> getCsv(string filename);