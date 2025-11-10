#include <string>

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
    
    // Геттеры
    int getId() const { return id; }
    string getName() const { return name; }
    double getLength() const { return length; }
    int getDiameter() const { return diameter; }
    bool isInRepair() const { return inRepair; }
    
    // Сеттеры с проверками
    void setName(const string& newName);
    void setLength(double newLength);
    void setDiameter(int newDiameter);
    void setInRepair(bool repair) { inRepair = repair; }

    void loadData(const string& loadName, double loadLength, int loadDiameter, bool loadInRepair);
};