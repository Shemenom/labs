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
    
public:
    Pipe() {};
    Pipe(int newId);
    
    int getId() const { return id; }
    string getName() const { return name; }
    double getLength() const { return length; }
    int getDiameter() const { return diameter; }
    bool isInRepair() const { return inRepair; }
    
    void setName();
    void setLength(double newLength);
    void setDiameter(int newDiameter);
    void setInRepair(bool repair);

    void loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair);
};