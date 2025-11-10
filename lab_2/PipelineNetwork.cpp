#include "PipelineNetwork.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <filesystem>

using namespace std;

PipelineNetwork::PipelineNetwork() : nextPipeId(1), nextStationId(1) {}

void PipelineNetwork::addPipe() {
    Pipe pipe(nextPipeId++);
    inputPipeData(pipe);
    pipes[pipe.getId()] = pipe;
    cout << "Труба добавлена (ID: " << pipe.getId() << ")\n";
    logger.log("Добавлена труба ID: " + to_string(pipe.getId()));
}

void PipelineNetwork::inputPipeData(Pipe& pipe) {
    cout << "Название трубы: ";
    string name;
    getline(cin >> ws, name);
    pipe.setName(name);

    cout << "Длина: ";
    double length;
    cin >> length;
    pipe.setLength(length);

    cout << "Диаметр: ";
    int diameter;
    cin >> diameter;
    pipe.setDiameter(diameter);

    cout << "Состояние (0 - в ремонте, 1 - целая): ";
    bool inRepair;
    cin >> inRepair;
    pipe.setInRepair(inRepair);

}

void PipelineNetwork::editPipe(int id) {
    if (pipes.count(id)) {
        cout << "Редактирование трубы ID: " << id << endl;
        inputPipeData(pipes[id]);
        cout << "Труба отредактирована\n";
        logger.log("Отредактирована труба ID: " + to_string(id));
    } else {
        cout << "Труба с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::deletePipe(int id) {
    if (pipes.count(id)) {
        pipes.erase(id);
        cout << "Труба удалена\n";
        logger.log("Удалена труба ID: " + to_string(id));
    } else {
        cout << "Труба с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::addStation() {
    CompressorStation station(nextStationId++);
    inputStationData(station);
    stations[station.getId()] = station;
    cout << "Компрессорная станция добавлена (ID: " << station.getId() << ")\n";
    logger.log("Добавлена КС ID: " + to_string(station.getId()));
}

void PipelineNetwork::inputStationData(CompressorStation& station) {
    cout << "Название КС: ";
    string name;
    getline(cin >> ws, name);
    try {
        station.setName(name);
    } catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << ". Введите название снова: ";
        getline(cin >> ws, name);
        station.setName(name);
    }

    cout << "Количество цехов: ";
    int numberWorkshop;
    cin >> numberWorkshop;
    station.setNumberWorkshop(numberWorkshop);

    cout << "Количество работающих цехов: ";
    int workingWorkshop;
    cin >> workingWorkshop;
    station.setWorkingWorkshop(workingWorkshop, station.getNumberWorkshop());

    cout << "Класс станции (1-5): ";
    int classWorkshop;
    cin >> classWorkshop;
    try {
        station.setClassWorkshop(classWorkshop);
    } catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << ". Введите класс снова: ";
        cin >> classWorkshop;
        station.setClassWorkshop(classWorkshop);
    }
}

void PipelineNetwork::editStation(int id) {
    if (stations.count(id)) {
        cout << "Запуск цеха (+1), остановка цеха (-1): ";
        int change;
        cin >> change;
        
        int currentWorking = stations[id].getWorkingWorkshop();
        int number = stations[id].getNumberWorkshop();
        int newWorking = currentWorking + change;
        
        if (newWorking >= 0 && newWorking <= number) {
            stations[id].setWorkingWorkshop(newWorking, number);
            cout << "Количество работающих цехов: " << stations[id].getWorkingWorkshop() << endl;
            logger.log("Отредактирована КС ID: " + to_string(id));
        } else {
            cout << "Недопустимое количество!\n";
        }
    } else {
        cout << "КС с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::deleteStation(int id) {
    if (stations.count(id)) {
        stations.erase(id);
        cout << "КС удалена\n";
        logger.log("Удалена КС ID: " + to_string(id));
    } else {
        cout << "КС с ID " << id << " не найдена\n";
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
    int choice;
    cin >> choice;
    cin.ignore(100, '\n');
    
    vector<int> pipesToEdit;
    if (choice == 1) {
        pipesToEdit = pipeIds;
    } else {
        cout << "Введите ID труб через пробел: ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        int id;
        while (ss >> id) {
            if (find(pipeIds.begin(), pipeIds.end(), id) != pipeIds.end()) {
                pipesToEdit.push_back(id);
            }
        }
    }
    
    cout << "Новое состояние (0 - в ремонте, 1 - целая): ";
    bool newStatus;
    cin >> newStatus;
    
    for (int id : pipesToEdit) {
        pipes[id].setInRepair(newStatus);
    }
    
    cout << "Отредактировано труб: " << pipesToEdit.size() << endl;
    logger.log("Пакетное редактирование: изменено " + to_string(pipesToEdit.size()) + " труб");
    
}

void PipelineNetwork::viewAllObjects() {
    cout << "\n=== ТРУБЫ ===\n";
    if (pipes.empty()) {
        cout << "Трубы не созданы\n";
    } else {
        for (const auto& [id, pipe] : pipes) {
            cout << "ID: " << id << ", Название: " << pipe.getName()
                 << ", Длина: " << pipe.getLength()
                 << ", Диаметр: " << pipe.getDiameter()
                 << ", В ремонте: " << (pipe.isInRepair() ? "Нет" : "Да") << endl;
        }
    }
    
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

void PipelineNetwork::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        // Сохраняем трубы
        file << "PIPES " << pipes.size() << endl;
        for (const auto& [id, pipe] : pipes) {
            file << "PIPE " << id << " "
                 << pipe.getName() << " "
                 << pipe.getLength() << " "
                 << pipe.getDiameter() << " "
                 << pipe.isInRepair() << endl;
        }
        
        // Сохраняем КС
        file << "STATIONS " << stations.size() << endl;
        for (const auto& [id, station] : stations) {
            file << "STATION " << id << " "
                 << station.getName() << " "
                 << station.getNumberWorkshop() << " "
                 << station.getWorkingWorkshop() << " "
                 << station.getClassWorkshop() << endl;
        }
        
        file.close();
        cout << "Данные сохранены в файл: " << filename << endl;
        logger.log("Сохранение данных в файл: " + filename);
    } else {
        cout << "Ошибка открытия файла для записи\n";
    }
}

void PipelineNetwork::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();
        
        string type;
        int count;
        
        // Загружаем трубы
        file >> type >> count;
        if (type == "PIPES") {
            for (int i = 0; i < count; i++) {
                file >> type; // "PIPE"
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
        
        // Загружаем КС
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
        
        file.close();
        cout << "Данные загружены из файла: " << filename << endl;
        logger.log("Загрузка данных из файла: " + filename);
    } else {
        cout << "Файл с данными не найден\n";
    }
}

bool PipelineNetwork::pipeExists(int id) const { 
    return pipes.count(id) > 0; 
}

bool PipelineNetwork::stationExists(int id) const { 
    return stations.count(id) > 0; 
}

const unordered_map<int, Pipe>& PipelineNetwork::getPipes() const { 
    return pipes; 
}

const unordered_map<int, CompressorStation>& PipelineNetwork::getStations() const { 
    return stations; 
}