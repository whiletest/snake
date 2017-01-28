#include "stdafx.h"
#include "head.h"

void DrawString(int x,int y,const char *format,...)
{
	if (x < 0 || x >= 40) 
		return;
	if (y < 0 || y >= 30)
		return;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	csbiInfo.dwCursorPosition.X = 2 * x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csbiInfo.dwCursorPosition);
	va_list arg;
	va_start(arg, format);
	vprintf(format, arg);
	va_end(arg);
}