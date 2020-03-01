#include "PlayerEntity.h"
#include <cmath>
#include <iostream>





PlayerEntity::PlayerEntity(float _mXPos, float _mYPos)
{
	velocity = 1300;
	sf::Vector2f pos = sf::Vector2f(_mXPos, _mYPos);
	mShape = new sf::CircleShape();
	mShape->setPosition(pos);
	mShape->setRadius(25);
	mShape->setFillColor(sf::Color::Green);
}

void PlayerEntity::Draw(sf::RenderWindow* window)
{
	window->draw(*mShape);
}

bool PlayerEntity::CheckForCollision(std::list<Obstacle*> mMapEntitys)
{

	for (Obstacle* obstacle : mMapEntitys)
	{
		//chekcs if collision with map entities
		
		if (CheckForSingleEntityCollision(obstacle->GetShape()))
			return true;
	}

	return false;
}

bool PlayerEntity::CheckForGoalCollision(Goal* goal)
{

	//std::cout << GetDistanceToShape(goal->GetShape()) << std::endl;

	if (CheckForSingleEntityCollision(goal->GetShape()))
		return true;

	return false;
}

bool PlayerEntity::CheckForSingleEntityCollision(sf::CircleShape* _shape)
{
	if (GetDistanceToShape(_shape) < mShape->getRadius() + _shape->getRadius())
		return true;

	return false;
}

float PlayerEntity::GetDistanceToShape(sf::CircleShape* _shape)
{
	float xRealPos = mShape->getPosition().x + (mShape->getRadius());
	float yRealPos = mShape->getPosition().y + (mShape->getRadius());

	float xRealPosMap = _shape->getPosition().x + (_shape->getRadius());
	float yRealPosMap = _shape->getPosition().y + (_shape->getRadius());

	float xdist = powf(xRealPos - xRealPosMap, 2.f);
	float ydist = powf(yRealPos - yRealPosMap, 2.f);

	float totDist = sqrtf(xdist + ydist);

	return totDist;
}

bool PlayerEntity::CheckForEdgeCollision(sf::RenderWindow* window, sf::Vector2f NewPos)
{
	sf::Vector2f WindowSize = window->getView().getSize();
	sf::Vector2u a = window->getSize();
	sf::FloatRect windowBounds({ 0.f, 0.f }, window->getDefaultView().getSize());
	float xLeft = NewPos.x;
	float xRight = NewPos.x + (mShape->getRadius() * 2);
	float yTop = NewPos.y;
	float yBottom = NewPos.y + (mShape->getRadius() * 2);

	if (xLeft < 0)
		return true;

	if (yTop < 0)
		return true;

	if (xRight > WindowSize.x)
		return true;

	if (yBottom > WindowSize.y)
		return true;
		
	return false;
}

void PlayerEntity::HandleInput(sf::RenderWindow* window, sf::Time dt, int NNInput)
{
	sf::Vector2f pos = mShape->getPosition();
	float dtVelocity = velocity * dt.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || NNInput == 1)
	{
		sf::Vector2f tempPos = mShape->getPosition();
		tempPos.x -= dtVelocity;
		if(!CheckForEdgeCollision(window, tempPos))
			pos.x -= dtVelocity;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || NNInput == 2)
	{
		sf::Vector2f tempPos = mShape->getPosition();
		tempPos.x += dtVelocity;
		if (!CheckForEdgeCollision(window, tempPos))
			pos.x += dtVelocity;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || NNInput == 3)
	{
		sf::Vector2f tempPos = mShape->getPosition();
		tempPos.y -= dtVelocity;
		if (!CheckForEdgeCollision(window, tempPos))
			pos.y -= dtVelocity;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || NNInput == 4)
	{
		sf::Vector2f tempPos = mShape->getPosition();
		tempPos.y += dtVelocity;
		if (!CheckForEdgeCollision(window, tempPos))
			pos.y += dtVelocity;
	}

	mShape->setPosition(pos);

}
