#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "PlayerEntity.h";
#include "Goal.h";
#include "Obstacle.h";

class LevelHandler {
private:
	int mCurrentLevel;
	std::list<Obstacle*> mMapEntitys;
	Goal* mGoal;
public:
	LevelHandler();

	void LoadCurrentLevel();
	void ResetLevel(PlayerEntity* player);
	void LoadNextLevel();
	void DrawCurrentLevel(sf::RenderWindow* window);
	Goal* GetGoal();
	std::list<Obstacle*> GetMapEntitys();
};