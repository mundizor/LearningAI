#include "Generation.h"
#include <sstream>

Generation::Generation()
{
	NrOfNeuralNetworksInGeneration = 12; //has to be higher than 3.

	for (int i = 0; i < NrOfNeuralNetworksInGeneration; i++)
	{
		NeuralNetwork* NNetwork = new NeuralNetwork();
		NNetwork->CreateInputLayer();
		NNetwork->CreateHiddenLayers();
		NNetwork->CreateOutputLayer();
		NNetwork->CreateNodeConnections();
		mNeuralNetworkList.push_back(NNetwork);
	}
}

std::list<NeuralNetwork*> Generation::GetNeuralNetworkList()
{
	return mNeuralNetworkList;
}

void Generation::BreedNewGeneration()
{
	int NrOfBottomNetowkrsToMakeIntoChilds = NrOfNeuralNetworksInGeneration / 3;
	int itrCount = 0;
	
	mNeuralNetworkList.sort([](NeuralNetwork * lhs, NeuralNetwork * rhs) {return lhs->GetFitnessValue() < rhs->GetFitnessValue(); });

	std::list<NeuralNetwork*>::iterator NetworkItr = mNeuralNetworkList.begin();

	//list.end() does not poin to an element. decrease by one to get last element.
	std::list<NeuralNetwork*>::iterator NetworkEndItr = mNeuralNetworkList.end();
	NetworkEndItr--;

	//makes the bottom 3rd to childs
	while (itrCount < NrOfBottomNetowkrsToMakeIntoChilds) {
		NeuralNetwork* n1p = (*NetworkEndItr);
		NetworkEndItr--;

		(*NetworkItr)->MakeIntoChild(n1p, (*(NetworkEndItr)));

		NetworkItr++;
		itrCount++;
	}

	//makes the next 3rd into children of the best 3rd aswell.
	itrCount = 0;
	NetworkEndItr = mNeuralNetworkList.end();
	NetworkEndItr--;
	while (itrCount < NrOfBottomNetowkrsToMakeIntoChilds) {
		NeuralNetwork* n1p = (*NetworkEndItr);
		NetworkEndItr--;

		(*NetworkItr)->MakeIntoChild(n1p, (*(NetworkEndItr)));

		NetworkItr++;
		itrCount++;
	}

	//reset all fitnessvalues
	for (NeuralNetwork* NetWork : mNeuralNetworkList)
	{
		NetWork->SetFitnessValue(0.f);
	}

	SaveGenerationDataLocally();
}



void Generation::SaveGenerationDataLocally()
{
	std::ofstream myfile;
	myfile.open("example.txt");
	myfile << "NeuralNetworkPart:" << mNeuralNetworkList.size() << "\n";
	for (NeuralNetwork* neuralNetwork : mNeuralNetworkList)
	{
		myfile << "InputLayerPart\n";
		myfile << "NodePart:" << neuralNetwork->GetInputLayer()->GetNodes().size() << "\n";
		for (Node* node : neuralNetwork->GetInputLayer()->GetNodes())
		{
			myfile << node->GetBias() << "\n";
			myfile << "NodeConnectionPart:" << node->GetNodeConnections().size() << "\n";
			for (NodeConnection* nodeConnection : node->GetNodeConnections())
			{
				myfile << nodeConnection->GetWeight() << "\n";
			}
			myfile << "NodeConnectionPartStop\n";
		}
		myfile << "NodePartStop\n";
		myfile << "InputLayerPartStop\n";
		int layercounter = 1;

		myfile << "HiddenLayerPart:" << neuralNetwork->GetHiddenLayers().size() <<"\n";
		for (Layer* layer : neuralNetwork->GetHiddenLayers())
		{
			
			myfile << "NodePart:" << layer->GetNodes().size() << "\n";
			for (Node* node : layer->GetNodes())
			{
				myfile << node->GetBias() << "\n";
				myfile << "NodeConnectionPart:" << node->GetNodeConnections().size() << "\n";
				for (NodeConnection* nodeConnection : node->GetNodeConnections())
				{
					myfile << nodeConnection->GetWeight() << "\n";
				}
				myfile << "NodeConnectionPartStop\n";
			}
			myfile << "NodePartStop\n";
		}
		myfile << "HiddenLayerPartStop\n";

		myfile << "OutputLayerPart\n";
		myfile << "NodePart:" << neuralNetwork->GetOutputLayer()->GetNodes().size() << "\n";
		for (Node* node : neuralNetwork->GetOutputLayer()->GetNodes())
		{
			myfile << node->GetBias() << "\n";
			
		}
		myfile << "NodePartStop\n";
		myfile << "OutputLayerPartStop\n";
	}
	myfile << "NeuralNetworkPartStop\n";
	myfile.close();
}

void Generation::LoadSavedGeneration()
{
	std::ifstream infile("example.txt");
	std::string line;
	std::list<std::string> stringList;

	std::getline(infile, line);

	std::list<NeuralNetwork*>::iterator NetworkItr = mNeuralNetworkList.begin();
	while (line != "NeuralNetowrkPartStop")
	{
		std::getline(infile, line);
		std::getline(infile, line);
		std::list<Node*>::iterator NodeItr = (*NetworkItr)->GetInputLayer()->GetNodes().begin();
		while (line != "NodePartStop")
		{
			std::getline(infile, line); //gets the node bias
			float bias = std::stof(line);
			(*NodeItr)->SetBias(bias);

			std::getline(infile, line);
			std::list<NodeConnection*>::iterator NodeConnectionItr = (*NodeItr)->GetNodeConnections().begin();
			while (line != "NodeConnectionPartStop")
			{
				std::getline(infile, line); //gets the nodeConenction Weigth
				float weight = std::stof(line);
				(*NodeConnectionItr)->SetWeight(weight);
				NodeConnectionItr++;
			}
			NodeItr++;
		}

		std::getline(infile, line);
		std::getline(infile, line); // HiddenLayerPart:2
		std::list<Layer*>::iterator LayerItr = (*NetworkItr)->GetHiddenLayers().begin();
		while (line != "HiddenLayerPartStop")
		{
			std::getline(infile, line);
			NodeItr = (*LayerItr)->GetNodes().begin();
			while (line != "NodePartStop")
			{
				std::getline(infile, line); //gets the node bias
				float bias = std::stof(line);
				(*NodeItr)->SetBias(bias);

				std::getline(infile, line);
				std::list<NodeConnection*>::iterator NodeConnectionItr = (*NodeItr)->GetNodeConnections().begin();
				while (line != "NodeConnectionPartStop")
				{
					std::getline(infile, line); //gets the nodeConenction Weigth
					float weight = std::stof(line);
					(*NodeConnectionItr)->SetWeight(weight);
					NodeConnectionItr++;
				}
				NodeItr++;
			}
			LayerItr++;
		}

		std::getline(infile, line); // OutputLayerPart
		std::getline(infile, line);

		while (line != "NodePartStop")
		{
			std::getline(infile, line); //gets the node bias
		}

		std::getline(infile, line); //OutputLayerPartStop
		NetworkItr++;
	}
	//std::string delimiter = ":";
	//std::string token = line.substr(0, line.find(delimiter));
	//line.erase(0, token.length() + delimiter.length());
	//int NrOfNodes = std::stoi(line);


}
