#include "Goal.h";

Goal::Goal(float _mXPos, float _mYPos)
{
	sf::Vector2f pos = sf::Vector2f(_mXPos, _mYPos);
	mShape = new sf::CircleShape();
	mShape->setPosition(pos);
	mShape->setRadius(25);
	mShape->setFillColor(sf::Color::Green);
}
