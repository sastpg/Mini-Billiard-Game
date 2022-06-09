#include "DataStructure.h"
#include "Physics.h"
#include <stdio.h>
#include<math.h>
#include<graphics.h>
#include<conio.h>
#include "CONST.h"
#include "Display.h"
#include "Rand.h"

#define rodlength 200
#define rodballdistance 30
#define extension_line_d 20
#define linelength 300
#define damper 0.993
#define radius RADIUS_BALL

extern int Gameover;
extern Mode Gamemode;
extern location kitchenLoaction;
extern location spotsLocation;
extern bBallNode* ballHead;
extern BOOL isQuit;
extern int Array[30];
extern bBallNode* ballTail;
extern int boardWidth[3];
extern int boardHeight[3];
extern int startX;
extern int startY;
extern int gameTime;
extern int turn;
extern int score[2];
extern int isDisplayBox;

static int Wrong = 0;
static int number;
static int isenterthehole = 0;
static int addgametime = 0;

int velocityBeg = 10;    //1-10
int BallNum;
double ball_x[22], ball_y[22];
double ball_vx[22], ball_vy[22];
int cur_state[22] = { 0 };	//0表示小球当前静止，1表示小球当前运动
double minDistance[22][2];
int isClickedMouse = 0;
double sinAngle, cosAngle;
double rodstart_x, rodstart_y;
double rodend_x, rodend_y;
double extension_line_bx, extension_line_by;
double extension_line_ex, extension_line_ey;

MOUSEMSG m;

//Pool
int isenter = 0;/*这句比赛是否进过球*/
char last[] = "Game Over";
char* winplayer = NULL;
int entertheball[22] = { 0 };/*该球是否进洞*/
bBallNode* into = NULL;

int mold[2] = { 0,1 };
int Pure = 0;
int Strip = 1;
int Finall = 2;

//Snooker
static int isMoved = 0;
int hitStripBall = 0;
int firstHitID = 0, k = 1;
int finalHitID = 0;
int snookerstripcount = 0, snookerpurecount = 0;
int foul = 0;
int isChosenBall = 1;
int objectBallID = 0;

//Nineball
int firstTouchedBallID = 0;
int isFirst = 1;
int isAnyballEntered = 0;
int touchedNum = 0;
static int isEntered[10];
int Freemode = 0;
extern int winner;
int isEnd = 0;
int min = 0;

void MouseEventProcess()
{
	int init_x = 0, init_y = 0;

	if (MouseHit())
	{
		m = GetMouseMsg();
		if (Gamemode == SNOOKER)
		{
			if (isChosenBall)
			{
				if (m.uMsg == WM_MOUSEMOVE && isClickedMouse == 0 && (m.x - ballHead->bBall.ballLocation.X) * (m.x - ballHead->bBall.ballLocation.X) + (m.y - ballHead->bBall.ballLocation.Y) * (m.y - ballHead->bBall.ballLocation.Y) > RADIUS_BALL * RADIUS_BALL)
				{
					double d;
					d = sqrt((m.x - ball_x[0]) * (m.x - ball_x[0]) + (m.y - ball_y[0]) * (m.y - ball_y[0]));
					cosAngle = (m.x - ball_x[0]) / d;
					sinAngle = (m.y - ball_y[0]) / d;
					rodstart_x = ball_x[0] + rodballdistance * cosAngle;
					rodstart_y = ball_y[0] + rodballdistance * sinAngle;
					rodend_x = ball_x[0] + (rodlength + rodballdistance) * cosAngle;
					rodend_y = ball_y[0] + (rodlength + rodballdistance) * sinAngle;
					extension_line_bx = ball_x[0] - extension_line_d * cosAngle;
					extension_line_by = ball_y[0] - extension_line_d * sinAngle;
					extension_line_ex = ball_x[0] - (linelength + rodballdistance) * cosAngle;
					extension_line_ey = ball_y[0] - (linelength + rodballdistance) * sinAngle;
				}
				if (m.uMsg == WM_LBUTTONUP && (m.x - ballHead->bBall.ballLocation.X) * (m.x - ballHead->bBall.ballLocation.X) + (m.y - ballHead->bBall.ballLocation.Y) * (m.y - ballHead->bBall.ballLocation.Y) > RADIUS_BALL * RADIUS_BALL)
				{
					isenterthehole = 0;
					addgametime = 1;
					isClickedMouse = 1;
					cur_state[0] = 1;
					Wrong = 0;
				}
				if (!isMoved)
				{
					if (m.uMsg == WM_MOUSEMOVE && (m.x - ballHead->bBall.ballLocation.X) * (m.x - ballHead->bBall.ballLocation.X) + (m.y - ballHead->bBall.ballLocation.Y) * (m.y - ballHead->bBall.ballLocation.Y) <= RADIUS_BALL * RADIUS_BALL)
					{
						ballHead->bBall.ballLocation.X = m.x;
						ballHead->bBall.ballLocation.Y = m.y;
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONDOWN)
						{
							isMoved = 1;
							init_x = ballHead->bBall.ballLocation.X;
							init_y = ballHead->bBall.ballLocation.Y;
						}
					}
				}
			}
			else {
				for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
				{
					if (m.uMsg == WM_LBUTTONUP && (m.x - temp->bBall.ballLocation.X) * (m.x - temp->bBall.ballLocation.X) + (m.y - temp->bBall.ballLocation.Y) * (m.y - temp->bBall.ballLocation.Y) <= RADIUS_BALL * RADIUS_BALL)
					{
						isChosenBall = 1;
						objectBallID = temp->bBall.ID;
						break;
					}
				}
			}
		}
		else {
			if (m.uMsg == WM_MOUSEMOVE && isClickedMouse == 0)
			{
				double d;
				d = sqrt((m.x - ball_x[0]) * (m.x - ball_x[0]) + (m.y - ball_y[0]) * (m.y - ball_y[0]));
				cosAngle = (m.x - ball_x[0]) / d;
				sinAngle = (m.y - ball_y[0]) / d;
				rodstart_x = ball_x[0] + rodballdistance * cosAngle;
				rodstart_y = ball_y[0] + rodballdistance * sinAngle;
				rodend_x = ball_x[0] + (rodlength + rodballdistance) * cosAngle;
				rodend_y = ball_y[0] + (rodlength + rodballdistance) * sinAngle;
				extension_line_bx = ball_x[0] - extension_line_d * cosAngle;
				extension_line_by = ball_y[0] - extension_line_d * sinAngle;
				extension_line_ex = ball_x[0] - (linelength + rodballdistance) * cosAngle;
				extension_line_ey = ball_y[0] - (linelength + rodballdistance) * sinAngle;
			}
			if (m.uMsg == WM_LBUTTONUP)
			{
				if (Freemode == 0)
				{
					isenterthehole = 0;
					addgametime = 1;
					isClickedMouse = 1;
					cur_state[0] = 1;

					//Pool Reset
					Wrong = 0;

					//Nineball Reset
					firstTouchedBallID = 0;
					isFirst = 1;
					isAnyballEntered = 0;
					touchedNum = 0;
					for (int i = 1; i < 10; i++)
					{
						if (isEntered[i] == 0)
						{
							min = i;
							break;
						}
					}
				}
				else {
					ResetLocation(0, m.x, m.y);
					Freemode = 0;
				}
			}
		}
	}
}
void UpdateBallPosition()
{
	for (int i = 0; i < BallNum; i++)
	{
		ball_x[i] += ball_vx[i];
		ball_y[i] += ball_vy[i];
		ball_vx[i] *= damper;
		ball_vy[i] *= damper;
		if (ball_vx[i] * ball_vx[i] + ball_vy[i] * ball_vy[i] <= 0.01)
		{
			ball_vx[i] = 0;
			ball_vy[i] = 0;
			cur_state[i] = 0;
		}
	}
}
void TouchedWall()
{
	int left = startX + radius;
	int right = startX + boardWidth[Gamemode] - radius;
	int top = startY + radius;
	int bottom = startY + boardHeight[Gamemode] - radius;

	for (int i = 0; i < BallNum; i++)
	{
		if ((ball_x[i] <= left && ball_y[i] <= top) || (ball_x[i] <= left && ball_y[i] >= bottom) || (ball_x[i] >= right && ball_y[i] <= top) || (ball_x[i] >= right && ball_y[i] >= bottom))
		{
			ball_vx[i] = ball_vx[i] * (-1);
			ball_vy[i] = ball_vy[i] * (-1);
			if (i == 0)
			{
				touchedNum++;
			}
		}
		else {
			if ((ball_x[i] <= left && ball_y[i] > top && ball_y[i] < bottom) || (ball_x[i] >= right && ball_y[i] > top && ball_y[i] < bottom))
			{
				ball_vx[i] = ball_vx[i] * (-1);
				if (i == 0)
				{
					touchedNum++;
				}
			}
			if ((ball_y[i] <= top && ball_x[i] > left && ball_x[i] < right) || ball_y[i] >= bottom && ball_x[i] > left && ball_x[i] < right)
			{
				ball_vy[i] = ball_vy[i] * (-1);
				if (i == 0)
				{
					touchedNum++;
				}
			}

		}
	}
}
int Enterhole()
{
	int width = boardWidth[Gamemode];
	int height = boardHeight[Gamemode];

	startX = 38;
	startY = 40;
	for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
	{
		double mx, my;
		mx = startX;
		my = startY;

		if (sqrt(pow(temp->bBall.ballLocation.X - mx, 2) + pow(temp->bBall.ballLocation.Y - my, 2)) <= RADIUS_HOLE * 2.0) {
			return temp->bBall.ID;
		}
		mx = startX + width / 2.0;
		my = startY;
		if (sqrt(pow(temp->bBall.ballLocation.X - mx, 2) + pow(temp->bBall.ballLocation.Y - my, 2)) <= RADIUS_HOLE * 2.0) {
			return temp->bBall.ID;
		}
		mx = startX + width;
		my = startY;
		if (sqrt(pow(temp->bBall.ballLocation.X - mx, 2) + pow(temp->bBall.ballLocation.Y - my, 2)) <= RADIUS_HOLE * 2.0) {
			return temp->bBall.ID;
		}
		mx = startX;
		my = startY + height;
		if (sqrt(pow(temp->bBall.ballLocation.X - mx, 2) + pow(temp->bBall.ballLocation.Y - my, 2)) <= RADIUS_HOLE * 2.0) {
			return temp->bBall.ID;
		}
		mx = startX + width / 2.0;
		my = startY + height;
		if (sqrt(pow(temp->bBall.ballLocation.X - mx, 2) + pow(temp->bBall.ballLocation.Y - my, 2)) <= RADIUS_HOLE * 2.0) {
			return temp->bBall.ID;
		}
		mx = startX + width;
		my = startY + height;
		if (sqrt(pow(temp->bBall.ballLocation.X - mx, 2) + pow(temp->bBall.ballLocation.Y - my, 2)) <= RADIUS_HOLE * 2.0) {
			return temp->bBall.ID;
		}
	}
	return -1;
}
void ScoreCal()
{
	for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
	{
		number = Enterhole();
		if (number == temp->bBall.ID)
		{
			temp->bBall.ballLocation.X = 0;
			temp->bBall.ballLocation.Y = 0;
			temp->bBall.ballVelocity.velocity_X = 0;
			temp->bBall.ballVelocity.velocity_Y = 0;
			setcolor(GREEN);
			setfillcolor(GREEN);
			fillcircle(0, 0, RADIUS_BALL);
			entertheball[number] = 1;
			cur_state[number] = 0;
			into = temp;
		}
		if (number == 0)//白球进球
		{
			Freemode = isDisplayBox = 1;
			cur_state[0] = 0;
			addgametime = 0;
			ResetVelocity(0, 0, 0);
			turn = !turn;
			gameTime++;
			switch (Gamemode)
			{
			case POOL:
				ResetLocation(0, 0, 0);
				Wrong = 1;
				break;
			case SNOOKER:
				temp->bBall.ballLocation.X = rand() % 957 - RADIUS_BALL;
				temp->bBall.ballLocation.Y = rand() % 442 - RADIUS_BALL;
				if (temp->bBall.ballLocation.X <= RADIUS_BALL + 38)
				{
					temp->bBall.ballLocation.X = RADIUS_BALL + 70;
				}
				if (temp->bBall.ballLocation.Y < 40 + RADIUS_BALL)
				{
					temp->bBall.ballLocation.Y = RADIUS_BALL + 70;
				}
				Wrong = 1;
				break;
			case NINEBALL:
				ResetLocation(0, 0, 0);
				score[turn]++;
				if (isEnd == 1)
				{
					ResetLocation(9, spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL, spotsLocation.Y);
					isEnd = 0;
				}
				break;
			}
		}
		if (Gamemode == POOL)
		{
			Poolscore();
			if (Wrong == 1 && isenterthehole == 1)
			{
				/*白球和其他球一起进洞*/
				into->bBall.ballLocation.X = rand() % 156 - RADIUS_BALL;
				into->bBall.ballLocation.Y = rand() % 789 - RADIUS_BALL;
				if (into->bBall.ballLocation.X <= RADIUS_BALL + 28)
				{
					into->bBall.ballLocation.X = RADIUS_BALL + 77;
				}
				if (into->bBall.ballLocation.Y < 40 + RADIUS_BALL)
				{
					into->bBall.ballLocation.Y = RADIUS_BALL + 70;
				}
				into->bBall.ballVelocity.velocity_X = 0;
				into->bBall.ballVelocity.velocity_Y = 0;
				score[!turn]--;/*进白球时转换过角色*/
				Wrong = 0;
			}
		}
		else if (Gamemode == SNOOKER)
		{
			if (number == temp->bBall.ID)
				SnookerRule();
		}
		else if (Gamemode == NINEBALL)
		{
			if (number != 0 && number != -1 && isEntered[number] == 0)//进球时
			{
				isEntered[number] = 1;
				isAnyballEntered = 1;
				if (number == 9)
				{
					isEnd = 1;
				}
			}
			if (isClickedMouse == 0 && addgametime == 1)//一局结束
			{
				if (gameTime == 0)
				{
					if (firstTouchedBallID == 1)
					{
						if (!isAnyballEntered)
						{
							turn = !turn;
							gameTime++;
						}
						else {
							gameTime += 2;
							if (isEnd)
							{
								winner = turn;
								score[turn] = 10000;
							}
						}
					}
					else {
						//重开
						score[turn]++;
						free(ballHead);
						RandomArray(7);
						NineballInit();
						cur_state[0] = 0;
						gameTime = 0;
						isEnd = 0;
					}
				}
				else {
					if (firstTouchedBallID == min)
					{
						if (!isAnyballEntered)
						{
							turn = !turn;
							gameTime++;
						}
						else {
							gameTime += 2;
							if (isEnd)
							{
								winner = turn;
								Gameover = 1;
							}
						}
					}
					else if (firstTouchedBallID == 0)
					{
						turn = !turn;
						gameTime++;
					}
					else {
						score[turn]++;
						cur_state[0] = 0;
						turn = !turn;
						Freemode = isDisplayBox = 1;
						ResetLocation(0, 0, 0);
						ResetVelocity(0, 0, 0);
						if (isEnd == 1)
						{
							ResetLocation(9, spotsLocation.X - 4 * sin(PI / 3) * RADIUS_BALL, spotsLocation.Y);
							isEnd = 0;
						}
					}
				}
				addgametime = 0;
			}
		}
	}
	if (Gamemode == SNOOKER)
		SnookerScore();
}



//POOL
void Poolscore() {
	if (number != 0 && number != -1) {
		isenterthehole = 1;
		entertheball[number] = 1;
		if (isenter == 0) /*没有进过球*/ {
			isenter = 1;
			switch (number) {
			case 1: case 2: case  3: case 4: case 5: case 6: case 7: mold[turn] = Pure;
				score[turn]++;
				break;
			case 9: case 10: case 11: case 12: case 13: case 14: case 15: mold[turn] = Strip;
				score[turn]++;
				break;
			default:/*进黑八*/
				mold[turn] = Finall;
				Gameover = 1;
			}
		}
		else {/*进过球*/
			if (mold[turn] == Pure)/*纯色*/ {
				switch (number) {
				case 1: case 2: case  3: case 4: case 5: case 6: case 7:
					score[turn]++;
					break;
				case 9: case 10: case 11: case 12: case 13: case 14: case 15:
					score[!turn]++;
					turn = !turn;
					gameTime++;
					break;
				default:
					if (!allballenter()) {
						mold[turn] = Finall;
						Gameover = 1;
					}
					else {
						Playerwin();/*自己打完所有球赢的方法*/
					}
				}
			}
			else if (mold[turn] == Strip)/*花色*/ {
				switch (number) {
				case 1: case 2: case  3: case 4: case 5: case 6: case 7:
					score[!turn]++;
					turn = !turn;
					gameTime++;
					break;
				case 9: case 10: case 11: case 12: case 13: case 14: case 15:
					score[turn]++;
					break;
				default:
					if (!allballenter()) {
						mold[turn] = Finall;
						Gameover = 1;
					}
					else {
						Playerwin();
					}
				}
			}
		}
	}
	if (mold[turn] == Finall) {/*没有打完自己的球就进了黑八*/
		if (turn == 0) {
			//strcpy(winplayer, "PLAYER B WIN");
			winner = B;
		}
		else
		{
			winner = A;
			//strcpy(winplayer, "PLAYER A WIN");
		}
		/*settextcolor(Black);
		settextstyle(25, 0, _T("Times New Roman"), 0, 0, 1000, 0, 0, 0);
		outtextxy(startX + 50, startY - 50, winplayer);
		outtextxy(startX + 50, startY - 60, last);*/
	}
	if (isenterthehole == 0 && isClickedMouse == 0 && addgametime == 1) {
		turn = !turn;
		gameTime++;
		addgametime = 0;
	}
}
int allballenter() {
	int i, ispure = 1, isstrip = 1;
	for (i = 1; i < 8; i++) {
		if (entertheball[i] != 1) {
			ispure = 0;
			break;
		}
	}
	for (i = 9; i < 16; i++) {
		if (entertheball[i] != 1) {
			isstrip = 0;
			break;
		}
	}
	if (ispure == 1 && mold[turn] == Pure) {
		return 1;
	}
	else if (isstrip == 1 && mold[turn] == Strip) {
		return 1;
	}
	return 0;
}
void Playerwin()
{
	if (turn == A)
	{
		//strcpy(winplayer, "PLAYER A WIN");
		winner = A;
		Gameover = 1;
	}
	else {
		//strcpy(winplayer, "PLAYER B WIN");
		winner = B;
		Gameover = 1;
	}
}
void showwinner() {
	int width = boardWidth[Gamemode];
	int height = boardHeight[Gamemode];
	const TCHAR* winnerstr[2] = { _T("PLAYER A WIN"),_T("PLAYER B WIN") };
	int strheight = textheight(winnerstr[winner]);
	int strwidth = textwidth(winnerstr[winner]);

	settextcolor(Black);
	settextstyle(40, 0, _T("Cambria"), 0, 0, 1000, 1, 0, 0);
	outtextxy(startX + width / 2 - strwidth / 2 - 30, startY + height / 2 - strheight / 2, winnerstr[turn]);
}


//SNOOKER
void SnookerRule()
{
	if (number != -1 /*&& isenterthehole == 0*/)
	{
		isenterthehole = 1;
		if (number <= 15 && number >= 1)
		{
			snookerpurecount++;
			entertheball[number] = 1;
			if (hitStripBall == 0 && firstHitID >= 16)//该打红球进洞时第一球打到了彩球
				foul = 1;
			if (hitStripBall == 0 && snookerstripcount > 0)//该打红球进洞时把彩球碰进洞
				foul = 1;
			if (hitStripBall == 1)//该打彩球却把红球碰进洞
				foul = 1;
		}
		else if (number >= 16 && number <= 21)
		{
			snookerstripcount++;
			entertheball[number] = 1;
			if (hitStripBall == 1 && snookerpurecount > 0)//该打彩球进洞时把红球进洞
				foul = 1;
			if (hitStripBall == 1 && snookerstripcount > 1)//打彩球时把两个彩球打进洞
				foul = 1;
			if (hitStripBall == 1 && firstHitID < 16)//该打彩球进洞时第一球打到了红球
				foul = 1;
			if (hitStripBall == 0)//该打红球却把彩球碰进洞
				foul = 1;
			if (firstHitID != objectBallID)
				foul = 1;
		}
		else
		{
			entertheball[number] = 1;
			foul = 2;
		}
	}
}
void SnookerScore()
{
	int i = 0;
	if (/*isenterthehole == 0&&*/isClickedMouse == 0 && addgametime == 1) {
		if (isenterthehole == 0)
		{
			turn = !turn;
			if (hitStripBall == 0 && firstHitID >= 16)
			{
				score[turn] += 4 > firstHitID - 14 ? 4 : firstHitID - 14;
				MessageBox(NULL, _T("非法击球！"), _T("Reminder"), MB_OK);
			}
			if (hitStripBall == 1 && firstHitID != objectBallID)
			{
				hitStripBall = 0;
				if (firstHitID > objectBallID)
					score[turn] += 4 > firstHitID - 14 ? 4 : firstHitID - 14;
				else
					score[turn] += 4 > objectBallID - 14 ? 4 : objectBallID - 14;
				MessageBox(NULL, _T("非法击球！"), _T("Reminder"), MB_OK);
			}
		}
		else
		{
			if (hitStripBall == 0 && foul == 0)
			{
				hitStripBall = 1;
				isChosenBall = 0;
				MessageBox(NULL, _T("下一杆请击打彩球！"), _T("提示"), MB_OK);
				score[turn] += snookerpurecount;
			}
			else if (hitStripBall == 0 && foul == 1)
			{
				turn = !turn;
				isChosenBall = 1;
				if (firstHitID >= 16)
				{
					score[turn] += 4 > firstHitID - 14 ? 4 : firstHitID - 14;
					MessageBox(NULL, _T("击错目标球！"), _T("犯规"), MB_OK);
					for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
					{
						if (temp->bBall.ID >= 16 && entertheball[temp->bBall.ID] == 1)
						{
							switch (temp->bBall.ID)
							{
								i = temp->bBall.ID;
							case 16:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 17:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y + 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 18:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 19:
								temp->bBall.ballLocation.X = startX + 0.5 * boardWidth[Gamemode];
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							case 20:
								temp->bBall.ballLocation.X = startX + 0.25 * boardWidth[Gamemode];
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							case 21:
								temp->bBall.ballLocation.X = startX + boardWidth[Gamemode] * BLACK_RATIO;
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							}
						}

					}
				}
				else
				{
					MessageBox(NULL, _T("目标球和彩球都进洞！"), _T("犯规"), MB_OK);
					for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
					{
						if (temp->bBall.ID >= 16 && entertheball[temp->bBall.ID] == 1)
						{
							i = temp->bBall.ID;
							switch (temp->bBall.ID)
							{
							case 16:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 17:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y + 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 18:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 19:
								temp->bBall.ballLocation.X = startX + 0.5 * boardWidth[Gamemode];
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							case 20:
								temp->bBall.ballLocation.X = startX + 0.25 * boardWidth[Gamemode];
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							case 21:
								temp->bBall.ballLocation.X = startX + boardWidth[Gamemode] * BLACK_RATIO;
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							}
						}

					}
					score[turn] += 4 > i - 14 ? 4 : i - 14;
				}
			}
			else if (hitStripBall == 1 && foul == 0)
			{
				hitStripBall == 0;
				isChosenBall = 1;
				for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
				{
					if (temp->bBall.ID >= 16 && entertheball[temp->bBall.ID] == 1)
					{
						i = temp->bBall.ID;
						switch (temp->bBall.ID)
						{
						case 16:
							temp->bBall.ballLocation.X = kitchenLoaction.X;
							temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
							break;
						case 17:
							temp->bBall.ballLocation.X = kitchenLoaction.X;
							temp->bBall.ballLocation.Y = kitchenLoaction.Y + 1.0 / 6 * boardHeight[Gamemode];
							break;
						case 18:
							temp->bBall.ballLocation.X = kitchenLoaction.X;
							temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
							break;
						case 19:
							temp->bBall.ballLocation.X = startX + 0.5 * boardWidth[Gamemode];
							temp->bBall.ballLocation.Y = spotsLocation.Y;
							break;
						case 20:
							temp->bBall.ballLocation.X = startX + 0.25 * boardWidth[Gamemode];
							temp->bBall.ballLocation.Y = spotsLocation.Y;
							break;
						case 21:
							temp->bBall.ballLocation.X = startX + boardWidth[Gamemode] * BLACK_RATIO;
							temp->bBall.ballLocation.Y = spotsLocation.Y;
							break;
						}
					}

				}
				score[turn] += i - 14;
			}
			else if (hitStripBall == 1 && foul == 1)
			{
				turn = !turn;
				isChosenBall = 1;
				if (firstHitID < 16)
				{
					MessageBox(NULL, _T("击错目标球！"), _T("犯规"), MB_OK);
					score[turn] += 4 > firstHitID - 14 ? 4 : firstHitID - 14;
				}
				else if (snookerpurecount > 0 || snookerstripcount > 1)
				{
					MessageBox(NULL, _T("目标球和其他球都进洞！"), _T("犯规"), MB_OK);
					for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
					{
						if (temp->bBall.ID >= 16 && entertheball[temp->bBall.ID] == 1)
						{
							i = temp->bBall.ID;
							switch (temp->bBall.ID)
							{
							case 16:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 17:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y + 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 18:
								temp->bBall.ballLocation.X = kitchenLoaction.X;
								temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
								break;
							case 19:
								temp->bBall.ballLocation.X = startX + 0.5 * boardWidth[Gamemode];
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							case 20:
								temp->bBall.ballLocation.X = startX + 0.25 * boardWidth[Gamemode];
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							case 21:
								temp->bBall.ballLocation.X = startX + boardWidth[Gamemode] * BLACK_RATIO;
								temp->bBall.ballLocation.Y = spotsLocation.Y;
								break;
							}
						}
					}
					score[turn] += 4 > i - 14 ? 4 : i - 14;
				}
			}
			else if (foul == 2)
			{
				turn = !turn;
				isChosenBall = 1;
				MessageBox(NULL, _T("白球进洞！"), _T("犯规"), MB_OK);
				for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
				{
					if (temp->bBall.ID >= 16 && entertheball[temp->bBall.ID] == 1)
					{
						i = temp->bBall.ID;
						switch (temp->bBall.ID)
						{
						case 16:
							temp->bBall.ballLocation.X = kitchenLoaction.X;
							temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
							break;
						case 17:
							temp->bBall.ballLocation.X = kitchenLoaction.X;
							temp->bBall.ballLocation.Y = kitchenLoaction.Y + 1.0 / 6 * boardHeight[Gamemode];
							break;
						case 18:
							temp->bBall.ballLocation.X = kitchenLoaction.X;
							temp->bBall.ballLocation.Y = kitchenLoaction.Y - 1.0 / 6 * boardHeight[Gamemode];
							break;
						case 19:
							temp->bBall.ballLocation.X = startX + 0.5 * boardWidth[Gamemode];
							temp->bBall.ballLocation.Y = spotsLocation.Y;
							break;
						case 20:
							temp->bBall.ballLocation.X = startX + 0.25 * boardWidth[Gamemode];
							temp->bBall.ballLocation.Y = spotsLocation.Y;
							break;
						case 21:
							temp->bBall.ballLocation.X = startX + boardWidth[Gamemode] * BLACK_RATIO;
							temp->bBall.ballLocation.Y = spotsLocation.Y;
							break;
						}
					}
				}
				score[turn] += 4 > i - 14 ? 4 : i - 14;
				isMoved = 0;
			}
		}
		gameTime++;
		addgametime = 0;
		snookerstripcount = 0;
		snookerpurecount = 0;
		foul = 0;
	}
}


void TouchedBall()
{
	MinDistance();
	Push();
	ChangeSpeed();
	Sleep(2);
}
void MinDistance()
{
	for (int i = 0; i < BallNum; i++)
	{
		minDistance[i][0] = 9999999;
		minDistance[i][1] = -1;
	}
	for (int i = 0; i < BallNum; i++)
	{
		for (int j = 0; j < BallNum; j++)
		{
			if (i != j)     //距离不与自己比
			{
				double d;
				d = (ball_x[i] - ball_x[j]) * (ball_x[i] - ball_x[j]) + (ball_y[j] - ball_y[i]) * (ball_y[j] - ball_y[i]);  //球之间的距离
				if (minDistance[i][0] > d)
				{
					minDistance[i][0] = d;         //获取距离最小值
					minDistance[i][1] = j;            //获取与i号球距离最近的下标



					//Snooker
					if (isClickedMouse == 0)
						k = 1;
					if (k == 1 && minDistance[0][0] <= 4 * RADIUS_BALL * RADIUS_BALL)
					{
						firstHitID = minDistance[0][1];
						k = 0;
					}
					if (minDistance[0][0] <= 4 * RADIUS_BALL * RADIUS_BALL)
						finalHitID = minDistance[0][1];
				}
			}
		}
	}
}
void Push()
{
	double d1, d2;
	double cosA, sinA;
	double p;
	for (int i = 0; i < BallNum; i++)
	{
		if (minDistance[i][0] <= 4 * radius * radius)
		{
			int j = minDistance[i][1];
			p = 2 * radius - sqrt(minDistance[i][0]) + 2;
			d1 = ball_x[i] - ball_x[j];
			d2 = ball_y[i] - ball_y[j];
			cosA = sqrt(d1 * d1 / (d1 * d1 + d2 * d2));       //小球连线与x负方向的cos,sin值
			sinA = sqrt(d2 * d2 / (d1 * d1 + d2 * d2));
			if (d1 > 0)
			{
				cosA = (-1) * cosA;
			}
			if (d2 > 0)
			{
				sinA = (-1) * sinA;
			}

			ball_x[j] += p * cosA;
			ball_y[j] += p * sinA;




			//Nineball 判定白球第一个撞到的ID
			if (i == 0 && isFirst == 1)
			{
				firstTouchedBallID = j;
				isFirst = 0;
			}
		}
	}
}
void ChangeSpeed()
{
	struct Vectors
	{
		double s_x, s_y, t_x, t_y;     //球心连线向量与垂直连线向量
		double s1_x, s1_y, t1_x, t1_y;   //球心连线向量与垂直连线单位向量
		double v1s, v2s, v1t, v2t;  //v1,v2在s与t上投影
		double v1s_x, v1s_y, v2s_x, v2s_y, v1t_x, v1t_y, v2t_x, v2t_y;     //用于投影向量化
	};
	Vectors a;
	for (int i = 0; i < BallNum; i++)
	{
		double temp;
		if (minDistance[i][0] <= 4 * radius * radius && cur_state[i] == 1)            //判断是否碰撞，若是进行速度动量分配，方向传递
		{
			int j = minDistance[i][1];
			a.s_x = ball_x[i] - ball_x[j];
			a.s_y = ball_y[i] - ball_y[j];    //计算s(球心连线)向量
			a.t_x = a.s_y * (-1);
			a.t_y = a.s_x;
			a.s1_x = a.s_x / (sqrt(a.s_x * a.s_x + a.s_y * a.s_y));
			a.s1_y = a.s_y / (sqrt(a.s_x * a.s_x + a.s_y * a.s_y));  //s单位向量
			a.t1_x = a.t_x / (sqrt(a.t_x * a.t_x + a.t_y * a.t_y));
			a.t1_y = a.t_y / (sqrt(a.t_x * a.t_x + a.t_y * a.t_y));  //t单位向量
			a.v1s = ball_vx[i] * a.s1_x + ball_vy[i] * a.s1_y;
			a.v1t = ball_vx[i] * a.t1_x + ball_vy[i] * a.t1_y;     //v1在s,t上的投影
			a.v2s = ball_vx[j] * a.s1_x + ball_vy[j] * a.s1_y;
			a.v2t = ball_vx[j] * a.t1_x + ball_vy[j] * a.t1_y;     //v2在s,t上的投影
			temp = a.v1s;
			a.v1s = a.v2s;
			a.v2s = temp;                                      //交换s方向的速度的值
			//转换为向量
			a.v1s_x = a.v1s * a.s1_x;
			a.v1s_y = a.v1s * a.s1_y;
			a.v1t_x = a.v1t * a.t1_x;
			a.v1t_y = a.v1t * a.t1_y;
			ball_vx[i] = 1.0 * (a.v1s_x * 1 + a.v1t_x * 1);
			ball_vy[i] = 1.0 * (a.v1s_y * 1 + a.v1t_y * 1);

			a.v2s_x = a.v2s * a.s1_x;
			a.v2s_y = a.v2s * a.s1_y;
			a.v2t_x = a.v2t * a.t1_x;
			a.v2t_y = a.v2t * a.t1_y;
			ball_vx[j] = 1.0 * (a.v2s_x * 1 + a.v2t_x * 1);   //还原至速度
			ball_vy[j] = 1.0 * (a.v2s_y * 1 + a.v2t_y * 1);
			cur_state[j] = 1;
			minDistance[j][0] = 999999999;   // 避免交换两次速度，又回去了
			minDistance[j][1] = -1;
		}
	}
}
void Boom()
{
	switch (Gamemode)
	{
	case POOL:
		BallNum = 16;
		break;
	case SNOOKER:
		BallNum = 22;
		break;
	case NINEBALL:
		BallNum = 10;
		break;
	}
	bBallNode* temp = ballHead;
	for (int i = 0; i < BallNum; i++)
	{
		ball_x[i] = temp->bBall.ballLocation.X;
		ball_y[i] = temp->bBall.ballLocation.Y;
		ball_vx[i] = temp->bBall.ballVelocity.velocity_X;
		ball_vy[i] = temp->bBall.ballVelocity.velocity_Y;
		temp = temp->next;
	}

	TouchedWall();
	UpdateBallPosition();
	TouchedBall();
	WhetherStop();



	bBallNode* finish = ballHead;

	for (int i = 0; i < BallNum; i++)
	{
		finish->bBall.ballLocation.X = ball_x[i];
		finish->bBall.ballLocation.Y = ball_y[i];
		finish->bBall.ballVelocity.velocity_X = ball_vx[i];
		finish->bBall.ballVelocity.velocity_Y = ball_vy[i];
		finish = finish->next;
	}
}
void WhetherStop()
{
	int stopnum = 0;

	for (int i = 0; i < BallNum; i++)
	{
		if (cur_state[i] == 0)
			stopnum++;
	}
	if (stopnum == BallNum)
	{
		isClickedMouse = 0;
		double d;
		d = sqrt((m.x - ball_x[0]) * (m.x - ball_x[0]) + (m.y - ball_y[0]) * (m.y - ball_y[0]));
		cosAngle = (m.x - ball_x[0]) / d;
		sinAngle = (m.y - ball_y[0]) / d;
		rodstart_x = ball_x[0] + rodballdistance * cosAngle;
		rodstart_y = ball_y[0] + rodballdistance * sinAngle;
		rodend_x = ball_x[0] + (rodlength + rodballdistance) * cosAngle;
		rodend_y = ball_y[0] + (rodlength + rodballdistance) * sinAngle;
	}
}
