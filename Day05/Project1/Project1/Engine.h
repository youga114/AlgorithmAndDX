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

	//입력 클래스, 게임 입력 1개, 디자인 패턴, Singleton
	static int CurrentKeyCode;

	const static int LEFT = 75;			//왼쪽 방향키
	const static int RIGHT = 77;		//오른쪽 방향키
	const static int UP = 72;			//위쪽 방향키
	const static int DOWN = 80;			//아래쪽 방향키

protected:
	bool bIsRunning;

	virtual void Input();
	virtual void Tick();
	virtual void Render();

	virtual bool GameLoop();


	std::vector<class Character*> Characters;

	class Map* MapData;
};