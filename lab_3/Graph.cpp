#include "Graph.h"

void Graph::addEdge(int source, int destination) {
    adjList[source].push_back(destination);
    vertices.insert(source);
    vertices.insert(destination);
    LOG_ACTION("Добавлено ребро в граф: " + to_string(source) + " -> " + to_string(destination));
}

void Graph::topologicalSortUtil(int v, unordered_map<int, bool>& visited, stack<int>& stack) {
    visited[v] = true;

    for (int neighbor : adjList[v]) {
        if (!visited[neighbor]) {
            topologicalSortUtil(neighbor, visited, stack);
        }
    }

    stack.push(v);
}

vector<int> Graph::topologicalSort() {
    LOG_ACTION("Запуск топологической сортировки");
    stack<int> stack;
    unordered_map<int, bool> visited;

    for (int vertex : vertices) {
        visited[vertex] = false;
    }

    for (int vertex : vertices) {
        if (!visited[vertex]) {
            topologicalSortUtil(vertex, visited, stack);
        }
    }

    vector<int> result;
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }

    LOG_ACTION("Топологическая сортировка завершена, найдено " + to_string(result.size()) + " вершин");
    return result;
}

// проверка на циклы
bool Graph::hasCycle() {
    LOG_ACTION("Проверка графа на циклы");
    unordered_map<int, bool> visited;
    unordered_map<int, bool> recStack;

    for (int vertex : vertices) {
        visited[vertex] = false;
        recStack[vertex] = false;
    }

    for (int vertex : vertices) {
        if (!visited[vertex]) {
            vector<int> stack = {vertex};
            vector<int> path = {vertex};
            
            while (!stack.empty()) {
                int current = stack.back();
                
                if (!visited[current]) {
                    visited[current] = true;
                    recStack[current] = true;
                } else {
                    recStack[current] = false;
                    stack.pop_back();
                    path.pop_back();
                    continue;
                }

                bool foundUnvisited = false;
                for (int neighbor : adjList[current]) {
                    if (!visited[neighbor]) {
                        stack.push_back(neighbor);
                        path.push_back(neighbor);
                        foundUnvisited = true;
                        break;
                    } else if (recStack[neighbor]) {
                        LOG_ERROR("Обнаружен цикл в графе: " + to_string(neighbor) + " уже в стеке вызовов");
                        return true;
                    }
                }
                
                if (!foundUnvisited) {
                    recStack[current] = false;
                    stack.pop_back();
                    path.pop_back();
                }
            }
        }
    }

    LOG_ACTION("Циклы не обнаружены");
    return false;
}

void Graph::printGraph() {
    cout << "=== СТРУКТУРА ГРАФА ===" << endl;
    for (const auto& [vertex, neighbors] : adjList) {
        cout << "КС " << vertex << " -> ";
        for (int neighbor : neighbors) {
            cout << "КС " << neighbor << " ";
        }
        cout << endl;
    }
}