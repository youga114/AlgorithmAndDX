#include "MyEngine.h"
#include <stdio.h>
#include "Map.h"
#include "Player.h"
#include "Monster.h"


MyEngine::MyEngine()
{
	//Engine::Init();
	Init();
}


MyEngine::~MyEngine()
{
	Term();
	//Engine::Term();
}

bool MyEngine::Init()
{
	printf("MyEngine Init().\n");
	MapData = new Map();
	Characters.push_back(new Player());
	Characters.push_back(new Monster());

	return true;
}

bool MyEngine::Term()
{
	for (int i = 0; i < Characters.size(); ++i)
	{
		delete Characters[i];
		Characters[i] = nullptr;
	}

	delete MapData;
	MapData = nullptr;

	printf("MyEngine Init().\n");
	return false;
}

bool MyEngine::Run()
{
	Engine::GameLoop();

	return false;
}

void MyEngine::Input()
{
	Engine::Input();
}

void MyEngine::Tick()
{

	Engine::Tick();
}
