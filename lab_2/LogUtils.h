#pragma once
#include <string>
#include "Logger.h"
#include <iostream>

using namespace std;

#define INPUT_LINE_LOG(in, str) \
        getline(in >> ws, str); \
        logger.log(str); \

#define LOG_ACTION(action) // ничего
#define LOG_ERROR(error) // ничего  
#define LOG_FUNCTION_START() // ничего
#define LOG_FUNCTION_END() // ничего
#define LOG_OBJECT_CREATION(type, id) // ничего
#define LOG_OBJECT_DELETION(type, id) // ничего

template <typename T>
T GetCorrectNumberLog(T min, T max)
{
    T x;
    while ((cin >> x).fail() || cin.peek() != '\n' || x < min || x > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите число (" << min << "-" << max << "):";
    }
    
    logger.log(to_string(x));
    return x;
}