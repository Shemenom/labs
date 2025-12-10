#include "CompressorStation.h"
#include <iostream>
#include <limits>
#include "Utils.h"

using namespace std;

int CompressorStation::nextId = 1;

CompressorStation::CompressorStation() {
    id = nextId++;
    numberWorkshop = 0;
    workingWorkshop = 0;
    classWorkshop = 0;
}

double CompressorStation::getUnusedPercentage() const {
    if (numberWorkshop == 0) return 0.0;
    double percentage = (numberWorkshop - workingWorkshop) * 100.0 / numberWorkshop;
    return percentage;
}

void CompressorStation::inputCS() { 
    cout << "Название КС: ";
    getline(cin >> ws, name);

    cout << "Введите количество цехов (1-100): ";
    numberWorkshop = GetCorrectNumber(1, 100);

    cout << "Введите количество работающих цехов (0-" << numberWorkshop << "): ";
    workingWorkshop = GetCorrectNumber(0, numberWorkshop);

    cout << "Введите класс станции (1-5): ";
    classWorkshop = GetCorrectNumber(1, 5);

    cout << "Данные станции успешно введены!\n";
}

void CompressorStation::loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop) {
    name = loadName;
    numberWorkshop = loadNumberWorkshop;
    workingWorkshop = loadWorkingWorkshop;
    classWorkshop = loadClassWorkshop;
}