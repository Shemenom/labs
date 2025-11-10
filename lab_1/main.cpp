#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pipe {
    string name;
    double lenght;
    int diametr;
    bool inRepair;
};

struct CompressorStation {
    string name;
    int numberWorkshop;
    int workingWorkshop;
    int classWorkshop;
};

void input_pipe(Pipe& pipe) {
    cout << "Название трубы: ";

    getline(cin >> ws, pipe.name);
    while (pipe.name.empty()) {
        cout << "Ошибка: некорректно введены данные: ";
        getline(cin, pipe.name);
    }

    cout << "Длина: ";
    while (!(cin >> pipe.lenght) || (pipe.lenght < 0) || (cin.peek() != '\n')) {
        cout << "Ошибка: корректно введите данные: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Диаметр: ";
    while (!(cin >> pipe.diametr) || (pipe.diametr < 0) || (cin.peek() != '\n')) {
        cout << "Ошибка: некорректно введены данные: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Состояние(0 - в ремонте, 1 - целый): ";
    while (!(cin >> pipe.inRepair) || (cin.peek() != '\n')) {
        cout << "Ошибка: некорректно введены данные: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
}

void edit_Repair_Pipe(Pipe& pipe) {
    cout << "Состояние(0 - в ремонте, 1 - целый): ";             
    while (!(cin >> pipe.inRepair)) {
        cout << "Ошибка: некорректно введены данные: ";
        cin.clear();
        cin.ignore();
    }
}

bool Pipe_created(const Pipe& pipe) {
    return !pipe.name.empty();
}


void ffile_1(Pipe& pipe, ifstream& file) {
    string line;
    getline(file >> ws, pipe.name); 
    file >> pipe.lenght;
    file >> pipe.diametr;
    file >> pipe.inRepair;
}
void save_Pipe(const Pipe& pipe, ofstream& file) {
    if (Pipe_created(pipe)) {
        file << "== Труба ==\n";
        file << pipe.name << "\n";
        file << pipe.lenght << "\n";
        file << pipe.diametr << "\n";
        file << pipe.inRepair << "\n";
    }
}

void input_CS(CompressorStation& CS) {
    cout << "Название КС: ";
    getline(cin >> ws, CS.name);
    while (CS.name.empty()) {
        cout << "Ошибка: некорректно введены данные: ";
        getline(cin, CS.name);
    }

    cout << "Количество цехов: ";
    while (!(cin >> CS.numberWorkshop) || (CS.numberWorkshop <= 0) || (cin.peek() != '\n')) {
        cout << "Ошибка: некорректно введены данные: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Количество работающих цехов: ";
    while (!(cin >> CS.workingWorkshop) || (CS.workingWorkshop <= 0) || (CS.workingWorkshop > CS.numberWorkshop) ||  (cin.peek() != '\n')) {
        cout << "Ошибка: некорректно введены данные: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Класс станции (1 - 5): ";
    while (!(cin >> CS.classWorkshop) || (CS.classWorkshop <= 1) || (CS.classWorkshop >= 5) || (cin.peek() != '\n')) {
        cout << "Ошибка: некорректно введены данные: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
}

void edit_CS(CompressorStation& CS) {
    int n;
    cout << "Запуск цеха 1, остановка цeха -1: ";
    while (!(cin >> n) || (n != 1 && n != -1)) {
        cout << "Ошибка: некорректно введены данные: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    CS.workingWorkshop += n;
    cout << "Количество цехов: " << CS.workingWorkshop << endl;
}

bool StationCreated(const CompressorStation& CS) {
    return !CS.name.empty();
}

void view_Object_1( Pipe& pipe) {
    if (Pipe_created(pipe)) {
        cout << "\n === Труба === \n";
        cout << "Название: " << pipe.name << ", Длина: " << pipe.lenght << ", Диаметр: " << pipe.diametr << ", В ремонте?: " << pipe.inRepair<< endl; 
    } else cout << "\n Труба не создана \n";
}

void view_Object_2(CompressorStation& CS) {
    if (StationCreated(CS)) {
        cout << "\n == Компрессорная станция == \n";
        cout << "Название: " << CS.name << ", Количество цехов: " << CS.numberWorkshop << ", Количество работающих цехов: " << CS.workingWorkshop << ", Класс станции: " << CS.classWorkshop << endl;
    } else cout << "\n КС не создана \n";
}

void display_Menu() {
    cout << "\n=== Меню управления трубопроводом ===\n";
    cout << "1. Добавить трубу\n";
    cout << "2. Добавить КС\n";
    cout << "3. Просмотр всех объектов\n";
    cout << "4. Редактировать трубу\n";
    cout << "5. Редактировать КС\n";
    cout << "6. Сохранить данные\n";
    cout << "7. Загрузить данные\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

void save_CS(const CompressorStation& CS, ofstream& file) {
    if (StationCreated(CS)) {
        file << "== КС ==\n";
        file << CS.name << "\n";
        file << CS.numberWorkshop << "\n";
        file << CS.workingWorkshop << "\n";
        file << CS.classWorkshop << "\n";
    }
}

void ffile_2(CompressorStation& CS, ifstream& file) {
    string line;
    getline(file >> ws, CS.name);
    file >> CS.numberWorkshop;
    file >> CS.workingWorkshop;
    file >> CS.classWorkshop;
}


int main() {
    Pipe pipe;
    CompressorStation CS;
    int choice;

    do {   
        display_Menu();
        cin >> choice;

        switch(choice) {
            case(1):
                input_pipe(pipe);
                cout << "Труба доваблена \n";
                break;
            case(2):
                input_CS(CS);
                cout << "КС добавлена \n";
                break;
            case(3):
                view_Object_1(pipe);
                view_Object_2(CS);
                break;
            case(4):
                if (Pipe_created(pipe)) 
                    edit_Repair_Pipe(pipe);
                else 
                    cout << "== Создайте трубу ===\n";
                break;
            case(5):
                if (StationCreated(CS)) edit_CS(CS);
                else cout << " == Создайте КС ==\n";
                break;
            case(6): {
                ofstream file("test.txt");
                if (file.is_open()) {
                    if (Pipe_created(pipe)) {
                        save_Pipe(pipe, file);
                    } else {
                        cout << "Труба не была создана \n";
                    }

                    if (StationCreated(CS)) {
                        save_CS(CS,file);
                        file.close();
                    } else {
                        cout << "КС не была создана \n";
                        file.close();
                    }
                }  
                cout << "\nДанные сохранены в файл\n";
                break;
            }
            case (7): {
                ifstream file("test.txt");
                if (file.is_open()) {
                    string line;
                    while (getline(file, line)) {
                        if (line == "== Труба ==") {
                            ffile_1(pipe, file);
                        }
                        else if (line == "== КС ==") {
                            ffile_2(CS, file);
                        }
                    }
                    file.close();
                    cout << "\nДанные загружены из файла\n";
                } else {
                    cout << "Ошибка: не удалось открыть файл для чтения\n";
                }
                break;
            }
            case(0):
                cout << "выход из программы";
                break;  
            default:
                cout << "\nНеверный ввод, введите число от 1 до 7\n";
            
        }

    } while ( choice != 0);
            display_Menu();

    return 0;
}