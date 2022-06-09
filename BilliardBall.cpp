#include "DataStructure.h"

extern bBallNode* ballHead;
extern bBallNode* ballTail;

void ResetLocation(int ID, int x, int y)
{
	bBallNode* temp = SearchBall(ID);

	temp->bBall.ballLocation.X = x;
	temp->bBall.ballLocation.Y = y;
}

void ResetVelocity(int ID, int vx, int vy)
{
	bBallNode* temp = SearchBall(ID);

	temp->bBall.ballVelocity.velocity_X = vx;
	temp->bBall.ballVelocity.velocity_Y = vy;
}


bBallNode* SearchBall(int ID)
{
	bBallNode* result = ballHead;

	for (int i = 0; i < ID; i++)
	{
		result = result->next;
	}
	return result;
}
