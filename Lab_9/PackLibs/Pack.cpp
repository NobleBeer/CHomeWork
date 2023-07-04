#include "..\PackBits\Global.h"

/* ������� �������� ���� ��������� ��������� � ����� �����

*/

STATUS Pack(int speed, int level, bool direct)

{

	return (((level < 1) ? 0 : ((level > 15) ? 14 : level - 1)) << 3) |

		((speed < 0) ? 0 : ((speed > 7) ? 7 : speed)) |

		((direct) ? 0x80 : 0);

}

/* ������� ���������� ���������� �������� �� ������������ �����

*/

int GetSpeed(STATUS state)

{

	return (state & 0x07);

}

/* ������� ���������� ���������� ������ �� ������������ �����

*/

int GetLevel(STATUS state)

{

	return ((state & 0x78) >> 3) + 1;

}

/* ������� ���������� ���������� ����������� �� ������������ �����

*/

bool GetDirect(STATUS state)

{

	return ((state & 0x80) ? true : false);

}