#include "PipelineNetwork.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Utils.h"


using namespace std;

PipelineNetwork::PipelineNetwork() : nextPipeId(1), nextStationId(1) {}

int PipelineNetwork::findFreePipeId() {
    int id = 1;
    while (pipes.count(id) > 0) {
        id++;
    }
    return id;
}

void PipelineNetwork::addPipe() {
    int freeId = findFreePipeId();
    Pipe pipe(freeId);
    inputPipeData(pipe);
    pipes[pipe.getId()] = pipe;
    
    cout << "Труба добавлена (ID: " << pipe.getId() << ")\n";
}

void PipelineNetwork::inputPipeData(Pipe& pipe) {    
    cout << "Название трубы: ";
    pipe.setName();

    cout << "Длина: ";
   // double length = GetCorrectNumberLog(0.1, 10000.0);
    pipe.setLength();

    cout << "Диаметр: ";
    //int diameter = GetCorrectNumberLog(1, 5000);
    pipe.setDiameter();

    cout << "Состояние (0 - в ремонте, 1 - работает): ";
    // bool inRepair = GetCorrectNumberLog(0, 1);
    pipe.setInRepair();
}

void PipelineNetwork::editPipe(int id) {
    if (pipes.count(id)) {
        cout << "Текущий статус ремонта: " << (pipes[id].isInRepair() ? "в ремонте" : "работает") << endl;
        cout << "Новый статус (0 - в ремонте, 1 - работает): ";
        //bool newStatus = GetCorrectNumberLog(0, 1);
        pipes[id].setInRepair();
        cout << "Статус трубы обновлен\n";
    } else {
        cout << "Труба с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::deletePipe(int id) {
    if (pipes.count(id)) {
        pipes.erase(id);
        cout << "Труба удалена\n";
    } else {
        cout << "Труба с ID " << id << " не найдена\n";
    }
}

int PipelineNetwork::findFreeStationId() {
    int id = 1;
    while (stations.count(id) > 0) {
        id++;
    }
    return id;
}

void PipelineNetwork::addStation() {
    int freeId = findFreeStationId();
    CompressorStation station(freeId);
    inputStationData(station);
    stations[station.getId()] = station;
    
    cout << "Компрессорная станция добавлена (ID: " << station.getId() << ")\n";
}

void PipelineNetwork::inputStationData(CompressorStation& station) {
    cout << "Название КС: ";
    station.setName();

    cout << "Количество цехов: ";
    station.setNumberWorkshop();

    cout << "Количество работающих цехов: ";
    station.setWorkingWorkshop();

    cout << "Класс станции (1-5): ";
    station.setClassWorkshop();
}

void PipelineNetwork::editStation(int id) {
    if (stations.count(id)) {
        cout << "Запуск цеха (+1), остановка цеха (-1): ";
        int change = GetCorrectNumberLog(-1, 1);
        stations[id].setWorkingWorkshop(change); 
    } else {
        cout << "Станция с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::deleteStation(int id) {
    if (stations.count(id)) {
        stations.erase(id);
        cout << "Станция удалена\n";
    } else {
        cout << "Станция с ID " << id << " не найдена\n";
    }
}

vector<int> PipelineNetwork::findPipesByName(const string& name) {
    vector<int> result;
    for (const auto& [id, pipe] : pipes) {
        if (pipe.getName().find(name) != string::npos) {
            result.push_back(id);
        }
    }
    return result;
}

vector<int> PipelineNetwork::findPipesByRepairStatus(bool inRepair) {
    vector<int> result;
    for (const auto& [id, pipe] : pipes) {
        if (pipe.isInRepair() == inRepair) {
            result.push_back(id);
        }
    }
    return result;
}

vector<int> PipelineNetwork::findStationsByName(const string& name) {
    vector<int> result;
    for (const auto& [id, station] : stations) {
        if (station.getName().find(name) != string::npos) {
            result.push_back(id);
        }
    }
    return result;
}
 
vector<int> PipelineNetwork::findStationsByUnusedPercentage(double minPercent) {
    vector<int> result;
    for (const auto& [id, station] : stations) {
        if (station.getUnusedPercentage() >= minPercent) {
            result.push_back(id);
        }
    }
    return result;
}

void PipelineNetwork::batchEditPipes(const vector<int>& pipeIds) {
    if (pipeIds.empty()) {
        cout << "Нет труб для редактирования\n";
        return;
    }
    
    cout << "Найдено труб: " << pipeIds.size() << endl;
    cout << "Редактировать все (1) или выбрать конкретные (2)? ";
    int choice = GetCorrectNumber(1, 2);
    
    vector<int> pipesToEdit;
    if (choice == 1) {
        pipesToEdit = pipeIds;
    } else {
        cout << "Введите ID труб через пробел: ";
        string line;
        INPUT_LINE(cin, line);
        stringstream ss(line);
        int id;
        while (ss >> id) {
            if (find(pipeIds.begin(), pipeIds.end(), id) != pipeIds.end()) {
                pipesToEdit.push_back(id);
            }
        }
    }
    
    cout << "Новое состояние (0 - в ремонте, 1 - работает): ";
    bool newStatus;
    cin >> newStatus;
    
    for (int id : pipesToEdit) {
        pipes[id].setInRepair();
    }
    
    cout << "Отредактировано труб: " << pipesToEdit.size() << endl;
}

void PipelineNetwork::viewAllObjects_pipe() {
    cout << "\n=== ТРУБЫ ===\n";
    if (pipes.empty()) {
        cout << "Трубы не созданы\n";
    } else {
        for (const auto& [id, pipe] : pipes) {
            cout << "ID: " << id << ", Название: " << pipe.getName()
                 << ", Длина: " << pipe.getLength()
                 << ", Диаметр: " << pipe.getDiameter()
                 << ", В ремонте: " << (pipe.isInRepair() ? "Да" : "Нет") << endl;
        }
    }
}
 
void PipelineNetwork::viewAllObjects_CS() {
    cout << "\n=== КОМПРЕССОРНЫЕ СТАНЦИИ ===\n";
    if (stations.empty()) {
        cout << "КС не созданы\n";
    } else {
        for (const auto& [id, station] : stations) {
            cout << "ID: " << id << ", Название: " << station.getName()
                 << ", Цехов: " << station.getNumberWorkshop() << "/" << station.getWorkingWorkshop()
                 << ", Незадействовано: " << fixed << setprecision(1) << station.getUnusedPercentage() << "%"
                 << ", Класс: " << station.getClassWorkshop() << endl;
        }
    }
}

void PipelineNetwork::saveToFile_pipe(ofstream& file) {
    file << "PIPES " << pipes.size() << endl;
    for (const auto& [id, pipe] : pipes) {
        file << "PIPE " << id << " "
             << pipe.getName() << " "
             << pipe.getLength() << " "
             << pipe.getDiameter() << " "
             << pipe.isInRepair() << endl;
    }
}

void PipelineNetwork::saveToFile_CS(ofstream& file) {
    file << "STATIONS " << stations.size() << endl;
    for (const auto& [id, station] : stations) {
        file << "STATION " << id << " "
             << station.getName() << " "
             << station.getNumberWorkshop() << " "
             << station.getWorkingWorkshop() << " "
             << station.getClassWorkshop() << endl;
    }
}

void PipelineNetwork::loadFromFile_pipe(ifstream& file) {
    string type;
    int count;
    
    file >> type >> count;
    if (type == "PIPES") {
        for (int i = 0; i < count; i++) {
            file >> type;
            int id;
            file >> id;
            
            Pipe pipe(id);
            
            string name;
            file >> name;
            double length;
            file >> length;
            int diameter;
            file >> diameter;
            bool inRepair;
            file >> inRepair;
            
            pipe.loadData(name, length, diameter, inRepair);
            pipes[id] = pipe;
            if (id >= nextPipeId) nextPipeId = id + 1;
        }
    }
}

void PipelineNetwork::loadFromFile_CS(ifstream& file) {
    string type;
    int count;
    
    file >> type >> count;
    if (type == "STATIONS") {
        for (int i = 0; i < count; i++) {
            file >> type;
            int id;
            file >> id;
            
            CompressorStation station(id);
            
            string name;
            file >> name;
            int numberWorkshop;
            file >> numberWorkshop;
            int workingWorkshop;
            file >> workingWorkshop;
            int classWorkshop;
            file >> classWorkshop;
            
            station.loadData(name, numberWorkshop, workingWorkshop, classWorkshop);
            stations[id] = station;
            if (id >= nextStationId) nextStationId = id + 1;
        }
    }
}

void PipelineNetwork::loadDataFromLog() {
    cout << "Загрузка данных из лог-файла\n";
    
    ifstream logFile(logger.getCurrentLogFilename());
    if (logFile.is_open()) {
        string line;
        
        while (logFile >> line) {
            if (line == "MENU:") {
                int menuNumber;
                logFile >> menuNumber;
                
                if (menuNumber == 1) {
                    Pipe pipe(nextPipeId++);
                    string name;
                    double length;
                    int diameter;
                    bool status;
                    
                    logFile >> name >> length >> diameter >> status;
                    
                    pipe.loadData(name, length, diameter, status);
                    pipes[pipe.getId()] = pipe;
                    
                    cout << "Труба загружена: " << name << " " << length << " " << diameter << " " << status << endl;
                }
                else if (menuNumber == 2) {
                    CompressorStation station(nextStationId++);
                    string name;
                    int total, working, classStation;
                    
                    logFile >> name >> total >> working >> classStation;
                    
                    station.loadData(name, total, working, classStation);
                    stations[station.getId()] = station;
                    
                    cout << "КС загружена: " << name << " " << total << " " << working << " " << classStation << endl;
                }
            }
        }
        logFile.close();
        cout << "Данные из лога загружены в сеть\n";
    } else {
        cout << "Не удалось открыть лог-файл\n";
    }
}