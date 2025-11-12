#include "PipelineNetwork.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Utils.h"

using namespace std;

PipelineNetwork::PipelineNetwork() : nextPipeId(1), nextStationId(1) {
    LOG_ACTION("Создана сеть трубопроводов");
}

void PipelineNetwork::addPipe() {
    LOG_FUNCTION_START();
    
    Pipe pipe(nextPipeId++);
    inputPipeData(pipe);
    pipes[pipe.getId()] = pipe;
    
    cout << "Труба добавлена (ID: " << pipe.getId() << ")\n";
    LOG_OBJECT_CREATION("Труба", pipe.getId());
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::inputPipeData(Pipe& pipe) {
    LOG_FUNCTION_START();
    
    cout << "Название трубы: ";
    pipe.setName();

    cout << "Длина: ";
    double length = GetCorrectNumber(0.1, 10000.0);
    pipe.setLength(length);

    cout << "Диаметр: ";
    int diameter = GetCorrectNumber(1, 5000);
    pipe.setDiameter(diameter);

    cout << "Состояние (0 - в ремонте, 1 - работает): ";
    bool inRepair;
    cin >> inRepair;
    pipe.setInRepair(inRepair);

    LOG_FUNCTION_END();
}

void PipelineNetwork::editPipe(int id) {
    LOG_FUNCTION_START();
    
    if (pipes.count(id)) {
        LOG_ACTION("Редактирование трубы ID: " + to_string(id));
        inputPipeData(pipes[id]);
        cout << "Труба отредактирована\n";
        LOG_ACTION("Труба ID " + to_string(id) + " успешно отредактирована");
    } else {
        LOG_ERROR("Труба с ID " + to_string(id) + " не найдена");
        cout << "Труба с ID " << id << " не найдена\n";
    }
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::deletePipe(int id) {
    LOG_FUNCTION_START();
    
    if (pipes.count(id)) {
        pipes.erase(id);
        cout << "Труба удалена\n";
        LOG_OBJECT_DELETION("Труба", id);
    } else {
        LOG_ERROR("Труба с ID " + to_string(id) + " не найдена");
        cout << "Труба с ID " << id << " не найдена\n";
    }
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::addStation() {
    LOG_FUNCTION_START();
    
    CompressorStation station(nextStationId++);
    inputStationData(station);
    stations[station.getId()] = station;
    
    cout << "Компрессорная станция добавлена (ID: " << station.getId() << ")\n";
    LOG_OBJECT_CREATION("КомпрессорнаяСтанция", station.getId());
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::inputStationData(CompressorStation& station) {
    LOG_FUNCTION_START();
    
    cout << "Название КС: ";
    station.setName();

    cout << "Количество цехов: ";
    int numberWorkshop = GetCorrectNumber(1, 1000);
    station.setNumberWorkshop(numberWorkshop);

    cout << "Количество работающих цехов: ";
    int workingWorkshop = GetCorrectNumber(0, numberWorkshop);
    station.setWorkingWorkshop(workingWorkshop, station.getNumberWorkshop());

    cout << "Класс станции (1-5): ";
    int classWorkshop = GetCorrectNumber(1, 5);
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::editStation(int id) {
    LOG_FUNCTION_START();
    
    if (stations.count(id)) {
        LOG_ACTION("Редактирование станции ID: " + to_string(id));
        cout << "Запуск цеха (+1), остановка цеха (-1): ";
        int change;
        cin >> change;
        
        int currentWorking = stations[id].getWorkingWorkshop();
        int number = stations[id].getNumberWorkshop();
        int newWorking = currentWorking + change;
        
        if (newWorking >= 0 && newWorking <= number) {
            stations[id].setWorkingWorkshop(newWorking, number);
            cout << "Количество работающих цехов: " << stations[id].getWorkingWorkshop() << endl;
            LOG_ACTION("Станция ID " + to_string(id) + " работающих цехов изменено на: " + to_string(newWorking));
        } else {
            LOG_ERROR("Неверное количество цехов для станции ID: " + to_string(id));
            cout << "Недопустимое количество!\n";
        }
    } else {
        LOG_ERROR("Станция с ID " + to_string(id) + " не найдена");
        cout << "Станция с ID " << id << " не найдена\n";
    }
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::deleteStation(int id) {
    LOG_FUNCTION_START();
    
    if (stations.count(id)) {
        stations.erase(id);
        cout << "Станция удалена\n";
        LOG_OBJECT_DELETION("КомпрессорнаяСтанция", id);
    } else {
        LOG_ERROR("Станция с ID " + to_string(id) + " не найдена");
        cout << "Станция с ID " << id << " не найдена\n";
    }
    
    LOG_FUNCTION_END();
}

vector<int> PipelineNetwork::findPipesByName(const string& name) {
    LOG_FUNCTION_START();
    LOG_ACTION("Поиск труб по названию: " + name);
    
    vector<int> result;
    for (const auto& [id, pipe] : pipes) {
        if (pipe.getName().find(name) != string::npos) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(pipe.getId()) + ", Имя: " + pipe.getName());
        }
    }
    
    LOG_ACTION("Найдено " + to_string(result.size()) + " труб с названием содержащим: " + name);
    LOG_FUNCTION_END();
    return result;
}

vector<int> PipelineNetwork::findPipesByRepairStatus(bool inRepair) {
    LOG_FUNCTION_START();
    LOG_ACTION("Поиск труб по статусу ремонта: " + string(inRepair ? "в ремонте" : "работает"));
    
    vector<int> result;
    for (const auto& [id, pipe] : pipes) {
        if (pipe.isInRepair() == inRepair) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(pipe.getId()) + ", Имя: " + pipe.getName());
        }
    }

    LOG_ACTION("Найдено " + to_string(result.size()) + " труб с указанным статусом ремонта");
    LOG_FUNCTION_END();
    return result;
}

vector<int> PipelineNetwork::findStationsByName(const string& name) {
    LOG_FUNCTION_START();
    LOG_ACTION("Поиск станций по названию: " + name);
    
    vector<int> result;
    for (const auto& [id, station] : stations) {
        if (station.getName().find(name) != string::npos) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(station.getId()) + ", Имя: " + station.getName());
        }
    }
    
    LOG_ACTION("Найдено " + to_string(result.size()) + " станций с названием содержащим: " + name);
    LOG_FUNCTION_END();
    return result;
}
 
vector<int> PipelineNetwork::findStationsByUnusedPercentage(double minPercent) {
    LOG_FUNCTION_START();
    LOG_ACTION("Поиск станций по проценту незадействованных цехов >= " + to_string(minPercent) + "%");
    
    vector<int> result;
    for (const auto& [id, station] : stations) {
        if (station.getUnusedPercentage() >= minPercent) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(station.getId()) + ", Имя: " + station.getName());
        }
    }
    
    LOG_ACTION("Найдено " + to_string(result.size()) + " станций с процентом незадействованных цехов >= " + to_string(minPercent) + "%");
    LOG_FUNCTION_END();
    return result;
}

void PipelineNetwork::batchEditPipes(const vector<int>& pipeIds) {
    LOG_FUNCTION_START();
    
    if (pipeIds.empty()) {
        LOG_ACTION("Не найдено труб для пакетного редактирования");
        cout << "Нет труб для редактирования\n";
        return;
    }
    
    LOG_ACTION("Пакетное редактирование " + to_string(pipeIds.size()) + " труб");
    cout << "Найдено труб: " << pipeIds.size() << endl;
    cout << "Редактировать все (1) или выбрать конкретные (2)? ";
    int choice = GetCorrectNumber(1, 2);
    
    vector<int> pipesToEdit;
    if (choice == 1) {
        pipesToEdit = pipeIds;
        LOG_ACTION("Выбраны все трубы для редактирования");
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
        LOG_ACTION("Выбрано " + to_string(pipesToEdit.size()) + " конкретных труб для редактирования");
    }
    
    cout << "Новое состояние (0 - в ремонте, 1 - работает): ";
    bool newStatus;
    cin >> newStatus;
    
    for (int id : pipesToEdit) {
        pipes[id].setInRepair(newStatus);
    }
    
    cout << "Отредактировано труб: " << pipesToEdit.size() << endl;
    LOG_ACTION("Пакетное редактирование завершено: " + to_string(pipesToEdit.size()) + " труб статус изменен на: " + 
               string(newStatus ? "работает" : "в ремонте"));
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::viewAllObjects() {
    LOG_FUNCTION_START();
    
    cout << "\n=== ТРУБЫ ===\n";
    if (pipes.empty()) {
        cout << "Трубы не созданы\n";
        LOG_ACTION("Нет труб для отображения");
    } else {
        for (const auto& [id, pipe] : pipes) {
            cout << "ID: " << id << ", Название: " << pipe.getName()
                 << ", Длина: " << pipe.getLength()
                 << ", Диаметр: " << pipe.getDiameter()
                 << ", В ремонте: " << (pipe.isInRepair() ? "Да" : "Нет") << endl;
            LOG_ACTION("ID " + to_string(id) + " Название: " + pipe.getName() + ", Длина: " + to_string(pipe.getLength()) + ", Диаметр: " + to_string(pipe.getDiameter()) + "В ремонте: " + (pipe.isInRepair() ? "Да" : "Нет"));
        }
        LOG_ACTION("Отображено " + to_string(pipes.size()) + " труб");
    }
    
    cout << "\n=== КОМПРЕССОРНЫЕ СТАНЦИИ ===\n";
    if (stations.empty()) {
        cout << "КС не созданы\n";
        LOG_ACTION("Нет станций для отображения");
    } else {
        for (const auto& [id, station] : stations) {
            cout << "ID: " << id << ", Название: " << station.getName()
                 << ", Цехов: " << station.getNumberWorkshop() << "/" << station.getWorkingWorkshop()
                 << ", Незадействовано: " << fixed << setprecision(1) << station.getUnusedPercentage() << "%"
                 << ", Класс: " << station.getClassWorkshop() << endl;
            LOG_ACTION("ID " + to_string(id) + " Название: " + station.getName() + ", Цехов: " + to_string(station.getNumberWorkshop()) + "/" + to_string(station.getWorkingWorkshop()) +", Класс: " + to_string(station.getClassWorkshop()));
        }
        LOG_ACTION("Отображено " + to_string(stations.size()) + " станций");
    }
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::saveToFile_pipe(ofstream& file) {
    LOG_FUNCTION_START();
    
    file << "PIPES " << pipes.size() << endl;
    for (const auto& [id, pipe] : pipes) {
        file << "PIPE " << id << " "
             << pipe.getName() << " "
             << pipe.getLength() << " "
             << pipe.getDiameter() << " "
             << pipe.isInRepair() << endl;
    }

    LOG_ACTION("Сохранено " + to_string(pipes.size()) + " труб в файл");
    LOG_FUNCTION_END();
}

void PipelineNetwork::saveToFile_CS(ofstream& file) {
    LOG_FUNCTION_START();
    
    file << "STATIONS " << stations.size() << endl;
    for (const auto& [id, station] : stations) {
        file << "STATION " << id << " "
             << station.getName() << " "
             << station.getNumberWorkshop() << " "
             << station.getWorkingWorkshop() << " "
             << station.getClassWorkshop() << endl;
    }
    
    LOG_ACTION("Сохранено " + to_string(stations.size()) + " станций в файл");
    LOG_FUNCTION_END();
}

void PipelineNetwork::loadFromFile_pipe(ifstream& file) {
    LOG_FUNCTION_START();
    
    string type;
    int count;
    
    file >> type >> count;
    if (type == "PIPES") {
        LOG_ACTION("Загрузка " + to_string(count) + " труб из файла");
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
        LOG_ACTION("Успешно загружено " + to_string(count) + " труб");
    }
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::loadFromFile_CS(ifstream& file) {
    LOG_FUNCTION_START();
    
    string type;
    int count;
    
    file >> type >> count;
    if (type == "STATIONS") {
        LOG_ACTION("Загрузка " + to_string(count) + " станций из файла");
        for (int i = 0; i < count; i++) {
            file >> type;
            int id;
            file >>id;
            
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
        LOG_ACTION("Успешно загружено " + to_string(count) + " станций");
    }
    
    LOG_FUNCTION_END();
}