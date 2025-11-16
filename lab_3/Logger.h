#pragma once
#include <fstream>
#include <string>
#include <random>
#include <chrono>

using namespace std;

class Logger {
private:
    ofstream logFile;
    string filename;
    
    string generateRandomFilename();

public:
    Logger();
    ~Logger();
    void log(const string& text);
    string getCurrentLogFilename() const { return filename; }
};

extern Logger logger;