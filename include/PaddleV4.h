#pragma once

#include <sstream>

class Paddle
{
public:
	// Initialising
	void initialise( int& x, int& y, int& paddleWidth, int& paddleHeight );
	// Text
	void textFormatting( sf::Font& _font, sf::Text& score_text );
	void textPositioning( float& score_text_x, float& score_text_y );
	const sf::Text getScoreText() const;
	// 
	const sf::RectangleShape getPaddleImage() const;
	void userMovement();
	void updateWindowBoundsCollision( const sf::RenderWindow* window );
	//
	void scored();
	int getScore();
	void reset();
	void resetScore();
	
	
private:
	// Coordinates
	float start_x_pos;
	float start_y_pos;
	float x_pos;
	float y_pos;
	
	// Speed
	float x_speed = 0.0f;
	float y_speed = 5.0f;
	
	// Score
	int points;
	sf::Font font;
	sf::Text score;
	
	// Image
	sf::RectangleShape paddleImage;
	
	// Movement
	void horizontalMovement();
	void verticalMovement();
	
	// Window collision
	void topWindowCollision( const sf::RenderWindow* window , sf::FloatRect& paddleBounds );
	void bottomWindowCollision( const sf::RenderWindow* window , sf::FloatRect& paddleBounds );
};
