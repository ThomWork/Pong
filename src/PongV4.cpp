#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "PuckV4.cpp"
#include "PaddleV4.cpp"
#include "PongV4.h"

Pong::Pong()
{
	this->initialiseVariables();
	this->initialiseWindow();
	this->initialiseObjects();
	this->initialiseText();
}

Pong::~Pong()
{
	delete this->window;
}

const bool Pong::running() const
{
	return this->window->isOpen();
}

void Pong::actions()
{
	this->puck.movement();
	this->userInput();
}

void Pong::update()
{
	this->sleepCheck();
	this->updateCollisions();
	this->checkGoalScored();
	this->checkGameOver();
}

void Pong::render()
{
	/* Renders the game objects
	 * 
	 * clear old frame
	 * render objects
	 * display frame in window
	 */
	
	this->window->clear();
	
	// Draw game objects
	this->window->draw( this->puck.getPuckImage() );
	this->window->draw( this->leftPaddle.getPaddleImage() );
	this->window->draw( this->rightPaddle.getPaddleImage() );
	
	// Draw text
	this->window->draw( this->leftPaddle.getScoreText() );
	this->window->draw( this->rightPaddle.getScoreText() );
	
	if ( game_over )
	{
		this->window->draw( this->winner_text );
		this->window->draw( this->restart_text );
	}
	
	this->window->display();
}

void Pong::initialiseVariables()
{
	this->window = nullptr;
}

void Pong::initialiseWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	
	this->window = new sf::RenderWindow ( this->videoMode, "Pong", sf::Style::Titlebar | sf::Style::Close );
	this->window->setFramerateLimit(60);
}

void Pong::initialiseObjects()
{
	// Puck size and positioning
	int puckSize = 6;
	int puckStartX = ( this->videoMode.width - puckSize ) / 2;
	int puckStartY = ( this->videoMode.height - puckSize ) / 2;
	puck.initialise( puckStartX , puckStartY , puckSize );
	
	// Paddle dimensions
	int paddleWidth = 4;
	int paddleHeight = 80;
	int paddleGap = 6;
	
	// Left paddle positioning
	int leftPaddleStartX = paddleGap;
	int leftPaddleStartY = ( this->videoMode.height - paddleHeight ) / 2;
	leftPaddle.initialise( leftPaddleStartX, leftPaddleStartY, paddleWidth, paddleHeight );
	
	// Right paddle positioning
	int rightPaddleStartX = this->videoMode.width - paddleGap - paddleWidth;
	int rightPaddleStartY = leftPaddleStartY;
	rightPaddle.initialise( rightPaddleStartX, rightPaddleStartY, paddleWidth, paddleHeight );
	
}

void Pong::initialiseText()
{
	// Load font
	
	if ( !font.loadFromFile( "src/DejaVuSans.ttf" ) )
	{
		std::cout << "Error loading font" << std::endl;
	}
	
	sf::Text score_text;
	textFormatting( font, score_text );
	textPositioning( score_text );
}

void Pong::textFormatting( sf::Font& font, sf::Text& score_text )
{
	score_text.setFont( font );
	score_text.setString( "0" );
	score_text.setCharacterSize( 50.f );
	score_text.setFillColor( sf::Color::White );
	score_text.setStyle( sf::Text::Regular);
	
	leftPaddle.textFormatting( font, score_text );
	rightPaddle.textFormatting( font, score_text );
	
	winner_text = score_text;
	restart_text = score_text;
	restart_text.setString( "Press r to restart or Esc to exit" );
}

void Pong::textPositioning( sf::Text& score_text )
{
	float gap = 30.f;
	float centre = ( this->videoMode.width - score_text.getGlobalBounds().width )/2 ;
	
	float left_score_x = centre - gap;
	float left_score_y = gap;
	leftPaddle.textPositioning( left_score_x , left_score_y );
	
	float right_score_x = centre + gap;
	float right_score_y = gap;
	rightPaddle.textPositioning( right_score_x , right_score_y );
	
	winner_text.setPosition( 0 , this->videoMode.height/2 - 50.f);
	restart_text.setPosition( 0 , this->videoMode.height/2 + 50.f );
}

void Pong::userInput()
{
	this->rightPaddle.userMovement();
	this->leftPaddle.userMovement();
	this->pollEvents();
}

void Pong::pollEvents()
{
	// Various controls
	while( this->window->pollEvent( this->ev ) )
	{
		switch ( this->ev.type )
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if ( this->ev.key.code == sf::Keyboard::Escape )
				this->window->close();
			break;
		}
	}
	
}

void Pong::sleepCheck()
{
	// Function to pause game after goal
	if ( time_to_sleep )
	{
		sf::sleep( sf::seconds( 1 ) );
		time_to_sleep = false;
	}
}

void Pong::updateCollisions()
{
	this->puck.updateWindowTopBottomCollision( window );
	
	this->leftPaddle.updateWindowBoundsCollision( window );
	this->rightPaddle.updateWindowBoundsCollision( window );
	
	this->checkPaddlePuckCollision();
}

void Pong::checkPaddlePuckCollision()
{
	// Check which paddle will have a collision based on puck direction
	
	if ( !puck.xIncreasing() )
		paddlePuckCollision( leftPaddle );
	else
		paddlePuckCollision( rightPaddle );
}

void Pong::paddlePuckCollision( Paddle& pad )
{
	// Check for puck-paddle collision
	
	if ( pad.getPaddleImage().getGlobalBounds().intersects( this->puck.getPuckImage().getGlobalBounds() ) )
		this->puck.paddleCollision( pad.getPaddleImage() );
}

void Pong::checkGoalScored()
{
	float goalline_left = 0.f;
	float goalline_right = this->window->getSize().x;
	
	// Somewhat complex goalline check
	if ( puck.getXPos() < goalline_left || puck.getXPos() > goalline_right )
	{
		if ( puck.xIncreasing() )
			leftPaddle.scored();
		else
			rightPaddle.scored();
		
		this->reset();
		time_to_sleep = true;
	}
}

void Pong::reset()
{
	puck.reset();
	leftPaddle.reset();
	rightPaddle.reset();
}

void Pong::checkGameOver()
{
	if ( rightPaddle.getScore() == gamePoint )
	{
		winner_text.setString( "Right player wins!" );
		game_over = true;
		this->render();
	}
	
	if ( leftPaddle.getScore() == gamePoint )
	{
		winner_text.setString( "Left player wins!" );
		game_over = true;
		this->render();
	}
	
	gameOverOptions();
}

void Pong::gameOverOptions()
{
	while ( game_over )
	{
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::R) )
		{
			restartGame();
			game_over = false;
		}
		
		if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
		{
			this->window->close();
			game_over = false;	// Game is obviously over but use this to escape while-loop
		}
	}
}

void Pong::restartGame()
{
	leftPaddle.resetScore();
	rightPaddle.resetScore();
	reset();
}
