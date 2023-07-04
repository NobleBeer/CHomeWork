#include "..\PackBits\Global.h"
#include <stdio.h>

#include <stdlib.h>


#pragma warning(disable: 4996)

/* Функция печати всех компонент данных в десятичном формате

*/

void PrintAllData(STATUS state)

{

	printf("\n Скорость = %d \n Уровень = %d \n Направление = %d ",

		GetSpeed(state), GetLevel(state), GetDirect(state));

}

/* Функция печати упакованного числа в шестнадцатеричном формате

*/

void PrintHexStatus(STATUS state)

{

	printf("Hex=0x%X Oct=0%o Dec=%d", state, state, state);

}

/* Функция заполнения компонент случайными данными

*/

STATUS RandomStatus()

{

	return Pack(rand() % 8, rand() % 15, rand() % 2);

}

/* Функций печати упакованного числа в бинарном формате

*/

void PrintBinStatus(STATUS state)

{

	// Объявить переменную маски для проверки битов и переменную счётчика битов

	int rotor, i;

	// В цикле свигать бит маски в состоянии "1" вправо на один бит

	for (i = 1, rotor = 0x80; rotor != 0; rotor >>= 1, i++)

	{

		// Сравнивать бит маски с битом упакованного числа

		putchar(((state & rotor) ? '1' : '0'));

		// Отделить пробелом группу из четырех бит

		if (i == 4)

		{

			i = 0;

			putchar(' ');

		}

	}

	// Вывести шестнадцатеричное представление числа

	printf(" (0x%X)", state);

}

/* Функция печати упакованного числа в выбранной системе счисления

*/

void PrintRadixStatus(STATUS state)

{

	char buffer[66]; // Символьный буфер для сохранения представления

	int check, radix; // Статус ввода и основание системы счисления

	// Ввести основание системы счисления

	printf("\nВведите основание системы счисления [2..36]:>");

	check = scanf("%d", &radix);

	// Проверить коректность ввода основания и допустимость диапазона значений

	if (check != 1 || fgetchar() != 10 || radix < 2 || radix > 36)

	{

		fflush(stdin);

		printf("Ошибка: Некорректное значение основания СС\n");

		return;

	}

	// Преобразовать упакованное число в строку по основанию системы счисления

	itoa(state, buffer, radix);

	// Вывести результат преобразования

	printf("\nОснование(%d)Статус = %s", radix, buffer);

}