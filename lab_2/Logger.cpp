#include "Logger.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для проверки существования файла
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// Функция для получения номера из имени файла
int extractNumber(const string& filename) {
    if (filename.find("log_") == 0) {
        string numStr = filename.substr(4); // Убираем "log_"
        size_t dotPos = numStr.find('.');
        if (dotPos != string::npos) {
            numStr = numStr.substr(0, dotPos); // Убираем расширение
        }
        try {
            return stoi(numStr);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Статический метод для получения следующего имени файла
string Logger::getNextLogFilename() {
    vector<int> existingNumbers;
    
    // Ищем все существующие log_ файлы
    for (const auto& entry : filesystem::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            if (filename.find("log_") == 0) {
                int num = extractNumber(filename);
                if (num > 0) {
                    existingNumbers.push_back(num);
                }
            }
        }
    }
    
    // Находим максимальный номер
    int maxNumber = 0;
    if (!existingNumbers.empty()) {
        maxNumber = *max_element(existingNumbers.begin(), existingNumbers.end());
    }
    
    // Следующий номер
    int nextNumber = maxNumber + 1;
    return "log_" + to_string(nextNumber) + ".txt";
}

// Конструктор
Logger::Logger() {
    filename = getNextLogFilename();
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

void Logger::setFilename(const string& newFilename) {
    if (logFile.is_open()) {
        logFile.close();
    }
    filename = newFilename;
    logFile.open(filename);
}

Logger logger;