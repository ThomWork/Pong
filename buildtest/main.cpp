#include <iostream>
#include "PongV4.cpp"

// g++ main.cpp -o main.exe -L../libs/SFML -lsfml-graphics -lsfml-window -lsfml-system
// ./main.exe

int main()
{
	// Init game engine
	Game game;
	
	// This is the game loop
	while ( game.running() )
	{		
		// Actions in game
		game.actions();
		
		// Update the game
		game.update();
		
		// Render the objects
		game.render();
	}
	
	return 0;
}
