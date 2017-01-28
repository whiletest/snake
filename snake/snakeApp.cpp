// snake.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "head.h"
#include "view.h"


int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR szWndTitle[MAX_PATH];
	GetConsoleTitle(szWndTitle,MAX_PATH);
	HWND hwnd = FindWindow(TEXT("ConsoleWindowClass"),szWndTitle);
	SetWindowText(hwnd,TEXT("snake"));

	CMyView view(hwnd);
	view.InitialGui();

	view.Start();

	DWORD preTime = 0;
	DWORD curTime = 0;
	const DWORD timeDelta = 100;
	while (true)
	{
		curTime = timeGetTime();

		if (curTime - preTime > timeDelta)
		{
			if (_kbhit())
				view.HandleMessage();

			view.Display();

			preTime = curTime;
		}
	}

	return 0;
}

