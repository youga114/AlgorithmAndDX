#include "Engine.h"
#include <stdio.h>
#include <conio.h>

Engine::Engine()
{
	Init();
}


Engine::~Engine()
{
	Term();
}

bool Engine::Init()
{
	printf("Engine Init().\n");
	bIsRunning = true;

	return true;
}

bool Engine::Term()
{
	printf("Engine Term().\n");
	return false;
}

bool Engine::Run()
{
	return GameLoop();
}

void Engine::Input()
{
	CurrentKeyCode = getch();
}

void Engine::Tick()
{
	switch (CurrentKeyCode)
	{
		case 'q':
		case 'Q':
			bIsRunning = false;
			break;
	}

	CurrentKeyCode = 0;
}

void Engine::Render()
{
}

bool Engine::GameLoop()
{
	while (bIsRunning)
	{
		Input();
		Tick();
		Render();
	}

	return false;
}