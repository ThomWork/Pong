#include "../include/PuckV4.h"

void Puck::initialise( int x, int y, int size )
{
	float puck_size = (float)size;
	
	// Starting position
	start_x_pos = (float)x;
	start_y_pos = (float)y;
	x_pos = start_x_pos;
	y_pos = start_y_pos;
	
	// Where it is and how it looks
	puckImage.setPosition( x_pos, y_pos );
	puckImage.setSize( sf::Vector2f( puck_size, puck_size ));
	puckImage.setFillColor( sf::Color::Cyan );
	
	// Giving it a speed
	x_speed = start_x_speed;
	y_speed = start_y_speed;
}

void Puck::movement()
{
	x_pos += x_speed;
	y_pos += y_speed;
	puckImage.setPosition( x_pos, y_pos );
}

void Puck::updateWindowTopBottomCollision( const sf::RenderWindow* window )
{
	sf::FloatRect puckBounds = this->puckImage.getGlobalBounds();
	
	// Top and bottom window collision
	if ( puckBounds.top <= 0.0f || puckBounds.top + puckBounds.height >= window->getSize().y )
	{
		y_speed *= -1;
		y_pos += y_speed; // This is to prevent puck from getting stuck in window
	}
}

void Puck::paddleCollision( const sf::RectangleShape &paddle )
{
	sf::FloatRect paddleBounds = paddle.getGlobalBounds();
	float midPaddle = paddleBounds.top + paddleBounds.height/2.0;
	
	sf::FloatRect puckBounds = this->puckImage.getGlobalBounds();
	float midPuck = puckBounds.top + puckBounds.height/2.0;
	
	// This is a ratio to determine how the ball will bounce off paddle
	float ratio = ( midPuck - midPaddle ) / ( paddleBounds.height);
	
	y_speed = max_speed * ratio;
	x_speed *= -1;
	
}

const sf::RectangleShape Puck::getPuckImage() const
{
	return this->puckImage;
}

float Puck::getXPos()
{
	return x_pos;
}

bool Puck::xIncreasing()
{
	if ( x_speed > 0 )
		return true;
	else
		return false;
}

void Puck::reset()
{
	x_pos = start_x_pos;
	y_pos = start_y_pos;
	
	puckImage.setPosition( x_pos, y_pos );
	
	y_speed = start_y_speed;
}
