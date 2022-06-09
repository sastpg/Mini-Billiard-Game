#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <WinUser.h>
#include <Windows.h>

#include "CONST.h"
#include "DataStructure.h"
#include "Display.h"
#include "Rand.h"
#include "Load_Save.h"
#include "Physics.h"

Mode Gamemode;
FILEMODE Filemode;
bool isDisplayLine;

int Array[30];
BOOL isQuit = 0;
bBallNode* ballHead;
bBallNode* ballTail;
int gameTime = 0;
int turn = A;
int winner = 0;
int gameStatus = 0;
int Gameover = 0;

extern int Freemode;
extern double menuWidth;
extern double menuHeight;

int main()
{
	UpdateSettingFromFile();
	GameMain();

	return 0;
}

void GameMain()
{
	initgraph(menuWidth, menuHeight);
	load_img();
	while (1)
	{
		if (gameStatus == 0)
		{
			DrawMenu();
			UpdateWithoutInput_menu();
			UpdateWithInput_menu();
		}
		if (gameStatus == 1)
		{
			UpdateSettingFromFile();
			if (Gamemode == POOL || Gamemode == NINEBALL)
			{
				initgraph(1080, 580);
			}
			else if (Gamemode == SNOOKER)
			{
				initgraph(1480, 780);
				Freemode = 1;
			}
			DisplayBoard();
			InitLocation();
			if (Gamemode == 1)
			{
				MessageBox(NULL, _T("请在D型区域内放置白球"), _T("Manager"), MB_OK);
			}
			GameProcess();
		}
		else if (gameStatus == 2)
		{
			if (LoadFile(Filemode))
			{
				UpdateColor(Gamemode);
			}
			else {
				HWND wnd = GetHWnd();
				MessageBox(wnd, _T("无存档"), _T("错误"), MB_OK | MB_ICONWARNING);
				gameStatus = 0;
				continue;
			}
			GameProcess();
		}
		else if (gameStatus == 3)
		{
			DisplaySetting();
		}
		else if (gameStatus == 4)
		{
			break;
		}
	}
	EndBatchDraw();
	_getch();
	closegraph();
}

void GameProcess()
{
	BeginBatchDraw();
	while (1)
	{
		UpdateBalls();
		DisplayBoard();
		Boom();
		ScoreCal();
		MouseEventProcess();
		if (Gameover == 1)
		{
			break;
		}
		if (isQuit == 1)
		{
			break;
		}
	}
	if (!isQuit)
	{
		showwinner();
	}
	else {
		isQuit = 0;
		gameStatus = 0;
		EndBatchDraw();
		initgraph(menuWidth, menuHeight);
	}
}
