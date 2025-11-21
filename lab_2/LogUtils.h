#pragma once
#include <string>
#include "Logger.h"
#include <iostream>

using namespace std;

#define INPUT_LINE_LOG(in, str) \
        getline(in >> ws, str); \
        logger.log(str); \

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
    return x;
}