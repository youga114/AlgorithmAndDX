#pragma once
#include "Character.h"
class Player : public Character
{
public:
	Player();
	virtual ~Player();

	virtual void Tick() override;
	virtual void Render() override;
protected:
	virtual void Move() override;
};

