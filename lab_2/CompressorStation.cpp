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
    INPUT_LINE(cin, name);
    LOG_ACTION("Станция ID " + to_string(id) + " название установлено: " + name);
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
    LOG_ACTION("Станция ID " + to_string(id) + " всего цехов: " + to_string(numberWorkshop));
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
    LOG_ACTION("Станция ID " + to_string(id) + " работающих цехов: " + to_string(workingWorkshop));
}

void CompressorStation::setClassWorkshop(int classW) {
    if (classW < 1 || classW > 5) { 
        LOG_ERROR("Класс станции должен быть от 1 до 5");
        throw invalid_argument("Класс станции должен быть от 1 до 5");
    }
    classWorkshop = classW;
    LOG_ACTION("Станция ID " + to_string(id) + " класс установлен: " + to_string(classWorkshop));
}

void CompressorStation::loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop) {
    name = loadName;
    numberWorkshop = loadNumberWorkshop;
    workingWorkshop = loadWorkingWorkshop;
    classWorkshop = loadClassWorkshop;
    LOG_ACTION("Станция ID " + to_string(id) + " данные загружены из файла");
}