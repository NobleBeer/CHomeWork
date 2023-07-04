#pragma once
// ����������� ������ ���� ������ "��������� ����������"

typedef unsigned __int8 STATUS;

// �������� ���� ��������� � ����� �����

STATUS Pack(int speed, int level, bool direct);

// ���������� ���������� ��������

int GetSpeed(STATUS state);

// ���������� ���������� ������

int GetLevel(STATUS state);

// ���������� ���������� �����������

bool GetDirect(STATUS state);

// ��������� ���������� ��������

STATUS ChangeSpeed(STATUS state, int speed);

// ��������� ���������� ������

STATUS ChangeLevel(STATUS state, int level);

// ��������� ���������� �����������

STATUS ChangeDirect(STATUS state, bool direct);

// ���������� ��������� ���������� �������

STATUS RandomStatus();

// ������ ���� ��������� ������ � ���������� �������

void PrintAllData(STATUS state);

// ������ ������������ ����� � ����������������� �������

void PrintHexStatus(STATUS state);

// ������ ������������ ����� � �������� �������

void PrintBinStatus(STATUS state);

// ������ ������������ ����� � ��������� ������� ���������

void PrintRadixStatus(STATUS state);