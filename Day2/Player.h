#pragma once
class Player
{
public:
	Player();
	~Player();

	const static int LEFT = 75;
	const static int RIGHT = 77;
	const static int UP = 72;
	const static int DOWN = 80;

	int X;
	int Y;

	void Move(int KeyCode);

	void Tick(int KeyCode);

	void Draw();
};