#include "PipelineNetwork.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Utils.h"


using namespace std;

PipelineNetwork::PipelineNetwork() : nextPipeId(1), nextStationId(1), gasNetwork(pipes, stations){
    LOG_ACTION("Создана сеть трубопроводов");
}

void PipelineNetwork::addPipe() {
    Pipe pipe(nextPipeId++);
    inputPipeData(pipe);
    pipes[pipe.getId()] = pipe;
    
    cout << "Труба добавлена (ID: " << pipe.getId() << ")\n";
}

void PipelineNetwork::inputPipeData(Pipe& pipe) {    
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
}

void PipelineNetwork::editPipe(int id) {
    
    if (pipes.count(id)) {
        LOG_ACTION("Редактирование трубы ID: " + to_string(id));
        inputPipeData(pipes[id]);
        cout << "Труба отредактирована\n";
        LOG_ACTION("Труба ID " + to_string(id) + " успешно отредактирована");
    } else {
        LOG_ERROR("Труба с ID " + to_string(id) + " не найдена");
        cout << "Труба с ID " << id << " не найдена\n";
    }

}

void PipelineNetwork::deletePipe(int id) {

    if (pipes.count(id)) {
        pipes.erase(id);
        cout << "Труба удалена\n";
        LOG_OBJECT_DELETION("Труба", id);
    } else {
        LOG_ERROR("Труба с ID " + to_string(id) + " не найдена");
        cout << "Труба с ID " << id << " не найдена\n";
    }
}

void PipelineNetwork::addStation() {

    
    CompressorStation station(nextStationId++);
    inputStationData(station);
    stations[station.getId()] = station;
    
    cout << "Компрессорная станция добавлена (ID: " << station.getId() << ")\n";
    LOG_OBJECT_CREATION("КомпрессорнаяСтанция", station.getId());
    
}

void PipelineNetwork::inputStationData(CompressorStation& station) {
    
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
    
}

void PipelineNetwork::editStation(int id) {
    
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
    
}

void PipelineNetwork::deleteStation(int id) {
    
    if (stations.count(id)) {
        stations.erase(id);
        cout << "Станция удалена\n";
        LOG_OBJECT_DELETION("КомпрессорнаяСтанция", id);
    } else {
        LOG_ERROR("Станция с ID " + to_string(id) + " не найдена");
        cout << "Станция с ID " << id << " не найдена\n";
    }
    
}

vector<int> PipelineNetwork::findPipesByName(const string& name) {
    LOG_ACTION("Поиск труб по названию: " + name);
    
    vector<int> result;
    for (const auto& [id, pipe] : pipes) {
        if (pipe.getName().find(name) != string::npos) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(pipe.getId()) + ", Имя: " + pipe.getName());
        }
    }
    
    LOG_ACTION("Найдено " + to_string(result.size()) + " труб с названием содержащим: " + name);
    return result;
}

vector<int> PipelineNetwork::findPipesByRepairStatus(bool inRepair) {
    LOG_ACTION("Поиск труб по статусу ремонта: " + string(inRepair ? "в ремонте" : "работает"));
    
    vector<int> result;
    for (const auto& [id, pipe] : pipes) {
        if (pipe.isInRepair() == inRepair) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(pipe.getId()) + ", Имя: " + pipe.getName());
        }
    }

    LOG_ACTION("Найдено " + to_string(result.size()) + " труб с указанным статусом ремонта");
    return result;
}

vector<int> PipelineNetwork::findStationsByName(const string& name) {
    LOG_ACTION("Поиск станций по названию: " + name);
    
    vector<int> result;
    for (const auto& [id, station] : stations) {
        if (station.getName().find(name) != string::npos) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(station.getId()) + ", Имя: " + station.getName());
        }
    }
    
    LOG_ACTION("Найдено " + to_string(result.size()) + " станций с названием содержащим: " + name);
    return result;
}
 
vector<int> PipelineNetwork::findStationsByUnusedPercentage(double minPercent) {
    LOG_ACTION("Поиск станций по проценту незадействованных цехов >= " + to_string(minPercent) + "%");
    
    vector<int> result;
    for (const auto& [id, station] : stations) {
        if (station.getUnusedPercentage() >= minPercent) {
            result.push_back(id);
            LOG_ACTION("ID " + to_string(station.getId()) + ", Имя: " + station.getName());
        }
    }
    
    LOG_ACTION("Найдено " + to_string(result.size()) + " станций с процентом незадействованных цехов >= " + to_string(minPercent) + "%");
    return result;
}

void PipelineNetwork::batchEditPipes(const vector<int>& pipeIds) {
    
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
    LOG_ACTION("Пакетное редактирование завершено: " + to_string(pipesToEdit.size()) + " труб статус изменен на: " + string(newStatus ? "работает" : "в ремонте"));
    
    LOG_FUNCTION_END();
}

void PipelineNetwork::viewAllObjects_pipe() {
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

    LOG_FUNCTION_END();
}
 
void PipelineNetwork::viewAllObjects_CS() {
    LOG_FUNCTION_START();

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


void PipelineNetwork::connectStations() {
    LOG_ACTION("Запуск процесса соединения КС");
    
    cout << "=== СОЕДИНЕНИЕ КОМПРЕССОРНЫХ СТАНЦИЙ ===\n";
    
    cout << "Введите ID КС источника: ";
    int sourceId = GetCorrectNumber(1, 1000);
    
    cout << "Введите ID КС назначения: ";
    int destinationId = GetCorrectNumber(1, 1000);
    
    cout << "Введите диаметр трубы (500, 700, 1000, 1400): ";
    int diameter = GetCorrectNumber(500, 1400);
    
    // Проверка допустимых диаметров
    if (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
        cout << "Ошибка: допустимые диаметры: 500, 700, 1000, 1400 мм!\n";
        LOG_ERROR("Введен недопустимый диаметр: " + to_string(diameter));
        return;
    }
    
    gasNetwork.connectStations(sourceId, destinationId, diameter);
}

void PipelineNetwork::disconnectStations() {
    LOG_ACTION("Запуск процесса разъединения КС");
    
    cout << "=== РАЗЪЕДИНЕНИЕ КОМПРЕССОРНЫХ СТАНЦИЙ ===\n";
    
    cout << "Введите ID трубы для разъединения: ";
    int pipeId = GetCorrectNumber(1, 1000);
    
    gasNetwork.disconnectStations(pipeId);
}

void PipelineNetwork::viewNetwork() {
    LOG_ACTION("Просмотр газовой сети");
    gasNetwork.viewNetwork();
}

void PipelineNetwork::topologicalSort() {
    LOG_ACTION("Запуск топологической сортировки");
    
    if (gasNetwork.checkCycles()) {
        cout << "Внимание: в сети обнаружены циклы! Топологическая сортировка невозможна.\n";
        LOG_ERROR("Попытка топологической сортировки при наличии циклов");
        return;
    }
    
    vector<int> sorted = gasNetwork.topologicalSort();
    
    cout << "\n=== ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА ===\n";
    if (sorted.empty()) {
        cout << "Сеть пуста или нет соединений\n";
    } else {
        cout << "Порядок обработки КС: ";
        for (size_t i = 0; i < sorted.size(); ++i) {
            cout << "КС " << sorted[i];
            if (i != sorted.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

void PipelineNetwork::checkNetworkCycles() {
    LOG_ACTION("Проверка сети на циклы");
    
    if (gasNetwork.checkCycles()) {
        cout << "В сети обнаружены циклы!\n";
    } else {
        cout << "Циклы не обнаружены. Сеть ациклична.\n";
    }
}