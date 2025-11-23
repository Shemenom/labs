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
    while(!(cin >> length) || (length <= 0)) {
        cout << "Введите денные коректно: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void Pipe::setDiameter() {
    while (!(cin >> diameter) || (diameter <= 0)) {
        cout << "Введите денные коректно: ";
        cin.clear();
        cin.ignore(1000, '\n');
    } 
}

void Pipe::setInRepair() { 
    while(!(cin >> inRepair)) {
        cout <<"Введите денные коректно: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void Pipe::loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair) {
    name = loadName;
    length = loadLength;
    diameter = loadDiameter;
    inRepair = loadInRepair;
}