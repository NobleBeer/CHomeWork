#include "..\PackBits\Global.h"

/* ������� ��������� ���������� �������� � ����������� �����

*/

STATUS ChangeSpeed(STATUS state, int speed)

{

	return (state & 0xF8) | ((speed < 0) ? 0 : ((speed > 7) ? 7 : speed));

}

/* ������� ��������� ���������� ������ � ����������� �����

*/

STATUS ChangeLevel(STATUS state, int level)

{

	return (state & 0x87) | (((level < 1) ? 0 : ((level > 15) ? 14 : level - 1)) << 3);

}

/* ������� ��������� ���������� ����������� � ����������� �����

*/

STATUS ChangeDirect(STATUS state, bool direct)

{

	return (state & 0x7F) | ((direct) ? 0x80 : 0);

}