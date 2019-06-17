#pragma once
#include "Character.h"
#include "Map.h"
class Player : public Character
{
public:
	Player();
	Player(Map* const newMap);
	virtual ~Player();

	virtual void Tick() override;
	virtual void Render() override;
protected:
	virtual void Move() override;
	Map* mapData;
};

