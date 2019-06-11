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
			if (PlayerX < 8)
				PlayerX++;
			break;
		case LEFT:
			if (PlayerX > 1)
				PlayerX--;
			break;
		case UP:
			if (PlayerY > 1)
				PlayerY--;
			break;
		case DOWN:
			if (PlayerY < 8)
				PlayerY++;
			break;
		case 'q':
		case 'Q':
			bIsRunning = false;
			break;
	}
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