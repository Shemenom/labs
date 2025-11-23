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
    getline(cin >> ws, name);
}

void CompressorStation::setNumberWorkshop() {
    while (!(cin >> numberWorkshop) || (numberWorkshop < 0)) {
        cout << "Введите данные коренктно: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void CompressorStation::setWorkingWorkshop() {
    // Используем numberWorkshop напрямую
    while (!(cin >> workingWorkshop) || (workingWorkshop < 0) || (workingWorkshop > numberWorkshop)) {
        cout << "Количество работающих цехов должно быть от 0 до " << numberWorkshop << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void CompressorStation::setWorkingWorkshop(int& change) {
    // Используем numberWorkshop напрямую
    workingWorkshop += change;
    while ((workingWorkshop < 0) || (workingWorkshop > numberWorkshop)) {
        cout << "Количество работающих цехов должно быть от 0 до " << numberWorkshop << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void CompressorStation::setClassWorkshop() {
   while (!(cin >> classWorkshop) || (classWorkshop > 5) || (classWorkshop < 1)) {
        cout << "Количество работающих цехов должно быть от 0 до " << numberWorkshop << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void CompressorStation::loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop) {
    name = loadName;
    numberWorkshop = loadNumberWorkshop;
    workingWorkshop = loadWorkingWorkshop;
    classWorkshop = loadClassWorkshop;
}