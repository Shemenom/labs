#include "Pipe.h"
#include <iostream>
#include <limits>
#include "Utils.h"
#include "LogUtils.h"

using namespace std;

Pipe::Pipe(int newId) : id(newId), length(0), diameter(0), inRepair(false) {
    LOG_OBJECT_CREATION("Труба", id);
}

void Pipe::setName() {
    INPUT_LINE(cin, name);
    LOG_ACTION("Труба ID " + to_string(id) + " название установлено: " + name);
}

void Pipe::setLength(double newLength) {
    while (newLength <= 0) {
        cout << "Ошибка: длина должна быть положительной. Введите снова: ";
        cin >> newLength;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            newLength = 0;
        }
    }
    length = newLength;
    LOG_ACTION("Труба ID " + to_string(id) + " длина установлена: " + to_string(length));
}

void Pipe::setDiameter(int newDiameter) {
    while (newDiameter <= 0) {
        cout << "Ошибка: диаметр должен быть положительным. Введите снова: ";
        cin >> newDiameter;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            newDiameter = 0;
        }
    }
    diameter = newDiameter;
    LOG_ACTION("Труба ID " + to_string(id) + " диаметр установлен: " + to_string(diameter));
}

void Pipe::setInRepair(bool repair) { 
    inRepair = repair; 
    LOG_ACTION("Труба ID " + to_string(id) + " статус ремонта: " + (repair ? "в ремонте" : "работает"));
}

void Pipe::loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair) {
    name = loadName;
    length = loadLength;
    diameter = loadDiameter;
    inRepair = loadInRepair;
    LOG_ACTION("Труба ID " + to_string(id) + " данные загружены из файла");
}