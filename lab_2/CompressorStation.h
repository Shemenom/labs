#pragma once
#include <string>
#include <stdexcept>
#include "LogUtils.h"

using namespace std;

class CompressorStation {
private:
    int id;
    string name;
    int numberWorkshop;
    int workingWorkshop;
    int classWorkshop;
    static int nextId;
    
public:
    CompressorStation() {};
    CompressorStation(int newId);
    double getUnusedPercentage() const;
    
    int getId() const { return id; }
    string getName() const { return name; }
    int getNumberWorkshop() const { return numberWorkshop; }
    int getWorkingWorkshop() const { return workingWorkshop; }
    int getClassWorkshop() const { return classWorkshop; }
    
    void inputCS();

    void loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop);
};