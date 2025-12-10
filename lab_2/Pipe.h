#pragma once
#include <string>
#include <stdexcept>
#include "LogUtils.h"

using namespace std;

class Pipe {
private:
    int id;
    string name;
    double length;
    int diameter;
    bool inRepair;
    static int nextId;
    
public:
    Pipe();
    
    void InputPipe();

    int getId() const { return id; }
    string getName() const { return name; }
    double getLength() const { return length; }
    int getDiameter() const { return diameter; }
    bool isInRepair() const { return inRepair; }

    void loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair);
};