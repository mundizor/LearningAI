#pragma once
#include <list>
#include "Layer.h";

class NeuralNetwork
{
public:
	NeuralNetwork();
	void CreateInputLayer();
	void CreateHiddenLayers();
	void CreateOutputLayer();
	void CreateNodeConnections();

	Layer* GetInputLayer();
	std::list<Layer*> GetHiddenLayers();
	Layer* GetOutputLayer();

	void SetInputData(float inputList[]);
	void SetFitnessValue(float _value);
	bool operator<(const NeuralNetwork& a) const;

	void MakeIntoChild(NeuralNetwork* Parent1, NeuralNetwork* Parent2);
	
	int GetFitnessValue();
	int GetOutput();

private:
	int mHiddenLayersSize;
	int mNrOfHiddenLayers;
	int mOutputLayerSize;
	int mNrOfInputNodes;

	int mFitnessValue;

	void ProcessAllData();
	Layer* mInputLayer;
	std::list<Layer*> mHiddenLayers;
	Layer* mOutputLayer;
};