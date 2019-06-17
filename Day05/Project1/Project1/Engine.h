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

	//�Է� Ŭ����, ���� �Է� 1��, ������ ����, Singleton
	static int CurrentKeyCode;

	const static int LEFT = 75;			//���� ����Ű
	const static int RIGHT = 77;		//������ ����Ű
	const static int UP = 72;			//���� ����Ű
	const static int DOWN = 80;			//�Ʒ��� ����Ű

protected:
	bool bIsRunning;

	virtual void Input();
	virtual void Tick();
	virtual void Render();

	virtual bool GameLoop();


	std::vector<class Character*> Characters;

	class Map* MapData;
};