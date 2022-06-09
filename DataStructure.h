#pragma once

//GameMode
#define POOL 0
#define SNOOKER 1
#define NINEBALL 2
typedef int Mode;
typedef int BOOL;

enum ballColor
{
	White,
	Yellow,
	Blue,
	Brown,
	Pink,
	Red,
	Purple,
	Orange,
	Green,
	Caramel,
	Black,
	Yellow_White,
	Blue_White,
	Red_White,
	Purple_White,
	Orange_White,
	Green_White,
	Caramel_White
};
typedef enum ballColor ballColor;

struct location
{
	double X;
	double Y;
};
typedef struct location location;

struct velocity
{
	double velocity_X;
	double velocity_Y;
};
typedef struct velocity velocity;

struct billiardBall
{
	int ID;
	ballColor color;
	location ballLocation;
	velocity ballVelocity;
};
typedef struct billiardBall billiardBall;

struct bBallNode
{
	billiardBall bBall;
	struct bBallNode* next;
};
typedef struct bBallNode bBallNode;





/*
	GameMode 0 : Pool
	0---White
	1---Yellow
	2---Blue
	3---Red
	4---Purple
	5---Orange
	6---Green
	7---Caramel
	8---Black
	9---Yellow_White
	10---Blue_White
	11---Red_White
	12---Purple_White
	13---Orange_White
	14---Green_White
	15---Caramel_White


	GameMode 1 : Snooker
	0---White
	1-15 ---Red
	16---Yellow
	17---Green
	18---Brown
	19---Blue
	20---Pink
	21---Black


	GameMode 2 : Nineball
	0---White
	1---Yellow
	2---Blue
	3---Red
	4---Purple
	5---Pink
	6---Green
	7---Caramel
	8---Black
	9---Yellow_White
*/

void ResetLocation(int ID, int x, int y);
void ResetVelocity(int ID, int vx, int vy);
bBallNode* SearchBall(int ID);
