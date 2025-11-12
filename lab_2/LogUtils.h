#pragma once
#include <string>
#include "Logger.h"
#include <iostream>

using namespace std;

// Макрос для ввода строки с логированием
#define INPUT_LINE_LOG(in, str) \
    do { \
        getline(in >> ws, str); \
        logger.log("ВВОД_ПОЛЬЗОВАТЕЛЯ: " + str); \
    } while(0)

// Макрос для вывода параметра с логированием  
#define PRINT_PARAM_LOG(out, x) \
    do { \
        out << #x << "=" << x << endl; \
        logger.log("ВЫВОД_ПАРАМЕТРА: " + string(#x) + "=" + to_string(x)); \
    } while(0)

// Макрос для логирования действий
#define LOG_ACTION(action) \
    do { \
        logger.log(string(action)); \
    } while(0)

// Макрос для логирования ошибок
#define LOG_ERROR(error) \
    do { \
        logger.log("ОШИБКА: " + string(error)); \
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

// Шаблонная функция для получения корректного числа с логированием
template <typename T>
T GetCorrectNumberLog(T min, T max)
{
    T x;
    while ((cin >> x).fail() || cin.peek() != '\n' || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите число (" << min << "-" << max << "):";
        logger.log("ОШИБКА_ВВОДА: Введено неверное число, запрос нового ввода");
    }
    
    logger.log("ВВОД_ЧИСЛА: " + to_string(x) + " (диапазон: " + to_string(min) + "-" + to_string(max) + ")");
    return x;
}