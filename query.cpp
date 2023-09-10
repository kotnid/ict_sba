#include "query.h"
#include <iostream>

using namespace std;

vector<Data> query (vector<Data>input, vector<string>name, vector<string>sub, vector<string>form, vector<string>Cla){
    /*
    Parameter:
    input - Data 
    name - query name (Empty = no query by name)
    sub - query subject (Empty = no query by subject)
    form - query form (Empty = no query by form)
    Cla - query class (Empty = no query by class)
    */
   
    vector<Data>output;

        for (const Data& data : input) {
        bool flag = true;

        if (!name.empty()) {
            bool found = false;
            for (const std::string& n : name) {
                if (data.name == n) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                flag = false;
            }
        }

        if (!sub.empty()) {
            bool found = false;
            for (const std::string& s : sub) {
                if (data.subject == s) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                flag = false;
            }
        }

        if (!form.empty()) {
            bool found = false;
            for (const std::string& f : form) {
                if (data.form == f) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                flag = false;
            }
        }

        if (!Cla.empty()) {
            bool found = false;
            for (const std::string& c : Cla) {
                if (data.Class == c) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                flag = false;
            }
        }

        if (flag) {
            output.push_back(data);
        }

        // cout << flag << " " << data.name << "\n";
    }

    return output;
}