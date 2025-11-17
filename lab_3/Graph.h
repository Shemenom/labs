#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <iostream>
#include "LogUtils.h"

using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjList; // смежные вершины
    unordered_set<int> vertices; // вершины графа 
    
    void topologicalSortUtil(int v, unordered_map<int, bool>& visited, stack<int>& stack);

public:
    void addEdge(int source, int destination);
    vector<int> topologicalSort();
    bool hasCycle();
    void printGraph();
};