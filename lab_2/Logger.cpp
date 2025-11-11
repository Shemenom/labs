#include "Logger.h"
#include <iostream>

Logger::Logger() {
    logFile.open("log.txt", ios::app);
    LOG_ACTION("=== Начало сессии ===");
}

Logger::~Logger() {
    LOG_ACTION("=== Конец сессии ===");
    logFile.close();
}

void Logger::log(const string& text) {
    logFile << text << endl;
    cerr << "ЛОГ: " << text << endl;
}

Logger logger;