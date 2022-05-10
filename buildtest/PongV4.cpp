#include <iostream>
#include "../src/GameV4.cpp"

// g++ PongV4.cpp -o PongV4.exe -L../libs/SFML -lsfml-graphics -lsfml-window -lsfml-system
// ./PongV4.exe

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
