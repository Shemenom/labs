#include "Pipe.h"
#include <iostream>
#include <limits>

using namespace std;

Pipe::Pipe(int newId) : id(newId), length(0), diameter(0), inRepair(false) {}

void Pipe::setName(const string& newName) {
    if (newName.empty()) {
        cout << "Ошибка: название не может быть пустым. Введите снова: ";
        string correctedName;
        getline(cin, correctedName);
        if (correctedName.empty()) {
            throw invalid_argument("Название не может быть пустым");
        }
        name = correctedName;
    } else {
        name = newName;
    }
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
}

void Pipe::loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair) {
    name = loadName;
    length = loadLength;
    diameter = loadDiameter;
    inRepair = loadInRepair;
}