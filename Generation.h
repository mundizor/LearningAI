#pragma once
#include <list>
#include "NeuralNetwork.h"
#include <fstream>
#include "tinyxml2.h"
#include "XMLSerialization.h"

class Generation
{
public:
	Generation();

	std::list<NeuralNetwork*> GetNeuralNetworkList();
	void BreedNewGeneration();

	void SaveGenerationDataLocally();
	void LoadSavedGeneration();
	private:
		std::list<NeuralNetwork*> mNeuralNetworkList;
		int NrOfNeuralNetworksInGeneration;
		//List<AIPlayer> mAiPlayerList;
};