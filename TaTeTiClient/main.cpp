#include "Game.h"

void main()
{
	
	Game demo;
	if (demo.Construct(200, 200, 2, 2))
		demo.Start();
}