#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "PipelineNetwork.h"
#include "Utils.h"
#include "LogUtils.h"

using namespace std;

void displayMenu() {
    cout << "\n=== МЕНЮ УПРАВЛЕНИЯ ТРУБОПРОВОДОМ ===\n";
    cout << "1. Добавить трубу\n";
    cout << "2. Добавить КС\n";
    cout << "3. Просмотр всех объектов\n";
    cout << "4. Редактировать трубу\n";
    cout << "5. Редактировать КС\n";
    cout << "6. Удалить трубу\n";
    cout << "7. Удалить КС\n";
    cout << "8. Поиск труб\n";
    cout << "9. Поиск КС\n";
    cout << "10. Пакетное редактирование труб\n";
    cout << "11. Сохранить данные\n";
    cout << "12. Загрузить данные\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {

    PipelineNetwork network;
    int choice;
    
    do {
        displayMenu();

        while (!(cin >> choice) || (choice < 0 || choice > 12)) {
            cout << "Ошибка! Введите число от 0 до 12: ";
            cin.clear(); 
            cin.ignore(10000, '\n'); 
        }
        
        logger.log("Пользователь выбрал пункт меню: " + to_string(choice));
        
        switch (choice) {
            case 1:
                network.addPipe();
                break;
                
            case 2:
                network.addStation();
                break;
                
            case 3:
                network.viewAllObjects_pipe();
                network.viewAllObjects_CS();
                break;
                
            case 4: {
                cout << "Введите ID трубы для редактирования: ";
                int id = GetCorrectNumberLog(1, 1000);
                network.editPipe(id);
                break;
            }
                
            case 5: {
                cout << "Введите ID КС для редактирования: ";
                int id = GetCorrectNumberLog(1, 1000);
                network.editStation(id);
                break;
            }
                
            case 6: {
                cout << "Введите ID трубы для удаления: ";
                int id = GetCorrectNumberLog(1, 1000);
                network.deletePipe(id);
                break;
            }
                
            case 7: {
                cout << "Введите ID КС для удаления: ";
                int id = GetCorrectNumberLog(1, 1000);
                network.deleteStation(id);
                break;
            }
                
            case 8: {
                cout << "Поиск труб по:\n";
                cout << "1 - названию, 2 - признаку 'в ремонте': ";
                int searchType = GetCorrectNumberLog(1, 2);
                
                vector<int> foundPipes;
                if (searchType == 1) {
                    cout << "Введите часть названия: ";
                    string name;
                    INPUT_LINE_LOG(cin, name);
                    foundPipes = network.findPipesByName(name);
                } else if (searchType == 2) {
                    cout << "В ремонте (0 - да, 1 - нет): ";
                    bool status;
                    cin >> status;
                    foundPipes = network.findPipesByRepairStatus(status);
                }
                
                cout << "Найдено труб: " << foundPipes.size() << endl;
                break;
            }
                
            case 9: {
                cout << "Поиск КС по:\n";
                cout << "1 - названию, 2 - проценту незадействованных цехов: ";
                int searchType = GetCorrectNumberLog(1, 2);
                
                vector<int> foundStations;
                if (searchType == 1) {
                    cout << "Введите часть названия: ";
                    string name;
                    INPUT_LINE_LOG(cin, name);
                    foundStations = network.findStationsByName(name);
                } else if (searchType == 2) {
                    cout << "Минимальный процент незадействованных цехов: ";
                    double percent = GetCorrectNumberLog(0.0, 100.0);
                    foundStations = network.findStationsByUnusedPercentage(percent);
                }
                
                cout << "Найдено КС: " << foundStations.size() << endl;
                break;
            }
                
            case 10: {
                cout << "Пакетное редактирование труб по:\n";
                cout << "1 - названию, 2 - признаку 'в ремонте': ";
                int searchType = GetCorrectNumberLog(1, 2);
                
                vector<int> foundPipes;
                if (searchType == 1) {
                    cout << "Введите часть названия: ";
                    string name;
                    INPUT_LINE_LOG(cin, name);
                    foundPipes = network.findPipesByName(name);
                } else if (searchType == 2) {
                    cout << "В ремонте (0 - да, 1 - нет): ";
                    bool status;
                    cin >> status;
                    foundPipes = network.findPipesByRepairStatus(status);
                }
                
                network.batchEditPipes(foundPipes);
                break;
            }
                
            case 11: {
                ofstream file("data.txt");
                if (file.is_open()) {
                    network.saveToFile_pipe(file);
                    network.saveToFile_CS(file);
                    file.close();
                    cout << "Данные сохранены в файл\n";
                    logger.log("Данные успешно сохранены в файл");
                } else {
                    cout << "Ошибка открытия файла для записи\n";
                    logger.log("ОШИБКА: Не удалось открыть файл для записи");
                }
                break;
            }

            case 12: {
                ifstream file("data.txt");
                if (file.is_open()) {
                    network.loadFromFile_pipe(file);
                    network.loadFromFile_CS(file);
                    file.close();
                    cout << "Данные загружены\n";
                    logger.log("Данные успешно загружены из файла");
                } else {
                    cout << "Ошибка открытия файла для чтения\n";
                    logger.log("ОШИБКА: Не удалось открыть файл для чтения");
                }
                break;
            }
                
            case 0:
                cout << "Выход из программы\n";
                logger.log("Пользователь завершил программу");
                break;
        }
                
    } while (choice != 0);
    
    return 0;
}