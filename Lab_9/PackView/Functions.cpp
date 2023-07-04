#include "..\PackBits\Global.h"
#include <stdio.h>

#include <stdlib.h>


#pragma warning(disable: 4996)

/* ������� ������ ���� ��������� ������ � ���������� �������

*/

void PrintAllData(STATUS state)

{

	printf("\n �������� = %d \n ������� = %d \n ����������� = %d ",

		GetSpeed(state), GetLevel(state), GetDirect(state));

}

/* ������� ������ ������������ ����� � ����������������� �������

*/

void PrintHexStatus(STATUS state)

{

	printf("Hex=0x%X Oct=0%o Dec=%d", state, state, state);

}

/* ������� ���������� ��������� ���������� �������

*/

STATUS RandomStatus()

{

	return Pack(rand() % 8, rand() % 15, rand() % 2);

}

/* ������� ������ ������������ ����� � �������� �������

*/

void PrintBinStatus(STATUS state)

{

	// �������� ���������� ����� ��� �������� ����� � ���������� �������� �����

	int rotor, i;

	// � ����� ������� ��� ����� � ��������� "1" ������ �� ���� ���

	for (i = 1, rotor = 0x80; rotor != 0; rotor >>= 1, i++)

	{

		// ���������� ��� ����� � ����� ������������ �����

		putchar(((state & rotor) ? '1' : '0'));

		// �������� �������� ������ �� ������� ���

		if (i == 4)

		{

			i = 0;

			putchar(' ');

		}

	}

	// ������� ����������������� ������������� �����

	printf(" (0x%X)", state);

}

/* ������� ������ ������������ ����� � ��������� ������� ���������

*/

void PrintRadixStatus(STATUS state)

{

	char buffer[66]; // ���������� ����� ��� ���������� �������������

	int check, radix; // ������ ����� � ��������� ������� ���������

	// ������ ��������� ������� ���������

	printf("\n������� ��������� ������� ��������� [2..36]:>");

	check = scanf("%d", &radix);

	// ��������� ����������� ����� ��������� � ������������ ��������� ��������

	if (check != 1 || fgetchar() != 10 || radix < 2 || radix > 36)

	{

		fflush(stdin);

		printf("������: ������������ �������� ��������� ��\n");

		return;

	}

	// ������������� ����������� ����� � ������ �� ��������� ������� ���������

	itoa(state, buffer, radix);

	// ������� ��������� ��������������

	printf("\n���������(%d)������ = %s", radix, buffer);

}