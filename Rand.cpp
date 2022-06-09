#include <time.h>
#include <stdlib.h>

extern int Array[30];

void RandomArray(int n)
{
	int rannum1 = 0;
	int rannum2 = 0;
	for (int i = 0; i < n; i++)
	{
		Array[i] = i;
	}
	time_t t = time(NULL);
	srand(t);
	for (int i = 0; i < 100; i++)
	{
		rannum1 = rand() % n;
		rannum2 = rand() % n;

		int temp = Array[rannum1];
		Array[rannum1] = Array[rannum2];
		Array[rannum2] = temp;
	}
}
