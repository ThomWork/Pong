#pragma once

class Game
{

public:
	// Constructor and destructor
	Game();
	virtual ~Game();
	
	// Accessors
	const bool running() const;
	
	// Functions
	void actions();
	void update();
	void render();
	
	
private:
	// Game objects
	Puck puck;
	Paddle leftPaddle;
	Paddle rightPaddle;
	
	// Initialising
	void initialiseVariables();
	void initialiseWindow();
	void initialiseObjects();
	void initialiseText();
	
	// Text
	void textFormatting( sf::Font &font, sf::Text &score_text );
	void textPositioning( sf::Text &score_text );
	
	// 
	void userInput();
	void pollEvents();
	void sleepCheck();
	
	// Collisions
	void updateCollisions();
	void checkPaddlePuckCollision();
	void paddlePuckCollision( Paddle &pad );
	
	// 
	void checkGoal();
	void reset();
	
	// Variables
	bool goalScored = false;
	
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;	// This has default initialisation
	
};
