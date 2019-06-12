#include "Player.h"
#include "Util.h"
#include <stdio.h>

Player::Player()
{
}


Player::~Player()
{
}

void Player::Move(int KeyCode)
{
	switch (KeyCode)
	{
	case Player::RIGHT:
		X++;
		break;
	case Player::LEFT:
		X--;
		break;
	case Player::UP:
		Y--;
		break;
	case Player::DOWN:
		Y++;
		break;
	}

	X = Util::Clamp(X, 1, 8);
	Y = Util::Clamp(Y, 1, 8);
}

void Player::Tick(int KeyCode)
{
	Move(KeyCode);
}

void Player::Draw()
{
	printf("@ ");
}
