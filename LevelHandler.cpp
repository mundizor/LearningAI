#include "LevelHandler.h"

LevelHandler::LevelHandler()
{
	mCurrentLevel = 1;

	//creates a temporary first level
	Obstacle* obstacle = new Obstacle();
	sf::CircleShape* shape = new sf::CircleShape(200.f);
	shape->setPosition(412.f, 0.f);
	obstacle->SetShape(shape);
	mMapEntitys.push_back(obstacle);

	Obstacle* obstacle2 = new Obstacle();
	shape = new sf::CircleShape(200.f);
	shape->setPosition(512.f, 400.f);
	obstacle2->SetShape(shape);
	mMapEntitys.push_back(obstacle2);

	Obstacle* obstacle3 = new Obstacle();
	shape = new sf::CircleShape(200.f);
	shape->setPosition(-200.f, 780.f);
	obstacle3->SetShape(shape);
	mMapEntitys.push_back(obstacle3);

	Obstacle* obstacle4 = new Obstacle();
	shape = new sf::CircleShape(200.f);
	shape->setPosition(1000.f,400.f);
	obstacle4->SetShape(shape);
	mMapEntitys.push_back(obstacle4);

	mGoal = new Goal(1650, 900);
	mGoal->GetShape()->setFillColor(sf::Color::Red);
}

void LevelHandler::LoadCurrentLevel()
{

}

void LevelHandler::ResetLevel(PlayerEntity* player)
{
	sf::Vector2f pos = sf::Vector2f(30.f,40.f);
	player->GetShape()->setPosition(pos);
}

void LevelHandler::LoadNextLevel()
{
}

void LevelHandler::DrawCurrentLevel(sf::RenderWindow* window)
{
	for ( Obstacle* obstacle : mMapEntitys)
	{
		window->draw(*(obstacle->GetShape()));
	}

	window->draw(*(mGoal->GetShape()));
}

Goal* LevelHandler::GetGoal()
{
	return mGoal;
}

std::list<Obstacle*> LevelHandler::GetMapEntitys()
{
	return mMapEntitys;
}
