#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "BaseEntity.h";
#include "Obstacle.h";
#include "Goal.h";

class PlayerEntity : public BaseEntity{
private:

	int velocity;

	bool CheckForSingleEntityCollision(sf::CircleShape* _shape);

	
	
public:
	PlayerEntity(float _mXPos, float _mYPos);

	void Draw(sf::RenderWindow* window);

	bool CheckForEdgeCollision(sf::RenderWindow* window, sf::Vector2f NewPos);

	void HandleInput(sf::RenderWindow* window, sf::Time dt, int NNInput);

	bool CheckForCollision(std::list<Obstacle*> mMapEntitys);

	bool CheckForGoalCollision(Goal* goal);

	float GetDistanceToShape(sf::CircleShape* _shape);
};