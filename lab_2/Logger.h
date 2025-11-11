#pragma once
#include <fstream>
#include <string>
#include "Utils.h"

class Logger {
private:
    ofstream logFile;
    
public:
    Logger();
    ~Logger();
    void log(const string& text);
};

extern Logger logger;