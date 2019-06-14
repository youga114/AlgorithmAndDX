#pragma once
#include "Character.h"
class Monster :	public Character
{
public:
	Monster();
	virtual ~Monster();

	virtual void Tick() override;
	virtual void Render() override;
protected:
	virtual void Move() override;
};

