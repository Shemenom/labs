#include <string>
#include <stdexcept>

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
    
    // Геттеры
    int getId() const { return id; }
    string getName() const { return name; }
    int getNumberWorkshop() const { return numberWorkshop; }
    int getWorkingWorkshop() const { return workingWorkshop; }
    int getClassWorkshop() const { return classWorkshop; }
    
    // Сеттеры с проверками
    void setName(const string& newName);
    void setNumberWorkshop(int& number);
    void setWorkingWorkshop(int& working, int number);
    void setClassWorkshop(int classW);

    void loadData(const string& loadName, int loadNumberWorkshop,int loadWorkingWorkshop, int loadClassWorkshop);

};