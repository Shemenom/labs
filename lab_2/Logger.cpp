#include "Logger.h"
#include <iostream>

using namespace std;

string Logger::generateRandomFilename() {
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);
    uniform_int_distribution<int> dist(1000, 9999);
    return "log_" + to_string(dist(generator)) + ".txt";
}

// Конструктор
Logger::Logger() {
    filename = generateRandomFilename();
    logFile.open(filename);
    cout << "Создан лог-файл: " << filename << endl;
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const string& text) {
    if (logFile.is_open()) {
        logFile << text << endl;
    }
}

Logger logger;