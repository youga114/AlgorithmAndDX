#pragma once

class Engine
{
public:
	void Init(class Player* _player, class Map* _map);
	void Run();
	void Draw();
	void Tick(int KeyCode);
	int Input();

	bool bIsRunning = true;
	class Map* map;
};