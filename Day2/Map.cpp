#include "Map.h"
#include "Player.h"
#include <stdio.h>

Map::Map()
{
}


Map::~Map()
{
}

void Map::Tick(int KeyCode)
{
	player->Tick(KeyCode);
}

void Map::Draw()
{
	for (int Y = 0; Y < 10; ++Y)
	{
		for (int X = 0; X < 10; ++X)
		{
			if (X == player->X && Y == player->Y)
			{
				player->Draw();
			}
			else
			{
				printf("%d ", Data[Y][X]);
			}
		}
		printf("\n");
	}
}
