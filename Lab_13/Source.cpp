#include <time.h>     // библиотека работы с таймером
#include <stdio.h>    // библиотека ввода-вывода
#include <stdlib.h>   // библиотека системных функций
#include <locale.h>   // библиотека языковой локализации

// Минимальный размер матрицы
const int minsize = 2;
// Максимальный размер матрицы
const int maxsize = 12;
// Минимальный диапазон случайных чисел
const int min_range = 8;
// Максимальный диапазон случайных чисел
const int max_range = 180;
// Длина имени файла
const int namelen = 66;

int k = 0; // Круги
int p = 0; // Шаблоны для ряда чисел 
double oversum = 0.0;
double undersum = 0.0;
double control = 0.0;

/*
   Функция резервирует память под матрицу и возвращает указатель на неё
*/
int** CreateMatrix(int rows, int cols)
{
    // Проверить размеры матрицы по измерениям
    if (rows < minsize || rows > maxsize ||
        cols < minsize || cols > maxsize) return NULL;

    // Зарезервировать память под одномерный массив указателей
    int** matrix = new int* [rows];

    // Убедиться, что память выделена
    if (matrix == NULL) return NULL;

    // Перемещаться по массиву указателей
    for (register int row = 0; row < rows; row++)
    {
        // Зарезервировать память под одномерный вектор-массив для хранения
        // значений матрицы и присоединить его к одномерному массиву указателей
        matrix[row] = new int[cols];

        // Убедиться, что память под вектор-массив выделена  
        if (matrix[row] == NULL)
        {
            // Удалить ранее выделенные одномерные массивы
            while ((--row) >= 0)
                // Удалить одномерные вектор-массивы
                delete[] matrix[row];
            // Удалить одномерный массив указателей
            delete[] matrix;
            // Вернуть результат в случае неуспеха 
            return NULL;
        }
    }  // Вернуть адрес матрицы при успехе
    return matrix;
}

static long Sv(int n)
{
    for (i=1; i<=) 
    return n;
}


/*
   Функция освобождает память из под матрицы и обнуляет управляющие переменные
*/
void DeleteMatrix(int& rows, int& cols, int**& matrix)
{
    // Убедиться, что память выделена
    if (matrix != NULL)
    {
        // Перемещаться по массиву указателей
        for (register int row = 0; row < rows; row++)
            // Удалять одномерные вектор-массивы ячеек, присоединенные к указателям
            delete[] matrix[row];
        // Удалить одномерный массив указателей
        delete[] matrix;
    }
    // Обнулить информацию о матрице
    matrix = NULL;
    rows = 0;
    cols = 0;
}

#pragma warning(disable: 4996)
/*
   Функция организует ввод значения в заданном диапазоне
*/
bool EntryValue(char* name, int& value, int min = INT_MAX, int max = INT_MIN)
{
    // Число для ввода, статус проверки ввода
    int temp, check;
    // Вывести информацию о параметре
    if (name != NULL) printf("\nВведите %s", name);

    // Если диапазон не задан, то любое значение
    if (min == INT_MAX && max == INT_MIN)
    {
        printf(":>");
        min = INT_MIN;
        max = INT_MAX;
    }
    // Если задан только максимум, то значение может быть не больше заданного
    else if (min == INT_MAX && max != INT_MIN)
    {
        printf(" [< %d]:>", max);
        min = INT_MIN;
    }
    // Если задан только минимум, то значение может быть не меньше заданного
    else if (min != INT_MAX && max == INT_MIN)
    {
        printf(" [> %d]:>", min);
        max = INT_MAX;
    }
    // Если задан максимум и минимум, то значение находится в диапазоне
    else
        printf(" [%d..%d]:>", min, max);

    // Ввести значение числа
    check = scanf("%d", &temp);

    // Проверить корректность ввода и допустимость диапазона
    if (check != 1 || fgetchar() != 10 || temp < min || temp > max)
    {
        fflush(stdin);
        // Вывести сообщение об ошибке
        printf("Ошибка: Некорректный ввод для %s\n", ((name) ? name : "значения"));
        return false;
    }
    else
    {
        // Вернуть значене через аргумент
        value = temp;
        return true;
    }
}
/*
   Статическая функция вычисляет число ряда по номеру
*/
static int number = 0;
static int NextNumber()
{
    return (number += 2);
}
/*
   Главная функция. Реализует ввод, проверку, интерфейс с пользователем.
*/
void main()
{
    int   pulley[] = { 0, 0 };          // Шапка параметров матрицы {строк, столбцов}
    int& rows = pulley[0];            // Количество строк матрицы
    int& cols = pulley[1];            // Количество столбцов матрицы
    char  ch = '\0';                    // Команда меню
    int   row, col, idx;                // Индекс строки, индекс столбца, просто индекс
    int   check, value;                 // Статус ввода, введенное значение
    int   range = max_range;            // Ширина диапазона случайных чисел
    int** matrix = NULL;                // Указатель на матрицу
    char  filename[namelen];            // Имя файла
    FILE* fp;                           // Указатель на файловой поток

    // Для сообщений на русском языке
    setlocale(LC_ALL, "Russian");
    printf("Лаба: Двумерные массивы( ");

    // Определить константу для шапки параметров матрицы
    const int heap = sizeof(pulley) / sizeof(int);

    // Инициализация генератора случайных чисел
    srand((unsigned int)time(NULL));

    do {                                // Обработка команд меню
        switch (ch)
        {
        case 'C':     // Ввод размера и резервирование матрицы
        case 'c':
            // Ввести количество строк матрицы и проверить корректность ввода
            if (!EntryValue("количество строк", row, minsize, maxsize)) break;

            // Ввести количество столбцов матрицы и проверить корректность ввода
            if (!EntryValue("количество столбцов", col, minsize, maxsize)) break;

            // Удалить текущую матрицу
            DeleteMatrix(rows, cols, matrix);

            // Зарезервировать память под матрицу для заданного размера
            if ((matrix = CreateMatrix(row, col)) == NULL)
            {
                printf("Ошибка: Недостаточно памяти\n");
                break;
            }

            // Запомнить новый размер матрицы
            rows = row;
            cols = col;
            // Перейти к заполнению матрицы

        case 'R':     // Заполнение матрицы случайными значениями
        case 'r':
            // Перемещаться по строкам матрицы
            for (row = 0; row < rows; row++)
                // Перемещаться по столбцам матрицы
                for (col = 0; col < cols; col++)
                    // Генерировать и запоминать случайные значения
                    matrix[row][col] = ((rand() % 2) ? +1 : -1) * (rand() % range);
            // Перейти к отображению текущей матрицы

        case 'P':     // Печать элементов матрицы
        case 'p':
            printf("\nТекущая матрица [%dx%d] %s\n", rows, cols,
                ((matrix) ? "содержит:" : "пуста!"));

            // Перемещаться по строкам матрицы
            for (row = 0; row < rows; row++)
            {
                printf("\n");
                // Перемещаться по столбцам матрицы
                for (col = 0; col < cols; col++)
                    // Выводить значение ячейки матрицы
                    printf("%6d", matrix[row][col]);
            }
            break;

        case 'D':     // Удаление матрицы
        case 'd':
            // Освободить память от матрицы
            DeleteMatrix(rows, cols, matrix);
            printf("\nМатрица пуста!");
            break;

        case 'V':     // Заполнение матрицы заданным значением
        case 'v':
            // Проверить, что матрица не пуста, т.е. есть что изменять
            if (matrix == NULL) break;
            // Ввести значение и проверить корректность ввода
            if (!EntryValue("значение для заполнения", value, SHRT_MIN, SHRT_MAX)) break;
            // Перемещаться по строкам матрицы
            for (row = 0; row < rows; row++)
                // Перемещаться по столбцам матрицы и запоминать значение
                for (col = 0; col < cols; col++)
                    matrix[row][col] = value;
            // Перейти к отображению текущей матрицы
            ch = 'P';
            continue;


        case 'E':     // Ввод всех элементов матрицы по порядку
        case 'e':
            // Перемещаться по строкам матрицы
            for (row = 0; row < rows; row++)
                // Перемещаться по столбцам матрицы
                for (col = 0; col < cols; col++)
                {
                    // Вводить новые значения для элементов матрицы
                    printf("\nМатрица[%d][%d]", row, col);
                    if (!EntryValue("ячейки", matrix[row][col], SHRT_MIN, SHRT_MAX)) col--;
                }
            break;


        case 'M':     // Изменение элемента матрицы по индексу
        case 'm':
            // Проверить, что матрица не пуста, т.е. есть что изменять
            if (matrix == NULL) break;

            // Ввести индекс строки и проверить корректность ввода
            if (!EntryValue("индекс строки", row, 0, rows - 1)) break;

            // Ввести индекс столбца и проверить корректность ввода
            if (!EntryValue("индекс столбца", col, 0, cols - 1)) break;

            // Ввести значение элемента и проверить корректность ввода
            if (!EntryValue("значение элемента", value, SHRT_MIN, SHRT_MAX)) break;

            // Запомнить новое значение в элементе матрицы
            matrix[row][col] = value;
            break;


        //case 'I':     // Перестановка строк местами
        //case 'i':
        //    // Проверить, что матрица не пуста, т.е. есть что изменять
        //    if (matrix == NULL) break;

        //    // Ввести индекс первой строки для обмена и проверить корректность ввода
        //    if (!EntryValue("индекс первой строки", row, 0, rows - 1)) break;

        //    // Ввести индекс второй строки для обмена и проверить корректность ввода
        //    if (!EntryValue("индекс второй строки", idx, 0, rows - 1)) break;

        //    if (row != idx)
        //        // Переставить значения элементов между строками (проход по столбцу)
        //        for (col = 0; col < cols; col++)
        //        {
        //            value = matrix[row][col];
        //            matrix[row][col] = matrix[idx][col];
        //            matrix[idx][col] = value;
        //        }
        //    // Перейти к отображению текущей матрицы 
        //    ch = 'P';
        //    continue;


        //case 'J':     // Перестановка столбцов местами
        //case 'j':
        //    // Проверить, что матрица не пуста, т.е. есть что изменять
        //    if (matrix == NULL) break;

        //    // Ввести индекс первого столбца для обмена и проверить корректность ввода
        //    if (!EntryValue("индекс первого столбца", col, 0, cols - 1)) break;

        //    // Ввести индекс второго столбца для обмена и проверить корректность ввода
        //    if (!EntryValue("индекс второго столбца", idx, 0, cols - 1)) break;

        //    if (col != idx)
        //        // Переставить значения элементов между столбцами (проход по строке)
        //        for (row = 0; row < rows; row++)
        //        {
        //            value = matrix[row][col];
        //            matrix[row][col] = matrix[row][idx];
        //            matrix[row][idx] = value;
        //        }
        //    // Перейти к отображению текущей матрицы 
        //    ch = 'P';
        //    continue;

        case 'B':        // Сохранение матрицы в бинарном файле
        case 'b':
        case 'S':        // Сохранение матрицы в текстовом файле
        case 's':
            fflush(stdin);
            // Ввести имя файла
            printf("\nВведите имя файла для сохранения (или нажмите [enter] для отмены):>");
            // if(*gets_s(filename, namelen) == '\0') break;
            scanf("%65s", filename);

            // Создать файл для сохранения матрицы
            if ((fp = fopen(filename, "w")) == NULL)
                printf("\nОшибка: Файл с указанным именем не может создан или открыт на запись\n");
            else
            {
                if (ch == 'b' || ch == 'B')
                {
                    // Записать размеры матрицы в бинарный файл как единый блок
                    fwrite(pulley, sizeof(int), heap, fp);

                    // Записать элементы матрицы в бинарный файл по-блочно
                    if (matrix != NULL)
                    {
                        // Пройти по массиву указателей
                        for (row = 0; row < rows; row++)
                            // Записывать одномерные вектор-массивы значений в бинарный файл 
                            fwrite(matrix[row], sizeof(int), cols, fp);
                    }
                }
                else if (ch == 's' || ch == 'S')
                {
                    // Записать размеры матрицы в текстовый файл
                    fprintf(fp, "%d \t %d", rows, cols);
                    // Перемещаться по строкам матрицы
                    for (row = 0; row < rows; row++)
                    {
                        fprintf(fp, "\n");
                        // Перемещаться по столбцам матрицы
                        for (col = 0; col < cols; col++)
                            // Записывать элементы матрицы в текстовый файл поштучно
                            fprintf(fp, "%d\t", matrix[row][col]);
                    }
                }
                // Закрыть файл
                fclose(fp);
                printf("\nМатрица сохранена успешно\n");
            }
            break;


        case 'L':        // Загрузка матрицы из файла
        case 'l':
        case 'O':
        case 'o':
            fflush(stdin);
            // Ввести имя файла
            printf("\nВведите имя файл для загрузки (или нажмите [enter] для отмены):>");
            //if(*gets_s(filename, namelen) == '\0') break;
            scanf("%65s", filename);

            // Открыть файл для загрузки матрицы
            if ((fp = fopen(filename, "r")) == NULL)
                printf("\nОшибка: Файл с указанным именем не может быть открыт на чтение\n");
            else
            {
                // Удалить текущую матрицу
                DeleteMatrix(rows, cols, matrix);
                check = 0;

                if (ch == 'o' || ch == 'O')
                    // Прочитать размеры матрицы из бинарного файла как единый блок
                    check += fread(pulley, sizeof(int), heap, fp);
                else if (ch == 'l' || ch == 'L')
                    // Прочитать размеры матрицы из текстового файла по отдельности
                    check += fscanf(fp, "%d", &rows);
                check += fscanf(fp, "%d", &cols);

                // Проверить корректность чтения размеров матрицы
                if (check == heap)
                {
                    // Проверить допустимость диапазона для каждого размера
                    if (rows >= minsize && rows <= maxsize && cols >= minsize && cols <= maxsize)
                    {
                        // Зарезервировать память под новую матрицу
                        matrix = CreateMatrix(rows, cols);

                        // Убедиться, что память выделена
                        if (matrix != NULL)
                        {
                            if (ch == 'o' || ch == 'O')
                            {
                                // Пройти по массиву указателей
                                for (check = 0, row = 0; row < rows; row++, check += cols)
                                    // Прочитать одномерные вектор-массивы значений из бинарного 
                                    // файла как единые блоки, т.е. по cols-элементов за раз
                                    if (fread(matrix[row], sizeof(int), cols, fp) != cols) break;
                            }
                            else if (ch == 'l' || ch == 'L')
                            {
                                // Перемещаться по строкам матрицы
                                for (check = 0, row = 0; row < rows; row++)
                                    // Перемещаться по столбцам матрицы
                                    for (col = 0; col < cols; col++, check++)
                                        // Прочитать элементы матрицы из текстового файла поштучно
                                        if (fscanf(fp, "%d", &matrix[row][col]) != 1) break;
                            }
                            // Если было прочитано rows*cols-элементов, то загрузка прошла успешно
                            if (check == rows * cols)
                            {
                                printf("\nМатрица загружена успешно\n");
                                // Закрыть файл
                                fclose(fp);
                                // Перейти к отображению текущей матрицы
                                ch = 'P';
                                continue;
                            }
                            // Удалить матрицу, в случае неудачи
                            DeleteMatrix(rows, cols, matrix);
                        }
                    }
                }
                // Обнулить размеры, если недостаточно памяти или размеры прочитаны некорректно
                else rows = cols = 0;


                // Если прочитать матрицу не удалось
                printf("\nОшибка: Некорректные данные (загрузка отменена, матрица удалена)\n");
                // Закрыть файл
                fclose(fp);
            }
            break;

        case 'A':     // Настройка диапазона случайных чисел
        case 'a':
            // Ввести ширину диапазона случайных чисел и проверить корректность ввода
            EntryValue("диапазон случайных чисел", range, min_range, max_range);
            break;

        //case 'H':     // Сортировка элементов для выбранного столбца
        //case 'h':
        //    if (matrix == NULL) break;
        //    // Ввести индекс столбца и проверить корректность ввода
        //    if (!EntryValue("индекс столбца", col, 0, cols - 1)) break;

        //    for (int j = 1; j < rows; j++)
        //    {
        //        for (row = 0; row < rows - 1; row++)
        //        {
        //            if (matrix[row][col] > matrix[row + 1][col])
        //            {
        //                value = matrix[row][col];
        //                matrix[row][col] = matrix[row + 1][col];
        //                matrix[row + 1][col] = value;
        //            }
        //        }
        //    }
        //    // Перейти к отображению текущей матрицы 
        //    ch = 'P';

        //    break;

        //case 'F':     // Вычисление характеристики по элементам матрицы
        //case 'f':
        //    if (matrix == NULL) break;
        //    if (rows != cols) break;
        //    
        //    if (rows == cols)
        //    {   
        //        // Перемещаться по строкам матрицы
        //        for (row = 0; row < rows; row++)
        //        {
        //            // Перемещаться по столбцам матрицы
        //            for (col = 0; col < cols; col++)
        //            {
        //                // Вычисление характеристики
        //                if (row < col) oversum += matrix[row][col];
        //                if (row > col) undersum += matrix[row][col];
        //            }
        //        }
        //        control = oversum/undersum;
        //    }
        //    printf("\nХарактеристика=%.2f\n", control);
        //    break;


        case 'Z':     // Заполнение матрицы по заданию
        case 'z':
            // Проверить, что матрица не пуста, т.е. есть что изменять
            if (matrix == NULL) break;
            row = 0;
            col = 0;
            while (row < rows * cols) /*Цикл по номеру витка*/
            {
                k++;
                for (col = k - 1; col < cols - k + 1; col++)
                {
                    p++;
                    matrix[k - 1][col] = Sv(p);
                    row++;
                }   /*Определение значений верхнего гор столбца*/

                for (col = k; col < rows - k + 1; col++)
                {
                    p++;
                    matrix[col][cols - k] = Sv(p);
                    row++;
                }   /* --//-- По правому вертикальному столбцу*/

                for (col = cols - k - 1; col >= k - 1; col--)
                {
                    p++;
                    matrix[rows - k][col] = Sv(p);
                    row++;
                }   /* --//-- по нижнему горизонтальному столбцу*/

                for (col = rows - k - 1; col >= k; col--)
                {
                    p++;
                    matrix[col][k - 1] = Sv(p);
                    row++;
                }   /* --//-- по левому вертикальному столбцу*/

            }
            // Перейти к отображению текущего массива
            ch = 'P';
            continue;

        case '\0':    // Пустое действие
            break;

        default:
            printf("Ошибка: Некорректная операция");
        };
        // Сбросить устройство ввода
        while (getchar() != '\n' && getchar() != EOF);
        // Отображение консольного меню
        printf("\n\nГлавное меню:");
        printf("\nP. Печать матрицы");
        printf("\nC. Создание новой матрицы");
        printf("\nD. Удаление текущей матрицы");
        //printf("\nF. Вычисление характеристики");
        printf("\nB. Сохранение матрицы в бинарном файле");
        printf("\nO. Загрузка матрицы из бинарного файла");
        printf("\nS. Сохранение матрицы в текстовом файле");
        printf("\nL. Загрузка матрицы из текстового файла");
        printf("\nA. Настройка диапазона случайных чисел");
        //printf("\nI. Обмен элементами двух строк матрицы");
        //printf("\nJ. Обмен элементами двух столбцов матрицы");
        printf("\nM. Изменение элемента матрицы по индексам");
        printf("\nE. Ввод всех элементов матрицы по порядку");
        printf("\nV. Заполнение матрицы введенным значением");
        //printf("\nH. Сортировка элементов для выбранного столбца в порядке возрастания");
        printf("\nZ. Заполнение матрицы случайными значениями ");
        printf("\nR. Заполнение матрицы случайными значениями");
        printf("\nQ. Выход");
        printf("\nВыберите пункт:>");
        ch = getchar();
    } while ((ch != 'Q') && (ch != 'q'));

    // Освободить память из под текущей матрицы
    DeleteMatrix(rows, cols, matrix);
}
