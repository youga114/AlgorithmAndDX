#include <stdio.h>
#include "Engine.h"
#include "MyEngine.h"

int main()
{
	Engine* engine = new MyEngine();

	engine->Run();

	delete engine;
	engine = nullptr;

	return 0;
}