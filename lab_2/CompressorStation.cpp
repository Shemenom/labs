#include "CompressorStation.h"
#include <iostream>
#include <limits>

using namespace std;

CompressorStation::CompressorStation(int newId) 
    : id(newId), numberWorkshop(0), workingWorkshop(0), classWorkshop(0) {}

double CompressorStation::getUnusedPercentage() const {
    if (numberWorkshop == 0) return 0.0;
    return (numberWorkshop - workingWorkshop) * 100.0 / numberWorkshop;
}

void CompressorStation::setName(const string& newName) {
    if (newName.empty()) {
        throw invalid_argument("Название не может быть пустым");
    }
    name = newName;
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

void CompressorStation::setWorkingWorkshop(int& working, int number) {
    while (working < 0 || working > number) {
        cout << "Количество работающих цехов должно быть от 0 до " << number << ": ";
        cin >> working;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            working = -1;
        }
    }
    workingWorkshop = working;
}

void CompressorStation::setClassWorkshop(int classW) {
    if (classW < 1 || classW > 5) { 
        throw invalid_argument("Класс цеха должен быть от 1 до 5");
    }
    classWorkshop = classW;
}

void CompressorStation::loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop) {
    name = loadName;
    numberWorkshop = loadNumberWorkshop;
    workingWorkshop = loadWorkingWorkshop;
    classWorkshop = loadClassWorkshop;
}