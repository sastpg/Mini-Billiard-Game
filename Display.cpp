#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <atlconv.h>

#include "CONST.h"
#include"DataStructure.h"
#include "Rand.h"
#include "Display.h"
#include "Physics.h"
#include "Load_Save.h"

//Definition
extern Mode Gamemode;
extern FILEMODE Filemode;
extern bool isDisplayLine;
extern int gameStatus;

location kitchenLoaction;
location spotsLocation;
extern bBallNode* ballHead;
extern int Array[30];
extern bBallNode* ballTail;
extern BOOL isQuit;
int boardWidth[3] = { 1000,1405 ,1000 };
int boardHeight[3] = { 500,700 ,500 };
int startX;
int startY;
int score[2] = { 0,0 };
int isDisplayBox = 0;
int finalhit;
double menu_angle1 = 0;
int menu_roll;
int whiteball_roll = 0;
int pickstart = 0;
int pickcontinue = 0;
int pickhelp = 0;
int pickqiut = 0;
int soundswitch = 0;



extern int isClickedMouse;
extern double sinAngle;
extern double cosAngle;
extern double rodstart_x;
extern double rodstart_y;
extern double rodend_x;
extern double rodend_y;
extern double extension_line_bx;
extern double extension_line_by;
extern double extension_line_ex;
extern double extension_line_ey;
extern int gameTime;
extern int turn;
extern int Freemode;
extern int gameStatus;
extern int firstHitID;
extern int finalHitID;
extern int objectBallID;
extern MOUSEMSG m;

IMAGE img_start;
IMAGE img_board;
IMAGE img_setting;
IMAGE img_whiteball;
IMAGE img_whiteball2;
IMAGE img_whiteballblock;
IMAGE img_button;
IMAGE img_startbutton;
IMAGE img_continuebutton;
IMAGE img_helpbutton;
IMAGE img_qiutbutton;
IMAGE img_gamemode;
IMAGE img_gamemodebackarrow1;
IMAGE img_gamemodebackarrow2;
IMAGE img_nineball1;
IMAGE img_pool1;
IMAGE img_snooker1;
IMAGE img_nineball2;
IMAGE img_pool2;
IMAGE img_snooker2;
IMAGE img_determine1;
IMAGE img_determine2;
IMAGE img_little_loading_bk;
IMAGE img_little_loading;
IMAGE img_little_loading2;
IMAGE img_loading_bar;
IMAGE img_loading;

double menuWidth = 1023;
double menuHeight = 682;

void DisplayBoard()
{
	int width = boardWidth[Gamemode];
	int height = boardHeight[Gamemode];

	startX = 38;
	startY = 40;
	cleardevice();
	setbkmode(TRANSPARENT);
	if (Gamemode != SNOOKER)
	{
		loadimage(&img_board, _T("Source/board1.jpg"));
		putimage(0, 0, &img_board);
	}
	else {
		loadimage(&img_board, _T("Source/board2.jpg"));
		putimage(0, 0, &img_board);
	}
	setlinecolor(BLACK);

	//Draw Board and Holes
	setlinestyle(PS_SOLID, 3);
	arc(startX - RADIUS_HOLE, startY - RADIUS_HOLE, startX + RADIUS_HOLE, startY + RADIUS_HOLE, 0, 1.5 * PI);
	line(startX + RADIUS_HOLE, startY, startX + width / 2 - RADIUS_HOLE, startY);
	arc(startX + width / 2 - RADIUS_HOLE, startY - RADIUS_HOLE, startX + width / 2 + RADIUS_HOLE, startY + RADIUS_HOLE, 0, PI);
	line(startX + width / 2 + RADIUS_HOLE, startY, startX + width - RADIUS_HOLE, startY);
	arc(startX + width - RADIUS_HOLE, startY - RADIUS_HOLE, startX + width + RADIUS_HOLE, startY + RADIUS_HOLE, -0.5 * PI, PI);
	line(startX + width, startY + RADIUS_HOLE, startX + width, startY + height - RADIUS_HOLE);
	arc(startX + width - RADIUS_HOLE, startY + height - RADIUS_HOLE, startX + width + RADIUS_HOLE, startY + height + RADIUS_HOLE, -PI, 0.5 * PI);
	line(startX + 0.5 * width + RADIUS_HOLE, startY + height, startX + width - RADIUS_HOLE, startY + height);
	arc(startX + 0.5 * width - RADIUS_HOLE, startY + height - RADIUS_HOLE, startX + 0.5 * width + RADIUS_HOLE, startY + height + RADIUS_HOLE, -PI, 0);
	line(startX + RADIUS_HOLE, startY + height, startX + 0.5 * width - RADIUS_HOLE, startY + height);
	arc(startX - RADIUS_HOLE, startY + height - RADIUS_HOLE, startX + RADIUS_HOLE, startY + height + RADIUS_HOLE, 0.5 * PI, 0);
	line(startX, startY + RADIUS_HOLE, startX, startY + height - RADIUS_HOLE);

	//Draw Kitchen Line & Kitchen Spot
	setlinestyle(PS_SOLID, 2);
	setlinecolor(WHITE);
	line(startX + 0.8 * width, startY + 2, startX + 0.8 * width, startY + height - 2);
	arc(startX + 0.8 * width - 1.0 / 6 * height, startY + 0.5 * height - 1.0 / 6 * height, startX + 0.8 * width + 1.0 / 6 * height, startY + 0.5 * height + 1.0 / 6 * height, -0.5 * PI, 0.5 * PI);
	setfillcolor(WHITE);
	solidcircle(startX + 0.8 * width, startY + 0.5 * height, 3);
	kitchenLoaction.X = startX + 0.8 * width;
	kitchenLoaction.Y = startY + 0.5 * height;

	//Draw Spots
	if (Gamemode == POOL || Gamemode == NINEBALL)
	{
		solidcircle(startX + 0.25 * width, startY + 0.5 * height, 3);
		spotsLocation.X = startX + 0.25 * width;
		spotsLocation.Y = startY + 0.5 * height;
	}
	else if (Gamemode == SNOOKER)
	{
		solidcircle(startX + 0.25 * width, startY + 0.5 * height, 3);
		spotsLocation.X = startX + 0.25 * width - 2 * RADIUS_BALL - DELTA;
		spotsLocation.Y = startY + 0.5 * height;
	}

	//Draw Text
	TCHAR s[1000];
	const TCHAR* modeStr[3] = { _T("Pool"),_T("Snooker"),_T("Nine balls") };
	const TCHAR* turnStr[2] = { _T("A"),_T("B") };

	if (Gamemode == POOL)
	{
		_stprintf(s, _T("GameMode: %s    Round: %d    Player: %s                            Score A: %d     Score B: %d"), modeStr[Gamemode], gameTime / 2 + 1, turnStr[turn], score[A], score[B]);
	}
	else if (Gamemode == SNOOKER)
	{
		_stprintf(s, _T("GameMode: %s    Round: %d   Player: %s  Score A: %d  Score B: %d             ObjectBallID: %d"), modeStr[Gamemode], gameTime / 2 + 1, turnStr[turn], score[A], score[B], objectBallID);
		//_stprintf(s, _T(" FinalHit: %d"), finalHitID);
	}
	else if (Gamemode == NINEBALL)
	{
		_stprintf(s, _T("GameMode: %s    Round: %d    Player: %s                            Error A: %d     Error B: %d"), modeStr[Gamemode], gameTime / 2 + 1, turnStr[turn], score[A], score[B]);
	}
	settextcolor(Black);
	settextstyle(25, 0, _T("Times New Roman"), 0, 0, 1000, 0, 0, 0);
	outtextxy(startX + 30, startY - 35, s);
	if (Freemode && isDisplayBox && Gamemode != SNOOKER)
	{
		const TCHAR* str[2] = { _T("系统：玩家A放置白球"),_T("系统：玩家B放置白球") };
		isDisplayBox = 0;
		MessageBox(NULL, str[turn], _T("Manager"), MB_OK);
	}

	//Button
	setfillcolor(BLUE);
	settextstyle(20, 0, _T("黑体"), 0, 0, 1000, 0, 0, 0);
	settextcolor(YELLOW);
	fillrectangle(startX + 50, startY + height + 5, startX + 145, startY + height + 35);
	outtextxy(startX + 50 + 5, startY + height + 5 + 5, L"返回菜单");
	if (m.x >= startX + 50 && m.x <= startX + 145 && m.y >= startY + height + 5 && m.y <= startY + height + 35)
	{
		setlinecolor(BLACK);
		rectangle(startX + 50 - 2, startY + height + 5 - 2, startX + 145 + 2, startY + height + 35 + 2);
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			int answer = MessageBox(NULL, _T("是否保存？"), _T("Manager"), MB_YESNO | MB_ICONQUESTION);

			if (answer == IDYES)
			{
				SaveFile(Filemode);
			}
			isQuit = 1;
		}
	}
	else
	{
		setlinecolor(WHITE);
		rectangle(startX + 50 - 2, startY + height + 5 - 2, startX + 145 + 2, startY + height + 35 + 2);
	}
}
void PowerControl()
{
	setlinestyle(PS_SOLID, 6);
	setcolor(YELLOW);
	settextcolor(BLACK);
	const TCHAR* str = _T("Power: ");
	if (Gamemode == POOL || Gamemode == NINEBALL)
	{
		outtextxy(775, 555, str);
		line(850, 560, 1000, 560);
	}
	else if (Gamemode == SNOOKER)
	{
		line(1250, 765, 1400, 765);
	}

	char input;
	double v;
	bBallNode* temp = ballHead;
	struct point
	{
		int toppoint_x, toppoint_y;
		int leftpoint_x, leftpoint_y;
		int rightpoint_x, rightpoint_y;
		int pointmovespeed;
	}p;

	if (Gamemode == POOL || Gamemode == NINEBALL)
	{
		p.toppoint_x = 850;         //三角形的顶部坐标
		p.toppoint_y = 10 + 565;
		p.rightpoint_x = 850 + 10;     //三角的右底角坐标
		p.rightpoint_y = 565;
		p.leftpoint_x = 850 - 10;      //三角的左底角坐标
		p.leftpoint_y = 565;
		p.pointmovespeed = 10;        //三角的移动速度
	}
	else {
		p.toppoint_x = 1250;         //三角形的顶部坐标
		p.toppoint_y = 10 + 770;
		p.rightpoint_x = 1250 + 10;     //三角的右底角坐标
		p.rightpoint_y = 770;
		p.leftpoint_x = 1250 - 10;      //三角的左底角坐标
		p.leftpoint_y = 770;
		p.pointmovespeed = 10;        //三角的移动速度
	}
	if (isClickedMouse == 0)
	{
		finalhit = 0;
	}
	POINT pts[3] = { {p.toppoint_x, p.toppoint_y}, {p.leftpoint_x, p.leftpoint_y}, {p.rightpoint_x, p.rightpoint_y} };
	setpolyfillmode(WINDING);
	setfillcolor(RED);
	solidpolygon(pts, 3);
	while (isClickedMouse == 1 && finalhit == 0)
	{
		for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
		{
			int x = temp->bBall.ballLocation.X;
			int y = temp->bBall.ballLocation.Y;
			int id = temp->bBall.ID;
			TCHAR s[5];
			POINT pts1[] = { {x, y}, {x + sin(PI / 3) * RADIUS_BALL, y - 0.5 * RADIUS_BALL}, {x - sin(PI / 3) * RADIUS_BALL, y - 0.5 * RADIUS_BALL} };
			POINT pts2[] = { {x, y}, {x + sin(PI / 3) * RADIUS_BALL, y + 0.5 * RADIUS_BALL}, {x - sin(PI / 3) * RADIUS_BALL, y + 0.5 * RADIUS_BALL} };
			_stprintf(s, _T("%d"), id);

			int height = textheight(s);
			int width = textwidth(s);

			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(13, 0, _T("黑体"), 0, 0, 1000, 0, 0, 0);
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 4);
			circle(x, y, RADIUS_BALL);

			switch (temp->bBall.color)
			{
			case 0:
				setfillcolor(WHITE);
				solidcircle(x, y, RADIUS_BALL);
				break;
			case 1:
				setfillcolor(RGB(255, 240, 0));
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 2:
				setfillcolor(BLUE);
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 3:
				setfillcolor(RGB(96, 56, 17));
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 4:
				setfillcolor(RGB(255, 192, 203));
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 5:
				setfillcolor(RED);
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 6:
				setfillcolor(MAGENTA);
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 7:
				setfillcolor(RGB(255, 128, 0));
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 8:
				setfillcolor(GREEN);
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 9:
				setfillcolor(RGB(176, 119, 72));
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 10:
				setfillcolor(BLACK);
				solidcircle(x, y, RADIUS_BALL);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);;
				break;
			case 11:
				setfillcolor(WHITE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
				setfillcolor(RGB(255, 240, 0));
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
				solidpolygon(pts1, 3);
				solidpolygon(pts2, 3);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 12:
				setfillcolor(WHITE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
				setfillcolor(BLUE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
				solidpolygon(pts1, 3);
				solidpolygon(pts2, 3);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 13:
				setfillcolor(WHITE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
				setfillcolor(RED);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
				solidpolygon(pts1, 3);
				solidpolygon(pts2, 3);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 14:
				setfillcolor(WHITE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
				setfillcolor(MAGENTA);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
				solidpolygon(pts1, 3);
				solidpolygon(pts2, 3);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 15:
				setfillcolor(WHITE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
				setfillcolor(RGB(255, 128, 0));
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
				solidpolygon(pts1, 3);
				solidpolygon(pts2, 3);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 16:
				setfillcolor(WHITE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
				setfillcolor(GREEN);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
				solidpolygon(pts1, 3);
				solidpolygon(pts2, 3);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			case 17:
				setfillcolor(WHITE);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
				setfillcolor(RGB(176, 119, 72));
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
				solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
				solidpolygon(pts1, 3);
				solidpolygon(pts2, 3);
				setfillcolor(WHITE);
				solidcircle(x, y, 0.4 * RADIUS_BALL);
				outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
				break;
			}
		}
		if (isClickedMouse == 0)
		{
			setlinestyle(PS_SOLID, 6);
			setcolor(YELLOW);
			line(rodstart_x, rodstart_y, rodend_x, rodend_y);
		}

		setpolyfillmode(WINDING);
		setfillcolor(GREEN);
		solidpolygon(pts, 3);
		p.toppoint_x += p.pointmovespeed;
		p.leftpoint_x += p.pointmovespeed;
		p.rightpoint_x += p.pointmovespeed;
		pts[0].x = p.toppoint_x;
		pts[0].y = p.toppoint_y;
		pts[1].x = p.leftpoint_x;
		pts[1].y = p.leftpoint_y;
		pts[2].x = p.rightpoint_x;
		pts[2].y = p.rightpoint_y;
		if (Gamemode == POOL || Gamemode == NINEBALL)
		{
			if (p.toppoint_x >= 1000 || p.toppoint_x <= 850)   //走到力度条尽头就反向
			{
				p.pointmovespeed = p.pointmovespeed * (-1);
			}
		}
		else {
			if (p.toppoint_x >= 1400 || p.toppoint_x <= 1250)   //走到力度条尽头就反向
			{
				p.pointmovespeed = p.pointmovespeed * (-1);
			}
		}
		setpolyfillmode(WINDING);
		setfillcolor(RED);
		solidpolygon(pts, 3);
		if (_kbhit())
		{
			input = _getch();
			if (input == ' ')
			{
				finalhit = 1;
				if (Gamemode == POOL || Gamemode == NINEBALL)
				{
					v = (p.toppoint_x - 850) / 15;
				}
				else {
					v = (p.toppoint_x - 1250) / 12.5;
				}
				temp->bBall.ballVelocity.velocity_X = (-1) * cosAngle * v;
				temp->bBall.ballVelocity.velocity_Y = (-1) * sinAngle * v;
				break;
			}
		}
		refresh();
		FlushBatchDraw();
		Sleep(100);
	}
}
void UpdateBalls()
{
	PowerControl();
	for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
	{
		int x = temp->bBall.ballLocation.X;
		int y = temp->bBall.ballLocation.Y;
		int id = temp->bBall.ID;
		TCHAR s[5];
		POINT pts1[] = { {x, y}, {x + sin(PI / 3) * RADIUS_BALL, y - 0.5 * RADIUS_BALL}, {x - sin(PI / 3) * RADIUS_BALL, y - 0.5 * RADIUS_BALL} };
		POINT pts2[] = { {x, y}, {x + sin(PI / 3) * RADIUS_BALL, y + 0.5 * RADIUS_BALL}, {x - sin(PI / 3) * RADIUS_BALL, y + 0.5 * RADIUS_BALL} };

		_stprintf(s, _T("%d"), id);
		int height = textheight(s);
		int width = textwidth(s);

		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(13, 0, _T("黑体"), 0, 0, 1000, 0, 0, 0);
		setlinestyle(PS_SOLID, 4);
		setlinecolor(BLACK);
		circle(x, y, RADIUS_BALL);

		switch (temp->bBall.color)
		{
		case 0:
			setfillcolor(WHITE);
			solidcircle(x, y, RADIUS_BALL);
			break;
		case 1:
			setfillcolor(RGB(255, 240, 0));
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 2:
			setfillcolor(BLUE);
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 3:
			setfillcolor(RGB(96, 56, 17));
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 4:
			setfillcolor(RGB(255, 192, 203));
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 5:
			setfillcolor(RED);
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 6:
			setfillcolor(MAGENTA);
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 7:
			setfillcolor(RGB(255, 128, 0));
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 8:
			setfillcolor(GREEN);
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 9:
			setfillcolor(RGB(176, 119, 72));
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 10:
			setfillcolor(BLACK);
			solidcircle(x, y, RADIUS_BALL);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);;
			break;
		case 11:
			setfillcolor(WHITE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
			setfillcolor(RGB(255, 240, 0));
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
			solidpolygon(pts1, 3);
			solidpolygon(pts2, 3);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 12:
			setfillcolor(WHITE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
			setfillcolor(BLUE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
			solidpolygon(pts1, 3);
			solidpolygon(pts2, 3);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 13:
			setfillcolor(WHITE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
			setfillcolor(RED);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
			solidpolygon(pts1, 3);
			solidpolygon(pts2, 3);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 14:
			setfillcolor(WHITE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
			setfillcolor(MAGENTA);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
			solidpolygon(pts1, 3);
			solidpolygon(pts2, 3);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 15:
			setfillcolor(WHITE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
			setfillcolor(RGB(255, 128, 0));
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
			solidpolygon(pts1, 3);
			solidpolygon(pts2, 3);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 16:
			setfillcolor(WHITE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
			setfillcolor(GREEN);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
			solidpolygon(pts1, 3);
			solidpolygon(pts2, 3);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		case 17:
			setfillcolor(WHITE);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, PI / 6, 5 * PI / 6);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -5 * PI / 6, -PI / 6);
			setfillcolor(RGB(176, 119, 72));
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, -PI / 5.87, PI / 5.87);
			solidpie(x - RADIUS_BALL, y - RADIUS_BALL, x + RADIUS_BALL, y + RADIUS_BALL, 5 * PI / 6, 7 * PI / 6);
			solidpolygon(pts1, 3);
			solidpolygon(pts2, 3);
			setfillcolor(WHITE);
			solidcircle(x, y, 0.4 * RADIUS_BALL);
			outtextxy(x - 0.5 * width, y - 0.5 * height + 1, s);
			break;
		}
	}

	//Draw Rod
	if (Gamemode != SNOOKER)
	{
		if (isClickedMouse == 0 && Freemode == 0)
		{
			setlinestyle(PS_SOLID, 6);
			setcolor(YELLOW);
			line(rodstart_x, rodstart_y, rodend_x, rodend_y);
			if (isDisplayLine)
			{
				setlinestyle(PS_DASH, 2);
				setcolor(WHITE);
				line(extension_line_bx, extension_line_by, extension_line_ex, extension_line_ey);
			}
		}
	}
	else {
		if (isClickedMouse == 0)
		{
			setlinestyle(PS_SOLID, 6);
			setcolor(YELLOW);
			line(rodstart_x, rodstart_y, rodend_x, rodend_y);
			if (isDisplayLine)
			{
				setlinestyle(PS_DASH, 2);
				setcolor(WHITE);
				line(extension_line_bx, extension_line_by, extension_line_ex, extension_line_ey);
			}
		}
	}

	refresh();
	FlushBatchDraw();
}
void refresh()
{
	setfillcolor(GREEN);
	fillcircle(0, 0, RADIUS_BALL + 2);
	setlinecolor(GREEN);
	circle(0, 0, RADIUS_BALL + 2);
}

void InitLocation()
{
	switch (Gamemode)
	{
	case POOL:
		RandomArray(14);
		PoolInit();
		break;
	case SNOOKER:
		SnookerInit();
		break;
	case NINEBALL:
		RandomArray(7);
		NineballInit();
		break;
	}
}
void PoolInit()
{
	turn = A;
	gameTime = 0;
	Freemode = 0;
	score[0] = score[1] = 0;
	for (int i = 0; i < 16; i++)
	{
		bBallNode* temp = (bBallNode*)malloc(sizeof(bBallNode));

		temp->bBall.ID = i;
		temp->bBall.ballVelocity.velocity_X = 0;
		temp->bBall.ballVelocity.velocity_Y = 0;
		if (i == 0)
		{
			ballHead = temp;
		}
		else {
			ballTail->next = temp;
		}
		ballTail = temp;
	}
	ballTail->next = NULL;

	//Location and Color
	location BALL_LOCATION[14] = {
		spotsLocation,
		{spotsLocation.X - 2 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - RADIUS_BALL},
		{spotsLocation.X - 2 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + RADIUS_BALL},
		{spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 2 * RADIUS_BALL },
		{spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 2 * RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 3 * RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 3 * RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 4 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 4 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 2 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 2 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y }
	};

	for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
	{
		switch (temp->bBall.ID)
		{
		case 0:
			temp->bBall.color = White;
			temp->bBall.ballLocation = kitchenLoaction;
			break;
		case 1:
			temp->bBall.color = Yellow;
			temp->bBall.ballLocation = BALL_LOCATION[Array[0]];
			break;
		case 2:
			temp->bBall.color = Blue;
			temp->bBall.ballLocation = BALL_LOCATION[Array[1]];
			break;
		case 3:
			temp->bBall.color = Red;
			temp->bBall.ballLocation = BALL_LOCATION[Array[2]];
			break;
		case 4:
			temp->bBall.color = Purple;
			temp->bBall.ballLocation = BALL_LOCATION[Array[3]];
			break;
		case 5:
			temp->bBall.color = Orange;
			temp->bBall.ballLocation = BALL_LOCATION[Array[4]];
			break;
		case 6:
			temp->bBall.color = Green;
			temp->bBall.ballLocation = BALL_LOCATION[Array[5]];
			break;
		case 7:
			temp->bBall.color = Caramel;
			temp->bBall.ballLocation = BALL_LOCATION[Array[6]];
			break;
		case 8:
			temp->bBall.color = Black;
			temp->bBall.ballLocation = { spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y };
			break;
		case 9:
			temp->bBall.color = Yellow_White;
			temp->bBall.ballLocation = BALL_LOCATION[Array[7]];
			break;
		case 10:
			temp->bBall.color = Blue_White;
			temp->bBall.ballLocation = BALL_LOCATION[Array[8]];
			break;
		case 11:
			temp->bBall.color = Red_White;
			temp->bBall.ballLocation = BALL_LOCATION[Array[9]];
			break;
		case 12:
			temp->bBall.color = Purple_White;
			temp->bBall.ballLocation = BALL_LOCATION[Array[10]];
			break;
		case 13:
			temp->bBall.color = Orange_White;
			temp->bBall.ballLocation = BALL_LOCATION[Array[11]];
			break;
		case 14:
			temp->bBall.color = Green_White;
			temp->bBall.ballLocation = BALL_LOCATION[Array[12]];
			break;
		case 15:
			temp->bBall.color = Caramel_White;
			temp->bBall.ballLocation = BALL_LOCATION[Array[13]];
			break;
		}
	}
}
void SnookerInit()
{
	turn = A;
	gameTime = 0;
	score[0] = score[1] = 0;
	int width = boardWidth[Gamemode];
	int height = boardHeight[Gamemode];

	for (int i = 0; i < 22; i++)
	{
		bBallNode* temp = (bBallNode*)malloc(sizeof(bBallNode));

		temp->bBall.ID = i;
		temp->bBall.ballVelocity.velocity_X = 0;
		temp->bBall.ballVelocity.velocity_Y = 0;
		if (i == 0)
		{
			ballHead = temp;
		}
		else {
			ballTail->next = temp;
		}
		ballTail = temp;
	}
	ballTail->next = NULL;

	//Location and Color
	location BALL_LOCATION[14] = {
		spotsLocation,
		{spotsLocation.X - 2 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - RADIUS_BALL},
		{spotsLocation.X - 2 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + RADIUS_BALL},
		{spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 2 * RADIUS_BALL },
		{spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 2 * RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 3 * RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 3 * RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 4 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 4 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 2 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 2 * RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y }
	};

	for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
	{
		switch (temp->bBall.ID)
		{
		case 0: //WHITE
			temp->bBall.color = White;
			//temp->bBall.ballLocation = { 0,0 };
			temp->bBall.ballLocation = { 1000.0,760.0 };
			//temp->bBall.ballLocation = { kitchenLoaction.X + 2 * RADIUS_BALL + DELTA,kitchenLoaction.Y };
			break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
			temp->bBall.color = Red;
			temp->bBall.ballLocation = BALL_LOCATION[temp->bBall.ID - 1];
			break;
		case 15:
			temp->bBall.color = Red;
			temp->bBall.ballLocation = { spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y };
			break;
		case 16:  //YELLOW
			temp->bBall.color = Yellow;
			temp->bBall.ballLocation = { kitchenLoaction.X,kitchenLoaction.Y - 1.0 / 6 * height };
			break;
		case 17:  //GREEN
			temp->bBall.color = Green;
			temp->bBall.ballLocation = { kitchenLoaction.X,kitchenLoaction.Y + 1.0 / 6 * height };
			break;
		case 18:  //BROWN
			temp->bBall.color = Brown;
			temp->bBall.ballLocation = kitchenLoaction;
			break;
		case 19:  //BLUE
			temp->bBall.color = Blue;
			temp->bBall.ballLocation = { startX + 0.5 * width,spotsLocation.Y };
			break;
		case 20:  //PINK
			temp->bBall.color = Pink;
			temp->bBall.ballLocation = { startX + 0.25 * width,spotsLocation.Y };
			break;
		case 21:  //BLACK
			temp->bBall.color = Black;
			temp->bBall.ballLocation = { startX + width * BLACK_RATIO,spotsLocation.Y };
			break;
		}
	}
}
void NineballInit()
{
	turn = A;
	gameTime = 0;
	Freemode = 0;
	score[0] = score[1] = 0;
	for (int i = 0; i < 10; i++)
	{
		bBallNode* temp = (bBallNode*)malloc(sizeof(bBallNode));

		temp->bBall.ID = i;
		temp->bBall.ballVelocity.velocity_X = 0;
		temp->bBall.ballVelocity.velocity_Y = 0;
		if (i == 0)
		{
			ballHead = temp;
		}
		else {
			ballTail->next = temp;
		}
		ballTail = temp;
	}
	ballTail->next = NULL;

	location BALL_LOCATION[7] = {
		{spotsLocation.X - 2 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - RADIUS_BALL},
		{spotsLocation.X - 2 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + RADIUS_BALL},
		{spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - 2 * RADIUS_BALL },
		{spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + 2 * RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y - RADIUS_BALL },
		{spotsLocation.X - 6 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y + RADIUS_BALL },
		{spotsLocation.X - 8 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y  }
	};
	for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
	{
		switch (temp->bBall.ID)
		{
		case 0:
			temp->bBall.color = White;
			temp->bBall.ballLocation = kitchenLoaction;
			break;
		case 1:
			temp->bBall.color = Yellow;
			temp->bBall.ballLocation = spotsLocation;
			break;
		case 2:
			temp->bBall.color = Blue;
			temp->bBall.ballLocation = BALL_LOCATION[Array[0]];
			break;
		case 3:
			temp->bBall.color = Red;
			temp->bBall.ballLocation = BALL_LOCATION[Array[1]];
			break;
		case 4:
			temp->bBall.color = Purple;
			temp->bBall.ballLocation = BALL_LOCATION[Array[2]];
			break;
		case 5:
			temp->bBall.color = Pink;
			temp->bBall.ballLocation = BALL_LOCATION[Array[3]];
			break;
		case 6:
			temp->bBall.color = Green;
			temp->bBall.ballLocation = BALL_LOCATION[Array[4]];
			break;
		case 7:
			temp->bBall.color = Caramel;
			temp->bBall.ballLocation = BALL_LOCATION[Array[5]];
			break;
		case 8:
			temp->bBall.color = Black;
			temp->bBall.ballLocation = BALL_LOCATION[Array[6]];
			break;
		case 9:
			temp->bBall.color = Yellow_White;
			temp->bBall.ballLocation = { spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL,spotsLocation.Y };
			break;
		}
	}
}



void load_img()
{
	loadimage(&img_start, _T("Source/background1.jpg"));
	loadimage(&img_whiteball, _T("Source/whiteball.png"));
	loadimage(&img_whiteballblock, _T("Source/白球遮罩2.png"));
	loadimage(&img_whiteball2, _T("Source/whiteball.png"));
	loadimage(&img_button, _T("Source/菜单1.jpg"));
	loadimage(&img_startbutton, _T("Source/开始游戏1.jpg"));
	loadimage(&img_continuebutton, _T("Source/继续游戏.jpg"));
	loadimage(&img_helpbutton, _T("Source/游戏帮助.jpg"));
	loadimage(&img_qiutbutton, _T("Source/退出游戏.jpg"));
	loadimage(&img_gamemode, _T("Source/模式选择.jpg"));
	loadimage(&img_gamemodebackarrow1, _T("Source/模式选择返回箭头.jpg"));
	loadimage(&img_gamemodebackarrow2, _T("Source/返回.jpg"));
	loadimage(&img_nineball1, _T("Source/美式九球.png"));
	loadimage(&img_pool1, _T("Source/美式普尔.png"));
	loadimage(&img_snooker1, _T("Source/斯诺克.png"));
	loadimage(&img_nineball2, _T("Source/美式九球1.png"));
	loadimage(&img_pool2, _T("Source/美式普尔1.png"));
	loadimage(&img_snooker2, _T("Source/斯诺克1.png"));
	loadimage(&img_determine1, _T("Source/确认.png"));
	loadimage(&img_determine2, _T("Source/橙色确认.png"));
	loadimage(&img_little_loading_bk, _T("Source/little_loading_bk.jpg"));
	loadimage(&img_little_loading, _T("Source/little_loading.jpg"));
	loadimage(&img_little_loading2, _T("Source/little_loading.jpg"));
	loadimage(&img_loading_bar, _T("Source/loading_bar.jpg"));
	loadimage(&img_loading, _T("Source/loading.jpg"));
}




void DrawMenu()
{
	cleardevice();
	BeginBatchDraw();

	putimage(0, 0, &img_start);
	setbkmode(TRANSPARENT);
	setbkcolor(RGB(255, 192, 203));

	if (whiteball_roll == 1)
	{
		putimage(500, 450, &img_whiteball2);
		putimagePng(500, 450, &img_whiteballblock);
	}
	Sleep(10);
}
void UpdateWithoutInput_menu()
{
	menu_angle1 = menu_angle1 + 0.05;
	rotateimage(&img_whiteball2, &img_whiteball, menu_angle1);
	whiteball_roll = 1;
}
void UpdateWithInput_menu()
{
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.x >= 130 && m.x <= 250 && m.y <= 506 && m.y >= 400)//开始游戏
		{
			pickstart = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				ChooseGamemode();
				if (gameStatus)
					loading();
			}
		}
		else
		{
			pickstart = 0;
		}
		if (m.x >= 315 && m.x <= 440 && m.y <= 506 && m.y >= 400)
		{
			pickcontinue = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				UpdateSettingFromFile();
				gameStatus = 2;
				loading();
			}
		}
		else
		{
			pickcontinue = 0;
		}
		if (m.x >= 130 && m.x <= 250 && m.y <= 650 && m.y >= 536)
		{
			pickhelp = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				DisplaySetting();
			}
		}
		else
		{
			pickhelp = 0;
		}
		if (m.x >= 315 && m.x <= 440 && m.y <= 650 && m.y >= 536)
		{
			pickqiut = 1;
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
		else
		{
			pickqiut = 0;
		}
	}

	if (pickstart == 1)
	{
		putimage(0, 0, &img_startbutton);
	}
	else if (pickcontinue != 1 && pickhelp != 1 && pickqiut != 1)
	{
		putimage(0, 0, &img_button);
	}
	if (pickcontinue == 1)
	{
		putimage(0, 0, &img_continuebutton);
	}
	else if (pickstart != 1 && pickhelp != 1 && pickqiut != 1)
	{
		putimage(0, 0, &img_button);
	}
	if (pickhelp == 1)
		putimage(0, 0, &img_helpbutton);
	else if (pickcontinue != 1 && pickstart != 1 && pickqiut != 1)
		putimage(0, 0, &img_button);
	if (pickqiut == 1)
		putimage(0, 0, &img_qiutbutton);
	else if (pickcontinue != 1 && pickhelp != 1 && pickstart != 1)
		putimage(0, 0, &img_button);
	FlushBatchDraw();
}
void ChooseGamemode()
{
	littleloading();
	int back = 0, backhit = 0, nineball = 0, pool = 0, snooker = 0, determine = 0, hitdetermine = 0;
	int nineballhit = 0, poolhit = 0, snookerhit = 0;

	while (1)
	{
		putimage(0, 0, &img_gamemode);
		putimagePng(63, 682 - 359, &img_nineball1);
		putimagePng(63 + 350, 682 - 359, &img_pool1);
		putimagePng(63 + 700, 682 - 359, &img_snooker1);
		if (nineballhit)
			putimagePng(63, 682 - 359, &img_nineball2);
		if (poolhit)
			putimagePng(63 + 350, 682 - 359, &img_pool2);
		if (snookerhit)
			putimagePng(63 + 700, 682 - 359, &img_snooker2);
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.x >= 30 && m.x <= 75 && m.y >= 55 && m.y <= 120)
			{
				back = 1;
				if (m.uMsg == WM_LBUTTONUP)
					backhit = 1;
			}
			else
			{
				back = 0;
			}
			if ((m.x - 175) * (m.x - 175) + (m.y - 435) * (m.y - 435) <= 105 * 105)
			{
				nineball = 1;
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					nineballhit = 1;
					poolhit = 0;
					snookerhit = 0;
					Gamemode = 2;
				}
			}
			else
				nineball = 0;
			if ((m.x - 525) * (m.x - 525) + (m.y - 435) * (m.y - 435) <= 105 * 105)
			{
				pool = 1;
				if (m.uMsg == WM_LBUTTONUP)
				{
					nineballhit = 0;
					poolhit = 1;
					snookerhit = 0;
					Gamemode = 0;
				}
			}
			else
				pool = 0;
			if ((m.x - 875) * (m.x - 875) + (m.y - 435) * (m.y - 435) <= 105 * 105)
			{
				snooker = 1;
				if (m.uMsg == WM_LBUTTONUP)
				{
					nineballhit = 0;
					poolhit = 0;
					snookerhit = 1;
					Gamemode = 1;
				}
			}
			else
				snooker = 0;
			if (m.x >= 1023 - 220 && m.x <= 1023 && m.y >= 682 - 70 && m.y <= 682)
			{
				determine = 1;
				if (m.uMsg == WM_LBUTTONUP)
				{
					hitdetermine = 1;
				}
			}
			else
				determine = 0;
		}
		if (back) {

			putimage(0, 0, &img_gamemodebackarrow1);
		}
		else
			putimage(0, 0, &img_gamemodebackarrow2);
		if (nineball)
			putimagePng(63, 682 - 359, &img_nineball2);
		else
			putimagePng(63, 682 - 359, &img_nineball1);
		if (pool)
			putimagePng(63 + 350, 682 - 359, &img_pool2);
		else
			putimagePng(63 + 350, 682 - 359, &img_pool1);
		if (snooker)
			putimagePng(63 + 700, 682 - 359, &img_snooker2);
		else
			putimagePng(63 + 700, 682 - 359, &img_snooker1);
		if (determine)
			putimagePng(1023 - 220, 682 - 70, &img_determine2);
		else
			putimagePng(1023 - 220, 682 - 70, &img_determine1);
		if (backhit)
			break;
		if (hitdetermine)
		{
			gameStatus = 1;
			break;
		}
		Animation();
	}
}
void littleloading()
{
	int i;
	int angle;
	angle = 0;
	putimage(0, 0, &img_little_loading_bk);
	for (i = 0; i < 50; i++) {
		angle = angle + 1;
		rotateimage(&img_little_loading2, &img_little_loading, PI / 100 * angle);
		putimage(1023 / 2 - 35, 621 / 2 - 35, &img_little_loading2);
		settextstyle(30, 0, L"宋体");
		outtextxy(1023 / 2 - 50, 621 / 2 + 100, L"加载中...");
		FlushBatchDraw();
		Sleep(10);
	}
}
void loading()
{
	int load;
	load = 0;
	putimage(0, 0, &img_loading);
	settextstyle(30, 0, L"宋体");
	outtextxy(400, 500, L"配置资源中...");
	for (load = 0; load < 36; load++) {
		putimage(140 + load * 20, 363, &img_loading_bar);
		Sleep(50);
		FlushBatchDraw();
	}
	Sleep(600);
}
void DisplaySetting()
{
	const TCHAR* fileStr[2] = { _T("BIN"),_T("TXT") };
	const TCHAR* disStr[2] = { _T("否"),_T("是") };

	initgraph(menuWidth, menuHeight);
	loadimage(&img_setting, _T("Source/settings.png"));
	putimage(0, 0, &img_setting);
	setbkmode(TRANSPARENT);
	setbkcolor(RGB(255, 192, 203));

	settextstyle(40, 0, _T("幼圆"), 0, 0, 1000, 0, 0, 0);
	settextcolor(WHITE);
	outtextxy(50, 30, L"帮助");

	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	line(50, 72, 1023 - 50, 72);

	settextstyle(25, 0, _T("楷体"), 0, 0, 200, 0, 0, 0);
	settextcolor(WHITE);;
	outtextxy(55, 150, L"保存模式");
	outtextxy(55, 200, L"是否有参考线");
	outtextxy(55, 250, L"清空所有存档");

	setfillcolor(BLUE);
	fillrectangle(1023 - 150, 600, 1023 - 50, 635);
	outtextxy(1023 - 150 + 22, 605, L"返回");
	while (1)
	{
		BeginBatchDraw();
		fillrectangle(300, 145, 400, 180);
		fillrectangle(300, 195, 400, 230);
		fillrectangle(300, 245, 400, 280);
		outtextxy(330, 150, fileStr[Filemode]);
		outtextxy(338, 200, disStr[isDisplayLine]);
		outtextxy(325, 250, L"清空");
		EndBatchDraw();

		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 400)
		{
			if (m.y >= 145 && m.y <= 180)
			{
				setlinecolor(BLACK);
				rectangle(300 - 2, 145 - 2, 400 + 2, 180 + 2);
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					Filemode = !Filemode;
					UpdateSettingFromGame();
				}
			}
			else if (m.y >= 195 && m.y <= 230)
			{
				setlinecolor(BLACK);
				rectangle(300 - 2, 195 - 2, 400 + 2, 230 + 2);
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					isDisplayLine = !isDisplayLine;
					UpdateSettingFromGame();
				}
			}
			else if (m.y >= 245 && m.y <= 280)
			{
				setlinecolor(BLACK);
				rectangle(300 - 2, 245 - 2, 400 + 2, 280 + 2);
				if (m.uMsg == WM_LBUTTONDOWN)
				{
					if (!ClearFile(Filemode))
					{
						MessageBox(NULL, _T("清除成功！"), _T("Manager"), MB_OK);
					}
					else {
						USES_CONVERSION;
						char s[1000];
						sprintf(s, "Error: %s", strerror(errno));
						MessageBox(NULL, A2W(s), _T("错误"), MB_OK | MB_ICONWARNING);
					}
				}
			}
			else {
				setlinecolor(WHITE);
				rectangle(300 - 2, 145 - 2, 400 + 2, 180 + 2);
				rectangle(300 - 2, 195 - 2, 400 + 2, 230 + 2);
				rectangle(300 - 2, 245 - 2, 400 + 2, 280 + 2);
			}
		}
		else if (m.x >= 1023 - 150 && m.x <= 1023 - 50 && m.y >= 600 && m.y <= 635)
		{
			setlinecolor(BLACK);
			rectangle(1023 - 150 - 2, 600 - 2, 1023 - 50 + 2, 635 + 2);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				gameStatus = 0;
				return;
			}
		}
		else {
			setlinecolor(WHITE);
			rectangle(300 - 2, 145 - 2, 400 + 2, 180 + 2);
			rectangle(300 - 2, 195 - 2, 400 + 2, 230 + 2);
			rectangle(300 - 2, 245 - 2, 400 + 2, 280 + 2);
			rectangle(1023 - 150 - 2, 600 - 2, 1023 - 50 + 2, 635 + 2);
		}
	}
}
void Animation()
{
	static double time_tick;
	double v0 = -1;
	static double vx = 1, vy = -1;
	double g = 0.00009;
	static double ball_x = 10 + (rand() % (1023 - 20)), ball_y = 704;
	setfillcolor(BLUE);
	vy += g * time_tick;
	ball_x += vx;
	ball_y = 680 + 1.5 * vy * time_tick;
	fillcircle(ball_x, ball_y, 20);
	//time_tick++;
	if (vy >= 1)
	{
		ball_x = 10 + (rand() % (1023 - 20));
		ball_y = 704;
		time_tick = 0;
		vy = -1;
	}

	static double ball_x1 = 10 + (rand() % (1023 - 20)), ball_y1 = 704;
	setfillcolor(RED);
	ball_x1 += vx;
	ball_y1 = 680 + 1.5 * vy * time_tick;
	fillcircle(ball_x1, ball_y1, 20);
	time_tick++;
	if (vy >= 1)
	{
		ball_x1 = 10 + (rand() % (1023 - 20));
		ball_y1 = 704;
		time_tick = 0;
		vy = -1;
	}
	Sleep(5);
	FlushBatchDraw();
	cleardevice();
}




void putimagePng(int img_x, int img_y, IMAGE* pSrcImg)
{
	DWORD* dst = GetImageBuffer();
	DWORD* src = GetImageBuffer(pSrcImg);
	int src_width = pSrcImg->getwidth();
	int src_height = pSrcImg->getheight();
	int dst_width = getwidth();
	int dst_height = getheight();

	int im_width, im_height;
	if (img_x + src_width > dst_width)
		im_width = dst_width - img_x;
	else
		im_width = src_width;
	if (img_y + src_height > dst_height)
		im_height = dst_height - img_y;
	else
		im_height = src_height;

	if (img_x < 0)
	{
		src = src - img_x;
		im_width = im_width + img_x;
		img_x = 0;
	}
	if (img_y < 0)
	{
		src = src - src_width * img_y;
		im_height = im_height + img_y;
		img_y = 0;
	}
	dst = dst + dst_width * img_y + img_x;

	for (int i = 0; i < im_height; i++)
	{
		for (int j = 0; j < im_width; j++)
		{
			int src_r = ((src[j] & 0xff0000) >> 16);
			int src_g = ((src[j] & 0xff00) >> 8);
			int src_b = src[j] & 0xff;
			int src_a = ((src[j] & 0xff000000) >> 24);
			int dst_r = ((dst[j] & 0xff0000) >> 16);
			int dst_g = ((dst[j] & 0xff00) >> 8);
			int dst_b = dst[j] & 0xff;
			dst[j] = ((src_r + dst_r * (255 - src_a) / 255) << 16)
				| ((src_g + dst_g * (255 - src_a) / 255) << 8)
				| (src_b + dst_b * (255 - src_a) / 255);
		}
		dst = dst + dst_width;
		src = src + src_width;
	}
}
