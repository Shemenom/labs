#include "PipelineNetwork.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Utils.h"

using namespace std;

PipelineNetwork::PipelineNetwork() : nextPipeId(1), nextStationId(1) {}


void PipelineNetwork::addPipe(unordered_map<int, Pipe> pipes) {
    Pipe pipe;
    //inputPipeData(pipe);
    pipe.InputPipe();
    pipes[pipe.getId()] = pipe;
    cout << "Труба добавлена (ID: " << pipe.getId() << ")\n";
}

// void PipelineNetwork::inputPipeData(Pipe& pipe) {    
//     cout << "Название трубы: ";
//     pipe.setName();

//     cout << "Длина: ";
//     pipe.setLength();

//     cout << "Диаметр: ";
//     pipe.setDiameter();

//     cout << "Состояние (0 - в ремонте, 1 - работает): ";
//     pipe.setInRepair();
// }

void PipelineNetwork::editPipe() {
    int id;
    cout << "Введите ID трубы для редактирования: ";
    id = GetCorrectNumber(1, 10000);
    
    if (pipes.count(id)) {
        cout << "Текущий статус ремонта: " << (pipes[id].isInRepair() ? "в ремонте" : "работает") << endl;
        cout << "Новый статус (0 - в ремонте, 1 - работает): ";
        pipes[id].setInRepair();
        cout << "Статус трубы обновлен\n";
    } else {
        cout << "Труба с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::deletePipe() {
    int id;
    cout << "Введите ID трубы для удаления: ";
    id = GetCorrectNumber(1, 10000);
    
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

void PipelineNetwork::addStation(unorderes_map<int, CompressorStation> stations) {
    CompressorStation CS;
    CS.inputCS();
    stations[CS.getId] = CS;
    cout << "Компрессорная станция добавлена (ID: " << stations.getId() << ")\n";
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

void PipelineNetwork::editStation() {
    int id;
    cout << "Введите ID КС для редактирования: ";
    id = GetCorrectNumber(1, 10000);
    
    if (stations.count(id)) {
        stations[id].setWorkingEditWorkshop(); 
    } else {
        cout << "Станция с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::deleteStation() {
    int id;
    cout << "Введите ID КС для удаления: ";
    id = GetCorrectNumber(1, 10000);
    
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
        cout << "Введите ID труб через пробел (0 для завершения): ";
        string line;
        INPUT_LINE(cin, line);
        stringstream ss(line);
        int id;
        while (ss >> id) {
            if (id == 0) break;
            if (find(pipeIds.begin(), pipeIds.end(), id) != pipeIds.end()) {
                pipesToEdit.push_back(id);
            } else {
                cout << "Труба с ID " << id << " не найдена в результатах поиска\n";
            }
        }
    }
    
    if (!pipesToEdit.empty()) {
        cout << "Новое состояние (0 - в ремонте, 1 - работает): ";
        bool newStatus;
        cin >> newStatus;
        
        for (int id : pipesToEdit) {
            pipes[id].setInRepair();
        }
        
        cout << "Отредактировано труб: " << pipesToEdit.size() << endl;
    } else {
        cout << "Нет труб для редактирования\n";
    }
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

