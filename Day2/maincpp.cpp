#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define LEFT	75
#define RIGHT	77
#define UP		72
#define DOWN	80

bool bIsRunning = true;

int PlayerX = 1;
int PlayerY = 1;

int Clamp(int Current, int Min, int Max);

int map[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

int Input()
{
	int KeyCode = _getch();

	return KeyCode;
}

void Tick(int KeyCode)
{

	switch (KeyCode)
	{
		case RIGHT:
			PlayerX++;
			break;
		case LEFT:
			PlayerX--;
			break;
		case UP:
			PlayerY--;
			break;
		case DOWN:
			PlayerY++;
			break;
		case 'q':
		case 'Q':
			bIsRunning = false;
			break;
	}

	PlayerX = Clamp(PlayerX, 1, 8);
	PlayerY = Clamp(PlayerY, 1, 8);
}

void Draw()
{
	system("cls");
	for (int Y = 0; Y < 10; ++Y) 
	{
		for (int X = 0; X < 10; ++X)
		{
			if (X == PlayerX && Y == PlayerY)
			{
				printf("@ ");
			}
			else
			{
				printf("%d ", map[Y][X]);
			}
		}
		printf("\n");
	}
}

int Clamp(int Current, int Min, int Max)
{
	if (Current < Min)
	{
		return Min;
	}

	if (Current > Max)
	{
		return Max;
	}

	return Current;
}

int main(int)
{
	while (bIsRunning)
	{
		int KeyCode = Input();
		Tick(KeyCode);
		Draw();
	}

	return 0;
}