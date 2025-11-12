#pragma once
#include <fstream>
#include <string>

using namespace std;

class Logger {
private:
    ofstream logFile;
    string filename;
    
public:
    Logger();
    ~Logger();
    void log(const string& text);
    void setFilename(const string& newFilename);
    static string getNextLogFilename();  // Статический метод для получения следующего имени файла
};

extern Logger logger;