#pragma once
#include <SFML/Graphics.hpp>

class BaseEntity {
protected:
	sf::CircleShape* mShape;
public:
	
	sf::CircleShape* GetShape();
	void SetShape(sf::CircleShape* _shape);
};