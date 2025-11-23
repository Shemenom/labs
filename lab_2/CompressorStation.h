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
    
public:
    CompressorStation() {};
    CompressorStation(int newId);
    double getUnusedPercentage() const;
    
    int getId() const { return id; }
    string getName() const { return name; }
    int getNumberWorkshop() const { return numberWorkshop; }
    int getWorkingWorkshop() const { return workingWorkshop; }
    int getClassWorkshop() const { return classWorkshop; }
    
    void setName();
    void setNumberWorkshop(int& number);
    void setWorkingWorkshop();
    void setWorkingWorkshop(int& change);
    void setClassWorkshop(int classW);

    void setWorkingEditWorkshop(int& change);

    void loadData(const string& loadName, int loadNumberWorkshop, int loadWorkingWorkshop, int loadClassWorkshop);
};