#include <time.h>     // ���������� ������ � ��������
#include <stdio.h>    // ���������� �����-������
#include <stdlib.h>   // ���������� ��������� �������
#include <locale.h>   // ���������� �������� �����������

// ����������� ������ �������
const int minsize = 2;
// ������������ ������ �������
const int maxsize = 12;
// ����������� �������� ��������� �����
const int min_range = 8;
// ������������ �������� ��������� �����
const int max_range = 180;
// ����� ����� �����
const int namelen = 66;

int k = 0; // �����
int p = 0; // ������� ��� ���� ����� 
double oversum = 0.0;
double undersum = 0.0;
double control = 0.0;

/*
   ������� ����������� ������ ��� ������� � ���������� ��������� �� ��
*/
int** CreateMatrix(int rows, int cols)
{
    // ��������� ������� ������� �� ����������
    if (rows < minsize || rows > maxsize ||
        cols < minsize || cols > maxsize) return NULL;

    // ��������������� ������ ��� ���������� ������ ����������
    int** matrix = new int* [rows];

    // ���������, ��� ������ ��������
    if (matrix == NULL) return NULL;

    // ������������ �� ������� ����������
    for (register int row = 0; row < rows; row++)
    {
        // ��������������� ������ ��� ���������� ������-������ ��� ��������
        // �������� ������� � ������������ ��� � ����������� ������� ����������
        matrix[row] = new int[cols];

        // ���������, ��� ������ ��� ������-������ ��������  
        if (matrix[row] == NULL)
        {
            // ������� ����� ���������� ���������� �������
            while ((--row) >= 0)
                // ������� ���������� ������-�������
                delete[] matrix[row];
            // ������� ���������� ������ ����������
            delete[] matrix;
            // ������� ��������� � ������ �������� 
            return NULL;
        }
    }  // ������� ����� ������� ��� ������
    return matrix;
}

static long Sv(int n)
{
    for (i=1; i<=) 
    return n;
}


/*
   ������� ����������� ������ �� ��� ������� � �������� ����������� ����������
*/
void DeleteMatrix(int& rows, int& cols, int**& matrix)
{
    // ���������, ��� ������ ��������
    if (matrix != NULL)
    {
        // ������������ �� ������� ����������
        for (register int row = 0; row < rows; row++)
            // ������� ���������� ������-������� �����, �������������� � ����������
            delete[] matrix[row];
        // ������� ���������� ������ ����������
        delete[] matrix;
    }
    // �������� ���������� � �������
    matrix = NULL;
    rows = 0;
    cols = 0;
}

#pragma warning(disable: 4996)
/*
   ������� ���������� ���� �������� � �������� ���������
*/
bool EntryValue(char* name, int& value, int min = INT_MAX, int max = INT_MIN)
{
    // ����� ��� �����, ������ �������� �����
    int temp, check;
    // ������� ���������� � ���������
    if (name != NULL) printf("\n������� %s", name);

    // ���� �������� �� �����, �� ����� ��������
    if (min == INT_MAX && max == INT_MIN)
    {
        printf(":>");
        min = INT_MIN;
        max = INT_MAX;
    }
    // ���� ����� ������ ��������, �� �������� ����� ���� �� ������ ���������
    else if (min == INT_MAX && max != INT_MIN)
    {
        printf(" [< %d]:>", max);
        min = INT_MIN;
    }
    // ���� ����� ������ �������, �� �������� ����� ���� �� ������ ���������
    else if (min != INT_MAX && max == INT_MIN)
    {
        printf(" [> %d]:>", min);
        max = INT_MAX;
    }
    // ���� ����� �������� � �������, �� �������� ��������� � ���������
    else
        printf(" [%d..%d]:>", min, max);

    // ������ �������� �����
    check = scanf("%d", &temp);

    // ��������� ������������ ����� � ������������ ���������
    if (check != 1 || fgetchar() != 10 || temp < min || temp > max)
    {
        fflush(stdin);
        // ������� ��������� �� ������
        printf("������: ������������ ���� ��� %s\n", ((name) ? name : "��������"));
        return false;
    }
    else
    {
        // ������� ������� ����� ��������
        value = temp;
        return true;
    }
}
/*
   ����������� ������� ��������� ����� ���� �� ������
*/
static int number = 0;
static int NextNumber()
{
    return (number += 2);
}
/*
   ������� �������. ��������� ����, ��������, ��������� � �������������.
*/
void main()
{
    int   pulley[] = { 0, 0 };          // ����� ���������� ������� {�����, ��������}
    int& rows = pulley[0];            // ���������� ����� �������
    int& cols = pulley[1];            // ���������� �������� �������
    char  ch = '\0';                    // ������� ����
    int   row, col, idx;                // ������ ������, ������ �������, ������ ������
    int   check, value;                 // ������ �����, ��������� ��������
    int   range = max_range;            // ������ ��������� ��������� �����
    int** matrix = NULL;                // ��������� �� �������
    char  filename[namelen];            // ��� �����
    FILE* fp;                           // ��������� �� �������� �����

    // ��� ��������� �� ������� �����
    setlocale(LC_ALL, "Russian");
    printf("����: ��������� �������( ");

    // ���������� ��������� ��� ����� ���������� �������
    const int heap = sizeof(pulley) / sizeof(int);

    // ������������� ���������� ��������� �����
    srand((unsigned int)time(NULL));

    do {                                // ��������� ������ ����
        switch (ch)
        {
        case 'C':     // ���� ������� � �������������� �������
        case 'c':
            // ������ ���������� ����� ������� � ��������� ������������ �����
            if (!EntryValue("���������� �����", row, minsize, maxsize)) break;

            // ������ ���������� �������� ������� � ��������� ������������ �����
            if (!EntryValue("���������� ��������", col, minsize, maxsize)) break;

            // ������� ������� �������
            DeleteMatrix(rows, cols, matrix);

            // ��������������� ������ ��� ������� ��� ��������� �������
            if ((matrix = CreateMatrix(row, col)) == NULL)
            {
                printf("������: ������������ ������\n");
                break;
            }

            // ��������� ����� ������ �������
            rows = row;
            cols = col;
            // ������� � ���������� �������

        case 'R':     // ���������� ������� ���������� ����������
        case 'r':
            // ������������ �� ������� �������
            for (row = 0; row < rows; row++)
                // ������������ �� �������� �������
                for (col = 0; col < cols; col++)
                    // ������������ � ���������� ��������� ��������
                    matrix[row][col] = ((rand() % 2) ? +1 : -1) * (rand() % range);
            // ������� � ����������� ������� �������

        case 'P':     // ������ ��������� �������
        case 'p':
            printf("\n������� ������� [%dx%d] %s\n", rows, cols,
                ((matrix) ? "��������:" : "�����!"));

            // ������������ �� ������� �������
            for (row = 0; row < rows; row++)
            {
                printf("\n");
                // ������������ �� �������� �������
                for (col = 0; col < cols; col++)
                    // �������� �������� ������ �������
                    printf("%6d", matrix[row][col]);
            }
            break;

        case 'D':     // �������� �������
        case 'd':
            // ���������� ������ �� �������
            DeleteMatrix(rows, cols, matrix);
            printf("\n������� �����!");
            break;

        case 'V':     // ���������� ������� �������� ���������
        case 'v':
            // ���������, ��� ������� �� �����, �.�. ���� ��� ��������
            if (matrix == NULL) break;
            // ������ �������� � ��������� ������������ �����
            if (!EntryValue("�������� ��� ����������", value, SHRT_MIN, SHRT_MAX)) break;
            // ������������ �� ������� �������
            for (row = 0; row < rows; row++)
                // ������������ �� �������� ������� � ���������� ��������
                for (col = 0; col < cols; col++)
                    matrix[row][col] = value;
            // ������� � ����������� ������� �������
            ch = 'P';
            continue;


        case 'E':     // ���� ���� ��������� ������� �� �������
        case 'e':
            // ������������ �� ������� �������
            for (row = 0; row < rows; row++)
                // ������������ �� �������� �������
                for (col = 0; col < cols; col++)
                {
                    // ������� ����� �������� ��� ��������� �������
                    printf("\n�������[%d][%d]", row, col);
                    if (!EntryValue("������", matrix[row][col], SHRT_MIN, SHRT_MAX)) col--;
                }
            break;


        case 'M':     // ��������� �������� ������� �� �������
        case 'm':
            // ���������, ��� ������� �� �����, �.�. ���� ��� ��������
            if (matrix == NULL) break;

            // ������ ������ ������ � ��������� ������������ �����
            if (!EntryValue("������ ������", row, 0, rows - 1)) break;

            // ������ ������ ������� � ��������� ������������ �����
            if (!EntryValue("������ �������", col, 0, cols - 1)) break;

            // ������ �������� �������� � ��������� ������������ �����
            if (!EntryValue("�������� ��������", value, SHRT_MIN, SHRT_MAX)) break;

            // ��������� ����� �������� � �������� �������
            matrix[row][col] = value;
            break;


        //case 'I':     // ������������ ����� �������
        //case 'i':
        //    // ���������, ��� ������� �� �����, �.�. ���� ��� ��������
        //    if (matrix == NULL) break;

        //    // ������ ������ ������ ������ ��� ������ � ��������� ������������ �����
        //    if (!EntryValue("������ ������ ������", row, 0, rows - 1)) break;

        //    // ������ ������ ������ ������ ��� ������ � ��������� ������������ �����
        //    if (!EntryValue("������ ������ ������", idx, 0, rows - 1)) break;

        //    if (row != idx)
        //        // ����������� �������� ��������� ����� �������� (������ �� �������)
        //        for (col = 0; col < cols; col++)
        //        {
        //            value = matrix[row][col];
        //            matrix[row][col] = matrix[idx][col];
        //            matrix[idx][col] = value;
        //        }
        //    // ������� � ����������� ������� ������� 
        //    ch = 'P';
        //    continue;


        //case 'J':     // ������������ �������� �������
        //case 'j':
        //    // ���������, ��� ������� �� �����, �.�. ���� ��� ��������
        //    if (matrix == NULL) break;

        //    // ������ ������ ������� ������� ��� ������ � ��������� ������������ �����
        //    if (!EntryValue("������ ������� �������", col, 0, cols - 1)) break;

        //    // ������ ������ ������� ������� ��� ������ � ��������� ������������ �����
        //    if (!EntryValue("������ ������� �������", idx, 0, cols - 1)) break;

        //    if (col != idx)
        //        // ����������� �������� ��������� ����� ��������� (������ �� ������)
        //        for (row = 0; row < rows; row++)
        //        {
        //            value = matrix[row][col];
        //            matrix[row][col] = matrix[row][idx];
        //            matrix[row][idx] = value;
        //        }
        //    // ������� � ����������� ������� ������� 
        //    ch = 'P';
        //    continue;

        case 'B':        // ���������� ������� � �������� �����
        case 'b':
        case 'S':        // ���������� ������� � ��������� �����
        case 's':
            fflush(stdin);
            // ������ ��� �����
            printf("\n������� ��� ����� ��� ���������� (��� ������� [enter] ��� ������):>");
            // if(*gets_s(filename, namelen) == '\0') break;
            scanf("%65s", filename);

            // ������� ���� ��� ���������� �������
            if ((fp = fopen(filename, "w")) == NULL)
                printf("\n������: ���� � ��������� ������ �� ����� ������ ��� ������ �� ������\n");
            else
            {
                if (ch == 'b' || ch == 'B')
                {
                    // �������� ������� ������� � �������� ���� ��� ������ ����
                    fwrite(pulley, sizeof(int), heap, fp);

                    // �������� �������� ������� � �������� ���� ��-������
                    if (matrix != NULL)
                    {
                        // ������ �� ������� ����������
                        for (row = 0; row < rows; row++)
                            // ���������� ���������� ������-������� �������� � �������� ���� 
                            fwrite(matrix[row], sizeof(int), cols, fp);
                    }
                }
                else if (ch == 's' || ch == 'S')
                {
                    // �������� ������� ������� � ��������� ����
                    fprintf(fp, "%d \t %d", rows, cols);
                    // ������������ �� ������� �������
                    for (row = 0; row < rows; row++)
                    {
                        fprintf(fp, "\n");
                        // ������������ �� �������� �������
                        for (col = 0; col < cols; col++)
                            // ���������� �������� ������� � ��������� ���� ��������
                            fprintf(fp, "%d\t", matrix[row][col]);
                    }
                }
                // ������� ����
                fclose(fp);
                printf("\n������� ��������� �������\n");
            }
            break;


        case 'L':        // �������� ������� �� �����
        case 'l':
        case 'O':
        case 'o':
            fflush(stdin);
            // ������ ��� �����
            printf("\n������� ��� ���� ��� �������� (��� ������� [enter] ��� ������):>");
            //if(*gets_s(filename, namelen) == '\0') break;
            scanf("%65s", filename);

            // ������� ���� ��� �������� �������
            if ((fp = fopen(filename, "r")) == NULL)
                printf("\n������: ���� � ��������� ������ �� ����� ���� ������ �� ������\n");
            else
            {
                // ������� ������� �������
                DeleteMatrix(rows, cols, matrix);
                check = 0;

                if (ch == 'o' || ch == 'O')
                    // ��������� ������� ������� �� ��������� ����� ��� ������ ����
                    check += fread(pulley, sizeof(int), heap, fp);
                else if (ch == 'l' || ch == 'L')
                    // ��������� ������� ������� �� ���������� ����� �� �����������
                    check += fscanf(fp, "%d", &rows);
                check += fscanf(fp, "%d", &cols);

                // ��������� ������������ ������ �������� �������
                if (check == heap)
                {
                    // ��������� ������������ ��������� ��� ������� �������
                    if (rows >= minsize && rows <= maxsize && cols >= minsize && cols <= maxsize)
                    {
                        // ��������������� ������ ��� ����� �������
                        matrix = CreateMatrix(rows, cols);

                        // ���������, ��� ������ ��������
                        if (matrix != NULL)
                        {
                            if (ch == 'o' || ch == 'O')
                            {
                                // ������ �� ������� ����������
                                for (check = 0, row = 0; row < rows; row++, check += cols)
                                    // ��������� ���������� ������-������� �������� �� ��������� 
                                    // ����� ��� ������ �����, �.�. �� cols-��������� �� ���
                                    if (fread(matrix[row], sizeof(int), cols, fp) != cols) break;
                            }
                            else if (ch == 'l' || ch == 'L')
                            {
                                // ������������ �� ������� �������
                                for (check = 0, row = 0; row < rows; row++)
                                    // ������������ �� �������� �������
                                    for (col = 0; col < cols; col++, check++)
                                        // ��������� �������� ������� �� ���������� ����� ��������
                                        if (fscanf(fp, "%d", &matrix[row][col]) != 1) break;
                            }
                            // ���� ���� ��������� rows*cols-���������, �� �������� ������ �������
                            if (check == rows * cols)
                            {
                                printf("\n������� ��������� �������\n");
                                // ������� ����
                                fclose(fp);
                                // ������� � ����������� ������� �������
                                ch = 'P';
                                continue;
                            }
                            // ������� �������, � ������ �������
                            DeleteMatrix(rows, cols, matrix);
                        }
                    }
                }
                // �������� �������, ���� ������������ ������ ��� ������� ��������� �����������
                else rows = cols = 0;


                // ���� ��������� ������� �� �������
                printf("\n������: ������������ ������ (�������� ��������, ������� �������)\n");
                // ������� ����
                fclose(fp);
            }
            break;

        case 'A':     // ��������� ��������� ��������� �����
        case 'a':
            // ������ ������ ��������� ��������� ����� � ��������� ������������ �����
            EntryValue("�������� ��������� �����", range, min_range, max_range);
            break;

        //case 'H':     // ���������� ��������� ��� ���������� �������
        //case 'h':
        //    if (matrix == NULL) break;
        //    // ������ ������ ������� � ��������� ������������ �����
        //    if (!EntryValue("������ �������", col, 0, cols - 1)) break;

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
        //    // ������� � ����������� ������� ������� 
        //    ch = 'P';

        //    break;

        //case 'F':     // ���������� �������������� �� ��������� �������
        //case 'f':
        //    if (matrix == NULL) break;
        //    if (rows != cols) break;
        //    
        //    if (rows == cols)
        //    {   
        //        // ������������ �� ������� �������
        //        for (row = 0; row < rows; row++)
        //        {
        //            // ������������ �� �������� �������
        //            for (col = 0; col < cols; col++)
        //            {
        //                // ���������� ��������������
        //                if (row < col) oversum += matrix[row][col];
        //                if (row > col) undersum += matrix[row][col];
        //            }
        //        }
        //        control = oversum/undersum;
        //    }
        //    printf("\n��������������=%.2f\n", control);
        //    break;


        case 'Z':     // ���������� ������� �� �������
        case 'z':
            // ���������, ��� ������� �� �����, �.�. ���� ��� ��������
            if (matrix == NULL) break;
            row = 0;
            col = 0;
            while (row < rows * cols) /*���� �� ������ �����*/
            {
                k++;
                for (col = k - 1; col < cols - k + 1; col++)
                {
                    p++;
                    matrix[k - 1][col] = Sv(p);
                    row++;
                }   /*����������� �������� �������� ��� �������*/

                for (col = k; col < rows - k + 1; col++)
                {
                    p++;
                    matrix[col][cols - k] = Sv(p);
                    row++;
                }   /* --//-- �� ������� ������������� �������*/

                for (col = cols - k - 1; col >= k - 1; col--)
                {
                    p++;
                    matrix[rows - k][col] = Sv(p);
                    row++;
                }   /* --//-- �� ������� ��������������� �������*/

                for (col = rows - k - 1; col >= k; col--)
                {
                    p++;
                    matrix[col][k - 1] = Sv(p);
                    row++;
                }   /* --//-- �� ������ ������������� �������*/

            }
            // ������� � ����������� �������� �������
            ch = 'P';
            continue;

        case '\0':    // ������ ��������
            break;

        default:
            printf("������: ������������ ��������");
        };
        // �������� ���������� �����
        while (getchar() != '\n' && getchar() != EOF);
        // ����������� ����������� ����
        printf("\n\n������� ����:");
        printf("\nP. ������ �������");
        printf("\nC. �������� ����� �������");
        printf("\nD. �������� ������� �������");
        //printf("\nF. ���������� ��������������");
        printf("\nB. ���������� ������� � �������� �����");
        printf("\nO. �������� ������� �� ��������� �����");
        printf("\nS. ���������� ������� � ��������� �����");
        printf("\nL. �������� ������� �� ���������� �����");
        printf("\nA. ��������� ��������� ��������� �����");
        //printf("\nI. ����� ���������� ���� ����� �������");
        //printf("\nJ. ����� ���������� ���� �������� �������");
        printf("\nM. ��������� �������� ������� �� ��������");
        printf("\nE. ���� ���� ��������� ������� �� �������");
        printf("\nV. ���������� ������� ��������� ���������");
        //printf("\nH. ���������� ��������� ��� ���������� ������� � ������� �����������");
        printf("\nZ. ���������� ������� ���������� ���������� ");
        printf("\nR. ���������� ������� ���������� ����������");
        printf("\nQ. �����");
        printf("\n�������� �����:>");
        ch = getchar();
    } while ((ch != 'Q') && (ch != 'q'));

    // ���������� ������ �� ��� ������� �������
    DeleteMatrix(rows, cols, matrix);
}
