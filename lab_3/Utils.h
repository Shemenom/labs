#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Макрос для ввода строки
#define INPUT_LINE(in, str) \
        getline(in >> ws, str); \

// Макрос для вывода параметра
#define PRINT_PARAM(out, x) \
        out << #x << "=" << x << endl; \

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
    }
    return x;
}