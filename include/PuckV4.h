#pragma once

class Puck
{
public:
	void initialise( int x, int y, int size );
	void movement();
	void updateWindowTopBottomCollision( const sf::RenderWindow* window );
	void paddleCollision( const sf::RectangleShape &paddle );
	const sf::RectangleShape getPuckImage() const;
	float getXPos();
	bool xIncreasing();	// Is the puck speed positive or negative
	void reset();

private:
	// Coordinates
	float start_x_pos;
	float start_y_pos;
	float x_pos;
	float y_pos;
	
	// Speed
	float max_speed = 10.0f;
	float start_x_speed = 10.0f;
	float start_y_speed = 0.0f;
	float x_speed;
	float y_speed;
	
	// Image
	sf::RectangleShape puckImage;
	
};
