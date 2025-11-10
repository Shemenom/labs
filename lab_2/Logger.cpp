#include "Logger.h"
#include <iostream>

using namespace std;

Logger::Logger() {
    logFile.open("log.txt", ios::app);
    logFile << "=== Сессия начата ===" << endl;
}

Logger::~Logger() {
    logFile << "=== Сессия завершена ===" << endl;
    logFile.close();
}

void Logger::log(const string& text) {
    logFile << text << endl;
}

Logger logger;