#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>
#include "apple.h"

using namespace std;

const int FramesPerSecond = 30;  // Number of frames to display per second
const int FrameWidth = 134;      // Width of each ASCII art frame
const int FrameHeight = 51;      // Height of each ASCII art frame

void clearConsoleScreen() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    DWORD charsWritten;
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    DWORD consoleSize;

    GetConsoleScreenBufferInfo(consoleHandle, &screenBufferInfo);
    consoleSize = screenBufferInfo.dwSize.X * screenBufferInfo.dwSize.Y;

    // Fill the console screen with spaces
    FillConsoleOutputCharacter(consoleHandle, ' ', consoleSize, cursorPosition, &charsWritten);

    // Reset the cursor position to (0, 0)
    SetConsoleCursorPosition(consoleHandle, cursorPosition);
}

void displayAsciiArt(const vector<string>& asciiArtFrames) {
    auto startTime = chrono::steady_clock::now();

    for (const string& frame : asciiArtFrames) {
        clearConsoleScreen();

        for (int i = 0; i < FrameHeight; ++i) {
            cout.write(frame.data() + i * FrameWidth, FrameWidth);
            cout << '\n';
        }
        cout << '\n';

        auto endTime = chrono::steady_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        auto frameTime = chrono::milliseconds(1000 / FramesPerSecond);
        auto remainingTime = frameTime - elapsedTime;
        int remainingTimeInt = (int)(remainingTime.count());

        if (remainingTime > chrono::milliseconds(0)) {
            Sleep(remainingTimeInt);
        }

        startTime = chrono::steady_clock::now();
    }
}

void play(){
    ifstream file("apple.txt");
    if (!file) {
        cerr << "Failed to open the file." << endl;
        return ;
    }

    vector<string> asciiArtFrames;
    string line;
    string frame;
    while (getline(file, line)) {
        if (line.empty()) {
            if (!frame.empty()) {
                asciiArtFrames.push_back(frame);
                frame.clear();
            }
        } else {
            frame += line;
        }
    }

    displayAsciiArt(asciiArtFrames);

    return ;
}