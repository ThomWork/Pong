#include <iostream>
#include "PongV4.cpp"

// g++ main.cpp -o main.exe -L../libs/SFML -lsfml-graphics -lsfml-window -lsfml-system
// ./main.exe

int main()
{
	// Init game engine
	Pong pong;
	
	// This is the game loop
	while ( pong.running() )
	{		
		// Actions in game events
		pong.actions();
		
		// Update the game
		pong.update();
		
		// Render/draw the objects
		pong.render();
	}
	
	return 0;
}
