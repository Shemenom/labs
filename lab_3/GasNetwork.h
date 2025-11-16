#pragma once
#include "Pipe.h"
#include "CompressorStation.h"
#include "Graph.h"
#include "GasNetwork.h"
#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include "LogUtils.h"

using namespace std;

struct Connection {
    int pipeId;
    int sourceStationId;
    int destinationStationId;
    int diameter;
    
    Connection(int pipe, int source, int dest, int diam) 
        : pipeId(pipe), sourceStationId(source), destinationStationId(dest), diameter(diam) {}
};

class GasNetwork {
private:
    unordered_map<int, Pipe>& pipes;
    unordered_map<int, CompressorStation>& stations;
    Graph networkGraph;
    vector<Connection> connections;
    map<pair<int, int>, int> pipeConnections; // (station1, station2) -> pipeId
    
    bool isPipeConnected(int pipeId);

public:
    GasNetwork(unordered_map<int, Pipe>& pipeRef, unordered_map<int, CompressorStation>& stationRef);
    
    bool connectStations(int sourceId, int destinationId, int diameter);
    void disconnectStations(int pipeId);
    void viewNetwork() const;
    vector<int> topologicalSort();
    bool checkCycles();
    vector<Connection> getConnections() const { return connections; }
};

