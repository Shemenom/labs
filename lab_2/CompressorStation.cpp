#include "CompressorStation.h"
#include <iostream>
#include <limits>
#include "Utils.h"

using namespace std;

CompressorStation::CompressorStation(int newId) : id(newId), numberWorkshop(0), workingWorkshop(0), classWorkshop(0) {}

double CompressorStation::getUnusedPercentage() const {
    if (numberWorkshop == 0) return 0.0;
    double percentage = (numberWorkshop - workingWorkshop) * 100.0 / numberWorkshop;
    return percentage;
}

void CompressorStation::setName() {
    INPUT_LINE_LOG(cin, name);
}

void CompressorStation::setNumberWorkshop(int& number) {
    while (number <= 0) {
        cout << "Количество цехов должно быть положительным: ";
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            number = 0;
        }
    }
    numberWorkshop = number;
}

void CompressorStation::setWorkingWorkshop() {
    // Используем numberWorkshop напрямую
    while (!(cin >> workingWorkshop) && (workingWorkshop < 0) || (workingWorkshop > numberWorkshop)) {
        cout << "Количество работающих цехов должно быть от 0 до " << numberWorkshop << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void CompressorStation::setWorkingWorkshop(int& change) {
    // Используем numberWorkshop напрямую
    workingWorkshop += change;
    while (!(cin >> workingWorkshop) && (workingWorkshop < 0) || (workingWorkshop > numberWorkshop)) {
        cout << "Количество работающих цехов должно быть от 0 до " << numberWorkshop << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void CompressorStation::setClassWorkshop(int classW) {
    while (classW < 1 || classW > 5) {
        cout << "Ошибка: класс станции должен быть от 1 до 5. Введите снова: ";
        cin >> classW;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            classW = 0;
        }
    }
    classWorkshop = classW;
}

void CompressorStation::loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop) {
    name = loadName;
    numberWorkshop = loadNumberWorkshop;
    workingWorkshop = loadWorkingWorkshop;
    classWorkshop = loadClassWorkshop;
}