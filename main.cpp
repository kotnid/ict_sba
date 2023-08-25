#include <iostream>
#include "input.h"

using namespace std;

int main() {
    variant<int, dbData> result = getCsv("example.csv", 0, 100);

    if (holds_alternative<int>(result)) {
        int isSuccess = get<int>(result);
        cout << "Returned value: " << isSuccess << endl;
    } else {
        cout << "Received data" << endl;
    }

    return 0;
}