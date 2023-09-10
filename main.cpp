#include <windows.h>
#include <iostream>
#include "input.h"
#include "stat.h"
#include "debug.h"
#include "query.h"
#include "apple.h"
#include <sstream>

using namespace std;

string keyToStr(WORD s) {
    if (s == VK_LEFT) {
        return "left";
    } else if (s == VK_RIGHT) {
        return "right";
    } else if (s == VK_UP) {
        return "up";
    } else if (s == VK_DOWN) {
        return "down";
    } else if (s == VK_RETURN) {
        return "enter";
    } else if (s == VK_BACK) {
        return "backspace";
    } else if (s >= 65 && s <= 91) {
        return string(1, 'a' + (int)s - 65);
    } else if (s >= 48 && s <= 57) {
        return to_string(s - 48);
    } else if(s == VK_OEM_COMMA){
        return ",";
    }else if(s == VK_ESCAPE){
        return "esc";
    }else{
        return "unknown";
    }
}
string getFile() {
    OPENFILENAME ofn;
    char filePath[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = GetForegroundWindow();
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        return filePath;
    } else {
        return "";
    }
}

vector<string>page0List = {
    "R : Read csv",
    "G : Get data",
    "ESC : Quit program"
};

vector<string>page1List = {
    "Enter : Nextline/page",
    "ESC : Return last page"
};

vector<string>page2List = {
    "1 : Sort by score ascending",
    "2 : Sort by score descending",
    "3 : Sort by class+number ascending(ascii)",
    "4 : Sort by class+number descending(ascii)",
    "5 : play bad apple!",
    "ESC : Return last page"
};

int width = 70;
int height = 30;

void screenOutput(vector<string>output){
    cout << "Scoring system - by tkt" << "\n";
    for(int i=0; i<width; i++)cout << "=";
    cout << "\n\n";

    for(string s : output){
        cout << s << "\n";
    }

    for(int i=0 ; i<height-(int)output.size();i++)cout << "\n";

    for(int i=0; i<width; i++)cout << "=";
    cout << "\n\n";
}

void contentOutput(vector<string>output){
    for(string s : output){
        cout << s << "\n";
    }
}

void extraOutput(vector<string>output,string msg,int val){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, val);
    
    cout << "\n<-- "+msg+" -->\n";
    for(string s : output){
        cout << s << "\n";
    }
    cout << "<-- "+msg+" -->\n";

    SetConsoleTextAttribute(hConsole, 0);
}

vector<string>initPage1Content = {
    "!!! Please Enter your data and click enter !!!",
    "Name (Comma for seperate, empty for no query):",
    "Form (Comma for seperate, empty for no query):",
    "Class (Comma for seperate, empty for no query):",
    "Subject (Comma for seperate, empty for no query):",
};

vector<string>initPage0Content = {
    "Welcome to scoring system made by tkt",
    "all the details will show on this box",
    "all the key control events are listed on the below area",
    "last update: 9/11/23 4:18am"
};

vector<string> splitString(string& input, char delimiter) {
    vector<string> result;
    stringstream iss(input);
    string token;

    while (getline(iss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

vector<string>printScreenData(vector<Data>& queryData){
    vector<string>printScreen;

    string s = "Name           Form      Class    Class No.  Subject      Score  ", s2 = "-------------- --------- -------- ---------- ------------ -------";
    printScreen.push_back(s);
    printScreen.push_back(s2);

    // int space[6] = {15,10,9,11,13,7};

    for(Data queryD : queryData){
        string s2 = "";

        if(queryD.name.length() < 15)s2 += queryD.name + string(15 - queryD.name.length(), ' ');
        else s2 += queryD.name;

        if(queryD.form.length() < 10)s2 += queryD.form + string(10 - queryD.form.length(), ' ');
        else s2 += queryD.form;

        if(queryD.Class.length() < 9)s2 += queryD.Class + string(9 - queryD.Class.length(), ' ');
        else s2 += queryD.Class;

        if(to_string(queryD.classNum).length() < 11)s2 += to_string(queryD.classNum) + string(11 - to_string(queryD.classNum).length(), ' ');
        else s2 += to_string(queryD.classNum);

        if(queryD.subject.length() < 13)s2 += queryD.subject + string(13 - queryD.subject.length(), ' ');
        else s2 += queryD.subject;

        if(to_string(queryD.scores[0]).length() < 7)s2 += to_string(queryD.scores[0]) + string(7 - to_string(queryD.scores[0]).length(), ' ');
        else s2 += to_string(queryD.scores[0]);

        printScreen.push_back(s2);
    }

    for(int i=0 ; i<10; i++)printScreen.push_back("");
    printScreen.push_back("     "+string(width-10,'-')+"     ");

    unordered_map<string,float>stats = getStats(queryData);
    for (const auto& pair : stats) {
        printScreen.push_back(pair.first+": "+to_string(pair.second));
    }

    return printScreen;
}

int main(){
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~ENABLE_ECHO_INPUT);

    // HWND consoleWindow = GetConsoleWindow();
    // ShowWindow(consoleWindow, SW_MAXIMIZE);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;


    INPUT_RECORD input;
    DWORD numEvents;

    int page = 0;
    int cnt = 0;
    system("cls");
    screenOutput(initPage0Content);
    contentOutput(page0List);

    dbData Database;
    vector<string>filters(4);
    vector<Data> queryData;

    while(true){
        ReadConsoleInput(hInput, &input, 1, &numEvents);
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            string key = keyToStr(input.Event.KeyEvent.wVirtualKeyCode);

            system("cls");

            if(page == 0){ // welcome    
                screenOutput(initPage0Content);
                contentOutput(page0List);

                if(key == "esc"){
                    system("cls");
                    return 0;
                }else if(key == "g"){
                    page = 1;
                    cnt = 0;
                    for (auto& filter : filters) {
                        filter = "";
                    }
                    system("cls");
                    screenOutput(initPage1Content);
                    contentOutput(page1List);
                }else if(key == "r"){
                    string filePath = getFile();
                    variant<int, dbData> output = getCsv(filePath);

                    if (holds_alternative<int>(output)) {
                        int ErrorCode = get<int>(output);
                        if(ErrorCode == 0){
                            extraOutput({"File not exists!"},"Error",100);
                        }else if(ErrorCode == 1){
                            extraOutput({"File is not csv!"},"Error",100);
                        }else if(ErrorCode == 2){
                            extraOutput({"Invalid data contain!"},"Error",100);
                        }else if(ErrorCode == 3){
                            extraOutput({"Data is not integer!"},"Error",100);
                        }
                    } else {
                        Database = get<dbData>(output);
                        extraOutput({filePath+" is loaded!"},"Info",30);
                    }
                }
            }
            else if(page == 1){ // filter 
                vector<string>printContent;

                if(key == "enter"){
                    cnt++;
                    if(cnt==4){
                        page = 2;
                        system("cls");
                        // printdbData(Database);
                        queryData = query(Database.result, splitString(filters[0],','),splitString(filters[3],','),splitString(filters[1],','),splitString(filters[2],','));
                        screenOutput(printScreenData(queryData));
                        contentOutput(page2List);
                    }
                }else if(key == "backspace"){
                    if(!filters[cnt].empty())filters[cnt].pop_back();
                }else if(key == "esc"){
                    page = 0;
                    system("cls");
                    screenOutput(initPage0Content);
                    contentOutput(page0List);
                }else if(key.length()==1){
                    filters[cnt]+=key;
                }

                if(page == 1){
                    printContent.push_back(initPage1Content[0]);
                    for(int i=0;i<4; i++){
                        if(cnt != i)printContent.push_back("\n    "+initPage1Content[i+1]+filters[i]);
                        else printContent.push_back("\n--> "+initPage1Content[i+1]+filters[i]);
                    }
                    screenOutput(printContent);
                    contentOutput(page1List);
                }
            }
            else if(page == 2){ // data
                if(key == "esc"){
                    page = 1;
                    cnt = 0;
                    for (auto& filter : filters) {
                        filter = "";
                    }
                    system("cls");
                    screenOutput(initPage1Content);
                    contentOutput(page1List);
                }else{
                    if(key == "1"){
                        queryData = dbSort(0,queryData);
                    }else if(key == "2"){
                        queryData = dbSort(1,queryData);
                    }else if(key == "3"){
                        queryData = dbSort(2,queryData);
                    }else if(key == "4"){
                        queryData = dbSort(3,queryData);
                    }else if(key == "5"){
                        play();
                        system("cls");
                    }

                    screenOutput(printScreenData(queryData));
                    contentOutput(page2List);
                }
            }
        }
    }
}