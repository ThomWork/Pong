#include "../include/PaddleV4.h"

void Paddle::initialise( int &x, int &y, int &paddleWidth, int &paddleHeight )
{
	// Starting position
	start_x_pos = (float)x;
	start_y_pos = (float)y;
	x_pos = start_x_pos;
	y_pos = start_y_pos;
	
	// Where it is and how it looks
	paddleImage.setPosition( x_pos, y_pos );
	paddleImage.setSize( sf::Vector2f( paddleWidth, paddleHeight ));
	paddleImage.setFillColor( sf::Color::Cyan );
}

void Paddle::textFormatting( sf::Font &_font, sf::Text &score_text )
{
	font = _font;
	score = score_text;
	score.setFont( font );
}

void Paddle::textPositioning( float &score_text_x, float &score_text_y )
{
	points = 0;
	score.setPosition( score_text_x, score_text_y );
}

const sf::Text Paddle::getScoreText() const
{
	return this->score;
}

const sf::RectangleShape Paddle::getPaddleImage() const
{
	return this->paddleImage;
}

void Paddle::userMovement()
{
	horizontalMovement();
	verticalMovement();
}

void Paddle::horizontalMovement()
{
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
	{
		this->paddleImage.move( -this->x_speed, 0.0f );
	}
	else if( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
	{
		this->paddleImage.move( this->x_speed, 0.0f );
	}
}

void Paddle::verticalMovement()
{
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
	{
		y_pos -= y_speed;
		this->paddleImage.setPosition( x_pos, y_pos );
	}
	else if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
	{
		y_pos += y_speed;
		this->paddleImage.setPosition( x_pos, y_pos );
	}
}

void Paddle::updateWindowBoundsCollision( const sf::RenderWindow* window )
{
	sf::FloatRect paddleBounds = this->paddleImage.getGlobalBounds();
	
	// Top and bottom window collision
	topWindowCollision( window , paddleBounds );
	bottomWindowCollision( window , paddleBounds );
}

void Paddle::topWindowCollision( const sf::RenderWindow* window , sf::FloatRect &paddleBounds )
{
	if ( paddleBounds.top <= 0.0f )
	{
		y_pos = 0;
		this->paddleImage.setPosition( paddleBounds.left, y_pos );
	}
}

void Paddle::bottomWindowCollision( const sf::RenderWindow* window , sf::FloatRect &paddleBounds )
{
	if ( paddleBounds.top + paddleBounds.height >= window->getSize().y )
	{
		y_pos = window->getSize().y - paddleBounds.height;
		this->paddleImage.setPosition( paddleBounds.left, y_pos );
	}
}

void Paddle::scored()
{
	points++;
	
	// Update text
	std::stringstream ss;
	ss << points;
	score.setString( ss.str() );
}

int Paddle::getScore()
{
	return points;
}

void Paddle::reset()
{
	x_pos = start_x_pos;
	y_pos = start_y_pos;
	
	paddleImage.setPosition( x_pos, y_pos );
}
