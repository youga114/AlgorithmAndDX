#pragma once

class Engine
{
public:
	void Run();
	void Draw();
	void Tick(int KeyCode);
	int Input();

	bool bIsRunning = true;
};