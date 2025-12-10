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
    cout << "Введите количество цехов (1-100): ";
    numberWorkshop = GetCorrectNumber(1, 100);
}

void CompressorStation::setWorkingWorkshop() {
    cout << "Введите количество работающих цехов (0-" << numberWorkshop << "): ";
    workingWorkshop = GetCorrectNumber(0, numberWorkshop);
}

void CompressorStation::setWorkingEditWorkshop() {
    cout << "Запуск цеха (+1), остановка цеха (-1): ";
    int change;
    change = GetCorrectNumber(-1, 1);
    
    int newWorking = workingWorkshop + change;
    if (newWorking < 0) {
        cout << "Ошибка: количество работающих цехов не может быть меньше 0\n";
    } else if (newWorking > numberWorkshop) {
        cout << "Ошибка: количество работающих цехов не может превышать общее количество цехов\n";
    } else {
        workingWorkshop = newWorking;
        cout << "Новое количество работающих цехов: " << workingWorkshop << endl;
    }
}

void CompressorStation::setClassWorkshop() {
    cout << "Введите класс станции (1-5): ";
    classWorkshop = GetCorrectNumber(1, 5);
}

void CompressorStation::loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop) {
    name = loadName;
    numberWorkshop = loadNumberWorkshop;
    workingWorkshop = loadWorkingWorkshop;
    classWorkshop = loadClassWorkshop;
}