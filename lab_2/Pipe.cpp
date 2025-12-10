#include "Pipe.h"
#include <iostream>
#include <limits>
#include "Utils.h"
#include "LogUtils.h"

using namespace std;

int Pipe::nextId = 1;

Pipe::Pipe() {
    id = nextId++;
    length = 0;
    diameter = 0;
    inRepair = false;
}

void Pipe::InputPipe() {
    // Ввод названия
    cout << "Название трубы: ";
    getline(cin >> ws, name);

    // Ввод длины
    cout << "Введите длину трубы: ";
    while (true) {
        length = GetCorrectNumber(0, 1000);
        if (length > 0) break;
        cout << "Длина должна быть положительной: ";
    }

    // Ввод диаметра
    cout << "Введите диаметр трубы: ";
    diameter = GetCorrectNumber(10, 2000);

    // Ввод состояния
    cout << "Введите состояние: ";
    inRepair = GetCorrectNumber(0, 1);
}

void Pipe::loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair) {
    name = loadName;
    length = loadLength;
    diameter = loadDiameter;
    inRepair = loadInRepair;
}