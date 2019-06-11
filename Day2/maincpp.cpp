#include "Engine.h"
#include "Player.h"
#include "Map.h"
#include "Util.h"

#define LEFT	75
#define RIGHT	77
#define UP		72
#define DOWN	80

int main()
{
	Engine* engine = new Engine();
	engine->Run();

	delete engine;
	return 0;
}