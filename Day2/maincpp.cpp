#include "Engine.h"
#include "Player.h"
#include "Map.h"
#include "Util.h"

int main()
{
	Engine* engine = new Engine();
	Player* player = new Player();
	Map* map = new Map();
	engine->Init(player, map);
	
	engine->Run();

	delete engine;
	return 0;
}