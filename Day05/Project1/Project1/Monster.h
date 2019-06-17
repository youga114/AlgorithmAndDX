#pragma once
#include "Character.h"
#include "Map.h"

class Monster :	public Character
{
public:
	Monster();
	Monster(Map* const newMap);

	virtual ~Monster();

	virtual void Tick() override;
	virtual void Render() override;

protected:
	virtual void Move() override;
	Map* mapData;
};
