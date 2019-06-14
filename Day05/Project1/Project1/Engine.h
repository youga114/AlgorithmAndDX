#pragma once
#include <vector>
#include "Map.h"

class Engine
{
public:
	Engine();
	virtual ~Engine();

	virtual bool Init();
	virtual bool Term();
	virtual bool Run();

	
protected:
	bool bIsRunning;

	virtual void Input();
	virtual void Tick();
	virtual void Render();

	virtual bool GameLoop();

	int CurrentKeyCode;

	std::vector<class Character*> Characters;

	class Map* MapData;
};