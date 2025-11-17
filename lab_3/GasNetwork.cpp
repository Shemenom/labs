#include "GasNetwork.h"
#include "PipelineNetwork.h"
#include <iostream>
#include <iomanip>

using namespace std;

GasNetwork::GasNetwork(unordered_map<int, Pipe>& pipeRef, unordered_map<int, CompressorStation>& stationRef) 
    : pipes(pipeRef), stations(stationRef) {
    LOG_ACTION("Создана газовая сеть");
}

// проверка используеться ли труба в каком-либо соединении 
bool GasNetwork::isPipeConnected(int pipeId) {
    for (const auto& conn : connections) {
        if (conn.pipeId == pipeId) {
            return true;
        }
    }
    return false;
}

// соединение основное
bool GasNetwork::connectStations(int sourceId, int destinationId, int diameter) {
    LOG_ACTION("Попытка соединения КС " + to_string(sourceId) + " -> КС " + to_string(destinationId) + " диаметром " + to_string(diameter));
    
    // Проверка существования КС
    if (stations.find(sourceId) == stations.end()) {
        LOG_ERROR("КС источник с ID " + to_string(sourceId) + " не найдена");
        cout << "Ошибка: КС с ID " << sourceId << " не найдена!\n";
        return false;
    }
    
    if (stations.find(destinationId) == stations.end()) {
        LOG_ERROR("КС назначение с ID " + to_string(destinationId) + " не найдена");
        cout << "Ошибка: КС с ID " << destinationId << " не найдена!\n";
        return false;
    }
    
    if (sourceId == destinationId) {
        LOG_ERROR("Попытка соединения КС с самой собой: " + to_string(sourceId));
        cout << "Ошибка: нельзя соединить КС с самой собой!\n";
        return false;
    }
    
    // Проверка допустимых диаметров
    set<int> allowedDiameters = {500, 700, 1000, 1400};
    if (allowedDiameters.find(diameter) == allowedDiameters.end()) {
        LOG_ERROR("Неверный диаметр трубы: " + to_string(diameter));
        cout << "Ошибка: допустимые диаметры: 500, 700, 1000, 1400 мм!\n";
        return false;
    }
    
    // Поиск свободной трубы с нужным диаметром
    int foundPipeId = -1;
    for (const auto& [id, pipe] : pipes) {
        if (pipe.getDiameter() == diameter && !isPipeConnected(id)) {
            foundPipeId = id;
            break;
        }
    }
    
    // Если труба не найдена, предлагаем создать новую
    if (foundPipeId == -1) {
        cout << "Свободная труба диаметром " << diameter << " мм не найдена.\n";
        cout << "Создать новую трубу? (1 - да, 0 - нет): ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            // Здесь должна быть логика создания новой трубы
            // Для простоты просто возвращаем false
            LOG_ACTION("Пользователь выбрал создание новой трубы");
            PipelineNetwork network;
            network.addPipe();
            foundPipeId = pipes.size() + 1;
        }
    }
    
    // Проверка на существующее соединение
    if (pipeConnections.find({sourceId, destinationId}) != pipeConnections.end()) {
        LOG_ERROR("Соединение между КС " + to_string(sourceId) + " и " + to_string(destinationId) + " уже существует");
        cout << "Ошибка: соединение между этими КС уже существует!\n";
        return false;
    }
    
    // Создание соединения
    connections.emplace_back(foundPipeId, sourceId, destinationId, diameter);
    pipeConnections[{sourceId, destinationId}] = foundPipeId;
    networkGraph.addEdge(sourceId, destinationId);
    
    cout << "КС " << sourceId << " соединена с КС " << destinationId 
         << " трубой ID " << foundPipeId << " (диаметр: " << diameter << " мм)\n";
    
    LOG_ACTION("Успешное соединение: КС " + to_string(sourceId) + " -> КС " + to_string(destinationId) + " трубой ID " + to_string(foundPipeId));
    
    return true;
}

void GasNetwork::disconnectStations(int pipeId) {
    LOG_ACTION("Попытка разъединения трубы ID: " + to_string(pipeId));
    
    auto it = connections.begin();
    while (it != connections.end()) {
        if (it->pipeId == pipeId) {
            pipeConnections.erase({it->sourceStationId, it->destinationStationId});
            // Здесь нужно обновить граф (более сложная операция)
            connections.erase(it);
            cout << "Соединение с трубой ID " << pipeId << " разорвано\n";
            LOG_ACTION("Соединение с трубой ID " + to_string(pipeId) + " разорвано");
            return;
        }
        ++it;
    }
    
    LOG_ERROR("Соединение с трубой ID " + to_string(pipeId) + " не найдено");
    cout << "Соединение с трубой ID " << pipeId << " не найдено!\n";
}

void GasNetwork::viewNetwork() const {
    cout << "\n=== ГАЗОТРАНСПОРТНАЯ СЕТЬ ===\n";
    
    if (connections.empty()) {
        cout << "Соединения отсутствуют\n";
        return;
    }
    
    cout << "Соединения:\n";
    for (const auto& conn : connections) {
        cout << "КС " << conn.sourceStationId << " -> КС " << conn.destinationStationId
             << " [Труба ID: " << conn.pipeId << ", Диаметр: " << conn.diameter << " мм]\n";
    }
    
    // Показываем структуру графа
    cout << "\nСтруктура сети:\n";
    map<int, vector<int>> adjacency;
    for (const auto& conn : connections) {
        adjacency[conn.sourceStationId].push_back(conn.destinationStationId);
    }
    
    for (const auto& [station, neighbors] : adjacency) {
        cout << "КС " << station << " -> ";
        for (int neighbor : neighbors) {
            cout << "КС " << neighbor << " ";
        }
        cout << endl;
    }
}

vector<int> GasNetwork::topologicalSort() {
    LOG_ACTION("Запуск топологической сортировки газовой сети");
    return networkGraph.topologicalSort();
}

bool GasNetwork::checkCycles() {
    LOG_ACTION("Проверка газовой сети на циклы");
    
    // Создаем временный граф для проверки циклов
    Graph tempGraph;
    for (const auto& conn : connections) {
        tempGraph.addEdge(conn.sourceStationId, conn.destinationStationId);
    }
    
    // Используем алгоритм поиска циклов
    unordered_map<int, bool> visited;
    unordered_map<int, bool> recStack;
    
    function<bool(int)> hasCycleUtil = [&](int v) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;
            
            // Получаем соседей из connections
            for (const auto& conn : connections) {
                if (conn.sourceStationId == v) {
                    int neighbor = conn.destinationStationId;
                    if (!visited[neighbor] && hasCycleUtil(neighbor)) {
                        return true;
                    } else if (recStack[neighbor]) {
                        return true;
                    }
                }
            }
        }
        recStack[v] = false;
        return false;
    };
    
    // Собираем все вершины
    set<int> vertices;
    for (const auto& conn : connections) {
        vertices.insert(conn.sourceStationId);
        vertices.insert(conn.destinationStationId);
    }
    
    for (int vertex : vertices) {
        visited[vertex] = false;
        recStack[vertex] = false;
    }
    
    for (int vertex : vertices) {
        if (!visited[vertex]) {
            if (hasCycleUtil(vertex)) {
                LOG_ERROR("Обнаружен цикл в газовой сети");
                return true;
            }
        }
    }
    
    LOG_ACTION("Циклы в газовой сети не обнаружены");
    return false;
}