#pragma once
#include "Pipe.h"
#include "CompressorStation.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include "LogUtils.h"

using namespace std;

class PipelineNetwork {
private:
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> stations;
    int nextPipeId;
    int nextStationId;

    int findFreeStationId();
public:
    PipelineNetwork();

    // void inputPipeData(Pipe& pipe);
    void editPipe();
    void deletePipe();
    
    void addStation();
    void inputStationData(CompressorStation& station);
    void editStation();
    void deleteStation();
    
    vector<int> findPipesByName(const string& name);
    vector<int> findPipesByRepairStatus(bool inRepair);
    vector<int> findStationsByName(const string& name);
    vector<int> findStationsByUnusedPercentage(double minPercent);
    
    void batchEditPipes(const vector<int>& pipeIds);
    void viewAllObjects_pipe();
    void viewAllObjects_CS();

    void saveToFile_pipe(ofstream& file);
    void saveToFile_CS(ofstream& file);
    void loadFromFile_pipe(ifstream& file);
    void loadFromFile_CS(ifstream& file);
};

void addPipe(unordered_map<int, Pipe> pipes);