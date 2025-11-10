#include "Pipe.h"
#include "CompressorStation.h"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class PipelineNetwork {
private:
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> stations;
    int nextPipeId;
    int nextStationId;
    
public:
    PipelineNetwork();
    
    // Трубы
    void addPipe();
    void inputPipeData(Pipe& pipe);
    void editPipe(int id);
    void deletePipe(int id);
    
    // Компрессорные станции
    void addStation();
    void inputStationData(CompressorStation& station);
    void editStation(int id);
    void deleteStation(int id);
    
    // Поиск
    vector<int> findPipesByName(const string& name);
    vector<int> findPipesByRepairStatus(bool inRepair);
    vector<int> findStationsByName(const string& name);
    vector<int> findStationsByUnusedPercentage(double minPercent);
    
    // Пакетное редактирование
    void batchEditPipes(const vector<int>& pipeIds);
    
    // Вывод
    void viewAllObjects();
    
    // Файлы
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    
    // Геттеры
    bool pipeExists(int id) const;
    bool stationExists(int id) const;
    const unordered_map<int, Pipe>& getPipes() const;
    const unordered_map<int, CompressorStation>& getStations() const;
};