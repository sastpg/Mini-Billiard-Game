#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>

#include "Load_Save.h"
#include "DataStructure.h"
#include "CONST.h"
#include "Display.h"

extern Mode Gamemode;
extern FILEMODE Filemode;
extern bool isDisplayLine;
extern int gameTime;
extern int turn;
extern int score[2];
extern bBallNode* ballHead;
extern bBallNode* ballTail;

void SaveFile(FILEMODE mode)
{
	if (mode == 0) //bin
	{
		FILE* fpSaveBin;
		int data[51] = { 0,Gamemode,gameTime,turn ,score[A],score[B] };
		int count = 6;

		fpSaveBin = fopen("Source/Save.bsave", "wb");
		for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
		{
			data[count++] = temp->bBall.ballLocation.X;
			data[count++] = temp->bBall.ballLocation.Y;
		}
		data[0] = count;
		fwrite(data, sizeof(int), count, fpSaveBin);
		fclose(fpSaveBin);
	}
	else {
		FILE* fpSaveTxt;

		fpSaveTxt = fopen("Source/Save.tsave", "w");
		fprintf(fpSaveTxt, "%d %d %d %d %d\n", Gamemode, gameTime, turn, score[A], score[B]);
		for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
		{
			fprintf(fpSaveTxt, "%d %d\n", (int)(temp->bBall.ballLocation.X), (int)(temp->bBall.ballLocation.Y));
		}
		fclose(fpSaveTxt);
	}
}

int LoadFile(FILEMODE mode)
{
	int ballNUM[3] = { 16,22,10 };

	if (mode == 0) //bin
	{
		FILE* fpLoadBin;
		static int data[52];
		int count = 0;

		fpLoadBin = fopen("Source/Save.bsave", "rb");
		if (fpLoadBin == NULL)
		{
			return 0;
		}
		fread(data, sizeof(int), 1, fpLoadBin);
		count = data[0];
		fread(data + 1, sizeof(int), count, fpLoadBin);
		fclose(fpLoadBin);
		Gamemode = data[1];
		gameTime = data[2];
		turn = data[3];
		score[A] = data[4];
		score[B] = data[5];
		UpdateSettingFromGame();
		if (Gamemode == POOL || Gamemode == NINEBALL)
		{
			initgraph(1080, 580);
		}
		else if (Gamemode == SNOOKER)
		{
			initgraph(1480, 780);
		}
		DisplayBoard();
		for (int i = 0; i < ballNUM[Gamemode]; i++)
		{
			bBallNode* temp = (bBallNode*)malloc(sizeof(bBallNode));

			temp->bBall.ID = i;
			temp->bBall.ballVelocity.velocity_X = 0;
			temp->bBall.ballVelocity.velocity_Y = 0;
			temp->bBall.ballLocation.X = data[6 + 2 * i];
			temp->bBall.ballLocation.Y = data[7 + 2 * i];
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

		return 1;
	}
	else {
		FILE* fpLoadTxt;

		fpLoadTxt = fopen("Source/Save.tsave", "r");
		if (fpLoadTxt == NULL)
		{
			return 0;
		}
		fscanf(fpLoadTxt, "%d %d %d %d %d", &Gamemode, &gameTime, &turn, &score[A], &score[B]);
		if (Gamemode == POOL || Gamemode == NINEBALL)
		{
			initgraph(1080, 580);
		}
		else if (Gamemode == SNOOKER)
		{
			initgraph(1480, 780);
		}
		DisplayBoard();
		for (int i = 0; i < ballNUM[Gamemode]; i++)
		{
			bBallNode* temp = (bBallNode*)malloc(sizeof(bBallNode));

			fscanf(fpLoadTxt, "%lf %lf", &(temp->bBall.ballLocation.X), &(temp->bBall.ballLocation.Y));
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
		fclose(fpLoadTxt);

		return 1;
	}
}

void UpdateColor(Mode Gamemode)
{
	for (bBallNode* temp = ballHead; temp != NULL; temp = temp->next)
	{
		switch (Gamemode)
		{
		case POOL:
			switch (temp->bBall.ID)
			{
			case 0:
				temp->bBall.color = White;
				break;
			case 1:
				temp->bBall.color = Yellow;
				break;
			case 2:
				temp->bBall.color = Blue;
				break;
			case 3:
				temp->bBall.color = Red;
				break;
			case 4:
				temp->bBall.color = Purple;
				break;
			case 5:
				temp->bBall.color = Orange;
				break;
			case 6:
				temp->bBall.color = Green;
				break;
			case 7:
				temp->bBall.color = Caramel;
				break;
			case 8:
				temp->bBall.color = Black;
				break;
			case 9:
				temp->bBall.color = Yellow_White;
				break;
			case 10:
				temp->bBall.color = Blue_White;
				break;
			case 11:
				temp->bBall.color = Red_White;
				break;
			case 12:
				temp->bBall.color = Purple_White;
				break;
			case 13:
				temp->bBall.color = Orange_White;
				break;
			case 14:
				temp->bBall.color = Green_White;
				break;
			case 15:
				temp->bBall.color = Caramel_White;
				break;
			}
			break;
		case SNOOKER:
			switch (temp->bBall.ID)
			{
			case 0: //WHITE
				temp->bBall.color = White;
				break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
				temp->bBall.color = Red;
				break;
			case 15:
				temp->bBall.color = Red;
				break;
			case 16:  //YELLOW
				temp->bBall.color = Yellow;
				break;
			case 17:  //GREEN
				temp->bBall.color = Green;
				break;
			case 18:  //BROWN
				temp->bBall.color = Brown;
				break;
			case 19:  //BLUE
				temp->bBall.color = Blue;
				break;
			case 20:  //PINK
				temp->bBall.color = Pink;
				break;
			case 21:  //BLACK
				temp->bBall.color = Black;
				break;
			}
			break;
		case NINEBALL:
			switch (temp->bBall.ID)
			{
			case 0:
				temp->bBall.color = White;
				break;
			case 1:
				temp->bBall.color = Yellow;
				break;
			case 2:
				temp->bBall.color = Blue;
				break;
			case 3:
				temp->bBall.color = Red;
				break;
			case 4:
				temp->bBall.color = Purple;
				break;
			case 5:
				temp->bBall.color = Pink;
				break;
			case 6:
				temp->bBall.color = Green;
				break;
			case 7:
				temp->bBall.color = Caramel;
				break;
			case 8:
				temp->bBall.color = Black;
				break;
			case 9:
				temp->bBall.color = Yellow_White;
				break;
			}
			break;
		}
	}
}

int ClearFile(FILEMODE mode)
{
	return mode == 0 ? remove("Source/Save.bsave") : remove("Source/Save.tsave");
}

void UpdateSettingFromFile()
{
	FILE* fpSetting;
	char b, c;

	if (fpSetting = fopen("Source/setting.set", "r"))
	{
		fscanf(fpSetting, "%c%c", &b, &c);
		Filemode = b - 48;
		isDisplayLine = c - 48;
		fclose(fpSetting);
	}
	else {
		fpSetting = fopen("Source/setting.set", "w");
		fprintf(fpSetting, "00");
		fclose(fpSetting);
	}
}
void UpdateSettingFromGame()
{
	FILE* fpSetting;

	fpSetting = fopen("Source/setting.set", "w");
	fprintf(fpSetting, "%d%d", Filemode, isDisplayLine);
	fclose(fpSetting);
}
