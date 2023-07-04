#pragma once
// Определение нового типа данных "состояние устройства"

typedef unsigned __int8 STATUS;

// Упаковка всех компонент в целое число

STATUS Pack(int speed, int level, bool direct);

// Извлечение компоненты скорости

int GetSpeed(STATUS state);

// Извлечение компоненты уровня

int GetLevel(STATUS state);

// Извлечение компоненты направления

bool GetDirect(STATUS state);

// Изменение компоненты скорости

STATUS ChangeSpeed(STATUS state, int speed);

// Изменение компоненты уровня

STATUS ChangeLevel(STATUS state, int level);

// Изменение компоненты направления

STATUS ChangeDirect(STATUS state, bool direct);

// Заполнение компонент случайными данными

STATUS RandomStatus();

// Печать всех компонент данных в десятичном формате

void PrintAllData(STATUS state);

// Печать упакованного числа в шестнадцатеричном формате

void PrintHexStatus(STATUS state);

// Печать упакованного числа в бинарном формате

void PrintBinStatus(STATUS state);

// Печать упакованного числа в выбранной системе счисления

void PrintRadixStatus(STATUS state);