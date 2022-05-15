#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "PuckV4.cpp"
#include "PaddleV4.cpp"
#include "GameV4.h"

Game::Game()
{
	this->initialiseVariables();
	this->initialiseWindow();
	this->initialiseObjects();
	this->initialiseText();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::actions()
{
	this->puck.movement();
	this->userInput();
}

void Game::update()
{
	this->sleepCheck();
	this->updateCollisions();
	this->checkGoal();
	
}

void Game::render()
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
	
	this->window->display();
}

void Game::initialiseVariables()
{
	this->window = nullptr;
}

void Game::initialiseWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	
	this->window = new sf::RenderWindow ( this->videoMode, "Pong", sf::Style::Titlebar | sf::Style::Close );
	this->window->setFramerateLimit(60);
}

void Game::initialiseObjects()
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

void Game::initialiseText()
{
	// Load font
	
	sf::Font font;
	if ( !font.loadFromFile( "src/DejaVuSans.ttf" ) )
	{
		std::cout << "Error loading font" << std::endl;
	}
	
	sf::Text score_text;
	textFormatting( font, score_text );
	textPositioning( score_text );
}

void Game::textFormatting( sf::Font &font, sf::Text &score_text )
{
	score_text.setFont( font );
	score_text.setString( "0" );
	score_text.setCharacterSize( 50.f );
	score_text.setFillColor( sf::Color::White );
	score_text.setStyle( sf::Text::Regular);
	
	leftPaddle.textFormatting( font, score_text );
	rightPaddle.textFormatting( font, score_text );
}

void Game::textPositioning( sf::Text &score_text )
{
	float gap = 20.f;
	float centre = ( this->videoMode.width - score_text.getGlobalBounds().width )/2 ;
	
	float left_score_x = centre - gap;
	float left_score_y = gap;
	leftPaddle.textPositioning( left_score_x , left_score_y );
	
	float right_score_x = centre + gap;
	float right_score_y = gap;
	rightPaddle.textPositioning( right_score_x , right_score_y );
}

void Game::userInput()
{
	this->rightPaddle.userMovement();
	this->leftPaddle.userMovement();
	this->pollEvents();
}

void Game::pollEvents()
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
	
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::R) )
		this->reset();
}

void Game::sleepCheck()
{
	// Function to pause game after goal and puck is reset
	if ( goalScored )
	{
		sf::sleep( sf::seconds( 1 ) );
		goalScored = false;
	}
}

void Game::updateCollisions()
{
	this->puck.updateWindowTopBottomCollision( window );
	
	this->leftPaddle.updateWindowBoundsCollision( window );
	this->rightPaddle.updateWindowBoundsCollision( window );
	
	this->checkPaddlePuckCollision();
}

void Game::checkPaddlePuckCollision()
{
	// Check which paddle will have a collision based on puck direction
	
	if ( !puck.xIncreasing() )
		paddlePuckCollision( leftPaddle );
	else
		paddlePuckCollision( rightPaddle );
}

void Game::paddlePuckCollision( Paddle &pad )
{
	// Check for puck-paddle collision
	
	if ( pad.getPaddleImage().getGlobalBounds().intersects( this->puck.getPuckImage().getGlobalBounds() ) )
		this->puck.paddleCollision( pad.getPaddleImage() );
}

void Game::checkGoal()
{
	float goalline_left = 0.f;
	float goalline_right = this->window->getSize().x;
	
	// Somewhat complex goalline check
	if ( puck.getXPos() < goalline_left || puck.getXPos() > goalline_right )
	{
		if ( !puck.xIncreasing() )
			rightPaddle.scored();
		else
			leftPaddle.scored();
		
		this->reset();
		goalScored = true;
	}
}

void Game::reset()
{
	puck.reset();
	leftPaddle.reset();
	rightPaddle.reset();
}

