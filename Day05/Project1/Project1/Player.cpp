#include "Player.h"
#include "Engine.h"
#include "Util.h"

Player::Player()
{
}

Player::Player(Map* newMap)
{
	mapData = newMap;
	Position = mapData->FindPlayerPosition();
}

Player::~Player()
{
}

void Player::Tick()
{
	Move();
}

void Player::Render()
{
	Util::SetXY(Position.X, Position.Y);
	Util::TextColor(RED, BLACK);
	Util::SetObject('@');
}

void Player::Move()
{
	Vector NewPosition = Position;
	switch (Engine::CurrentKeyCode)
	{
		case Engine::RIGHT:
			NewPosition.X++;
			break;
		case Engine::LEFT:
			NewPosition.X--;
			break;
		case Engine::UP:
			NewPosition.Y--;
			break;
		case Engine::DOWN:
			NewPosition.Y++;
			break;
	}

	//�̵� �̸� ����
	if (mapData->Data[NewPosition.Y][NewPosition.X] == 1)
	{
		//�̵� �Ұ�
	}
	else
	{
		//�̵� ����
		Position = NewPosition;
	}

	Position.X = Util::Clamp(Position.X, 1, 8);
	Position.Y = Util::Clamp(Position.Y, 1, 8);

	//Engine::CurrentKeyCode
	//Position
	//Map
}
