#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "PlayerEntity.h"
#include <sstream>
#include <SFML/System.hpp>
#include <fstream>
#include <SFML/System/InputStream.hpp>
#include "LevelHandler.h"
#include "NeuralNetwork.h"
#include "Generation.h"

int main()
{


	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	PlayerEntity* PE = new PlayerEntity(30.f, 40.f);

	LevelHandler* LH = new LevelHandler();

	Generation* generation = new Generation();

	generation->LoadSavedGeneration();

	//initiates the clock
	sf::Clock deltaClock;
	sf::Clock PointTimer;
	float LastFitnessTimer = 0.f;
	int LastUpdatedFitnessValue = 0;
	while (window.isOpen())
	{
		std::list<NeuralNetwork*> NeuralNetworkList = generation->GetNeuralNetworkList();
		std::list<NeuralNetwork*>::iterator NetworkItr = NeuralNetworkList.begin();
		int NItrCounter = 1;
		while (NetworkItr != NeuralNetworkList.end())
		{
			bool shouldStartNewNetwork = false;
			std::cout << "Processing Network: " << NItrCounter << std::endl;
			//cheks if the score has changed for an interval
			int TFitnessValue = (*NetworkItr)->GetFitnessValue();
			int dist = 10;
			if (TFitnessValue < LastUpdatedFitnessValue - dist || TFitnessValue > LastUpdatedFitnessValue + dist)
			{
				LastUpdatedFitnessValue = (*NetworkItr)->GetFitnessValue();
				LastFitnessTimer = PointTimer.restart().asSeconds();
			}
			else
			{ 
				float time = PointTimer.getElapsedTime().asSeconds();
				if (time > 1.f)
				{
					PointTimer.restart();
					shouldStartNewNetwork = true;
				}
			
			}


			sf::Time dt = deltaClock.restart();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();

			float inputArray[4] = { 0.f, 0.f ,0.f ,0.f };
			int itr = 0;
			for (Obstacle* o : LH->GetMapEntitys())
			{
				inputArray[itr] = PE->GetDistanceToShape(o->GetShape()) / 750.f;
				itr++;
			}


			(*NetworkItr)->SetInputData(inputArray);
			int mmOutput = (*NetworkItr)->GetOutput();
			std::cout << "Output: " << mmOutput << std::endl;

			PE->Draw(&window);
			PE->HandleInput(&window, dt, mmOutput);

			LH->DrawCurrentLevel(&window);

			
			if (PE->CheckForCollision(LH->GetMapEntitys()))
			{
				shouldStartNewNetwork = true;
			}

			if (PE->CheckForGoalCollision(LH->GetGoal()))
			{
				shouldStartNewNetwork = true;
			}

			(*NetworkItr)->SetFitnessValue(PE->GetDistanceToShape(LH->GetGoal()->GetShape()));

			if (shouldStartNewNetwork)
			{
				//when the player collides this sets the fitnessvalue and resets the board.
				LH->ResetLevel(PE);
				NetworkItr++;
				NItrCounter++;
			}

			window.display();


		}
		generation->BreedNewGeneration();
	}

	return 0;
}
