#pragma once
#include "Actor.h"

class Map : public Actor
{
public:
	Map();
	~Map();

	void Init(class Player* _player)
	{
		player = _player;
	}

	void Tick(int KeyCode);
	void Draw();

	class Player* player;

	int Data[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,9,1},
	{1,1,1,1,1,1,1,1,1,1}
	};

	virtual void Tick() override;
	virtual void Render() override;
};

