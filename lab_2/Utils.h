#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// ========== МАКРОСЫ ==========

// Макрос для ввода строки с логированием
#define INPUT_LINE(in, str) \
    do { \
        getline(in >> ws, str); \
        cerr << "ВВОД: " << str << endl; \
        if (logger.is_open()) { \
            logger << "ВВОД_ПОЛЬЗОВАТЕЛЯ: " << str << endl; \
        } \
    } while(0)

// Макрос для вывода параметра с логированием  
#define PRINT_PARAM(out, x) \
    do { \
        out << #x << "=" << x << endl; \
        if (logger.is_open()) { \
            logger << "ВЫВОД_ПАРАМЕТРА: " << #x << "=" << x << endl; \
        } \
    } while(0)

// Макрос для логирования действий
#define LOG_ACTION(action) \
    do { \
        if (logger.is_open()) { \
            logger << "ДЕЙСТВИЕ: " << action << endl; \
        } \
        cerr << "ЛОГ: " << action << endl; \
    } while(0)

// Макрос для логирования ошибок
#define LOG_ERROR(error) \
    do { \
        if (logger.is_open()) { \
            logger << "ОШИБКА: " << error << endl; \
        } \
        cerr << "ОШИБКА: " << error << endl; \
    } while(0)

// Макрос для логирования начала функции
#define LOG_FUNCTION_START() \
    LOG_ACTION(string("НАЧАЛО: ") + __FUNCTION__)

// Макрос для логирования завершения функции
#define LOG_FUNCTION_END() \
    LOG_ACTION(string("КОНЕЦ: ") + __FUNCTION__)

// Макрос для логирования создания объекта
#define LOG_OBJECT_CREATION(type, id) \
    LOG_ACTION(string("СОЗДАНО: ") + type + " ID: " + to_string(id))

// Макрос для логирования удаления объекта
#define LOG_OBJECT_DELETION(type, id) \
    LOG_ACTION(string("УДАЛЕНО: ") + type + " ID: " + to_string(id))

// ========== КЛАССЫ ==========

// Класс для перенаправления вывода
class redirect_output_wrapper
{
    ostream& stream;
    streambuf* const old_buf;
public:
    redirect_output_wrapper(ostream& src)
        : old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    
    void redirect(ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};

// ========== ШАБЛОННЫЕ ФУНКЦИИ ==========

// Шаблонная функция для получения корректного числа в диапазоне
template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((cin >> x).fail() || cin.peek() != '\n' || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите число (" << min << "-" << max << "):";
        
        if (logger.is_open()) {
            logger << "ОШИБКА_ВВОДА: Введено неверное число, запрос нового ввода" << endl;
        }
    }
    
    cerr << "ВВОД: " << x << endl;
    if (logger.is_open()) {
        logger << "ВВОД_ЧИСЛА: " << x << " (диапазон: " << min << "-" << max << ")" << endl;
    }
    
    return x;
}