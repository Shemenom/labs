#include <iostream>
#include <string>
#include <vector>
#include "PipelineNetwork.h"
#include "Logger.h"

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
        cin >> choice;
        cin.ignore(100, '\n');
        
        switch (choice) {
            case 1:
                network.addPipe();
                break;
                
            case 2:
                network.addStation();
                break;
                
            case 3:
                network.viewAllObjects();
                break;
                
            case 4: {
                cout << "Введите ID трубы для редактирования: ";
                int id;
                cin >> id;
                network.editPipe(id);
                break;
            }
                
            case 5: {
                cout << "Введите ID КС для редактирования: ";
                int id;
                cin >> id;
                network.editStation(id);
                break;
            }
                
            case 6: {
                cout << "Введите ID трубы для удаления: ";
                int id;
                cin >> id;
                network.deletePipe(id);
                break;
            }
                
            case 7: {
                cout << "Введите ID КС для удаления: ";
                int id;
                cin >> id;
                network.deleteStation(id);
                break;
            }
                
            case 8: {
                cout << "Поиск труб по:\n";
                cout << "1 - названию, 2 - признаку 'в ремонте': ";
                int searchType;
                cin >> searchType;
                cin.ignore(100, '\n');
                
                vector<int> foundPipes;
                if (searchType == 1) {
                    cout << "Введите часть названия: ";
                    string name;
                    getline(cin, name);
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
                int searchType;
                cin >> searchType;
                cin.ignore(100, '\n');
                
                vector<int> foundStations;
                if (searchType == 1) {
                    cout << "Введите часть названия: ";
                    string name;
                    getline(cin, name);
                    foundStations = network.findStationsByName(name);
                } else if (searchType == 2) {
                    cout << "Минимальный процент незадействованных цехов: ";
                    double percent;
                    cin >> percent;
                    foundStations = network.findStationsByUnusedPercentage(percent);
                }
                
                cout << "Найдено КС: " << foundStations.size() << endl;
                break;
            }
                
            case 10: {
                cout << "Пакетное редактирование труб по:\n";
                cout << "1 - названию, 2 - признаку 'в ремонте': ";
                int searchType;
                cin >> searchType;
                cin.ignore(100, '\n');
                
                vector<int> foundPipes;
                if (searchType == 1) {
                    cout << "Введите часть названия: ";
                    string name;
                    getline(cin, name);
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
                    network.saveToFile_pipe();
                    network.saveToFile_CS();
                    file.close();
                    cout << "Данные сохранены в файл";

                } else {
                    cout << "Ошибка открытия файла для записи";
                }
                break;
            }

            case 12: {
                string filename = "data.txt";
                network.loadFromFile(filename);
                break;
            }
                
            case 0:
                cout << "Выход из программы\n";
                break;
                
            default:
                cout << "Неверный ввод, введите число от 0 до 12\n";
        }
        
    } while (choice != 0);
    
    return 0;
}