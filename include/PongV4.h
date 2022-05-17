#pragma once

class Pong
{

public:
	// Constructor and destructor
	Pong();
	virtual ~Pong();
	
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
	void textFormatting( sf::Font& font, sf::Text& score_text );
	void textPositioning( sf::Text& score_text );
	sf::Font font;
	sf::Text winner_text;
	sf::Text restart_text;
	
	// 
	void userInput();
	void pollEvents();
	void sleepCheck();
	
	// Collisions
	void updateCollisions();
	void checkPaddlePuckCollision();
	void paddlePuckCollision( Paddle& pad );
	
	// Points
	void checkGoalScored();
	bool checkGoalline( float& goalline , float one );
	void reset();
	void checkGameOver();
	void gameOverOptions();
	void restartGame();
	
	// Variables
	bool time_to_sleep = false;
	bool game_over = false;
	
	// Game points
	const int gamePoint = 1;
	
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;	// This has default initialisation
	
};
