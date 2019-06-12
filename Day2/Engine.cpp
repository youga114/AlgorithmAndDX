#include "Engine.h"
#include "Player.h"
#include "Map.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

void Engine::Init(Player * _player, Map * _map)
{
	map = _map;
	map->Init(_player);
}

void Engine::Run()
{
	while (bIsRunning)
	{
		int KeyCode = Input();
		Tick(KeyCode);
		Draw();
	}
}

void Engine::Draw()
{
	system("cls");
	map->Draw();
}

void Engine::Tick(int KeyCode)
{
	switch (KeyCode)
	{
	case 'q':
	case 'Q':
		bIsRunning = false;
		break;
	}
	map->Tick(KeyCode);
}

int Engine::Input()
{
	int KeyCode = _getch();

	return KeyCode;
}
