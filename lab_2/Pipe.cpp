#include "Pipe.h"
#include <iostream>
#include <limits>
#include "Utils.h"
#include "LogUtils.h"

using namespace std;

Pipe::Pipe(int newId) : id(newId), length(0), diameter(0), inRepair(false) {}

void Pipe::setName() {
    getline(cin >> ws, name);
}

void Pipe::setLength() {
    cout << "Введите длину трубы (0.1-1000 км): ";
    double minLength = 0.1;
    double maxLength = 1000.0;
    while (true) {
        length = GetCorrectNumber(minLength, maxLength);
        if (length > 0) break;
        cout << "Длина должна быть положительной: ";
    }
}

void Pipe::setDiameter() {
    cout << "Введите диаметр трубы (10-2000 мм): ";
    diameter = GetCorrectNumber(10, 2000);
}

void Pipe::setInRepair() { 
    cout << "Введите состояние (0 - в ремонте, 1 - работает): ";
    inRepair = GetCorrectNumber(0, 1);
}

void Pipe::loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair) {
    name = loadName;
    length = loadLength;
    diameter = loadDiameter;
    inRepair = loadInRepair;
}