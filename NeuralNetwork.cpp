#include "NeuralNetwork.h";

NeuralNetwork::NeuralNetwork()
{
	mHiddenLayers = std::list<Layer*>();
	mHiddenLayersSize = 5;
	mOutputLayerSize = 4;
	mNrOfHiddenLayers = 2;
	mNrOfInputNodes = 4;

	mFitnessValue = 0;

	//creates the hidden layers
	for (int i = 0; i < mNrOfHiddenLayers; i++)
	{
		mHiddenLayers.push_back(new Layer());
	}

	mInputLayer = new Layer();
	mOutputLayer = new Layer();
}

void NeuralNetwork::CreateInputLayer()
{
	for (int i = 0; i < mNrOfInputNodes; i++)
	{
		Node* node = new Node(0.f,0.f);
		mInputLayer->AddNode(node);
	}
	
}

void NeuralNetwork::CreateHiddenLayers()
{
	for (Layer* hiddenLayer : mHiddenLayers)
	{
		for (int i = 0; i < mHiddenLayersSize; i++)
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			hiddenLayer->AddNode(new Node(0.f, r));
		}
	}
}

void NeuralNetwork::CreateOutputLayer()
{
	//oututlayer size is 4. One for each output. Up, Down, Left Right.
	for (int i = 0; i < mOutputLayerSize; i++)
	{
		
		mOutputLayer->AddNode(new Node(i+1));
	}
}

void NeuralNetwork::CreateNodeConnections()
{
	//sets all connections for the input layer.
	for (Node* node : mInputLayer->GetNodes())
	{
		for (Node* EndNode : mHiddenLayers.front()->GetNodes())
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			node->AddNodeConnection(new NodeConnection(EndNode, r));
		}
	}

	//sets all connections for all hidden layers.
	int hiddenLayer = 1;
	std::list<Layer*>::const_iterator it = mHiddenLayers.begin();
	while (it != mHiddenLayers.end())
	{
		for (Node* node : (*it)->GetNodes())
		{
			//if (it == mHiddenLayers.end())
				//break;

			
			std::list<Node*> NextLayerNodes;
			std::list<Layer*>::const_iterator tempitr = it;
			tempitr++;
			if (tempitr != mHiddenLayers.end())
			{
				//if there is a hidden layer after this one. Use the next hidden layer.
				NextLayerNodes = (*tempitr)->GetNodes();
			}
			else
			{
				//if there are no more hidden layers use the output layer.
				NextLayerNodes = mOutputLayer->GetNodes();
			}

			for (Node* EndNode : NextLayerNodes)
			{
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				node->AddNodeConnection(new NodeConnection(EndNode, r));
			}
		}
		++it;
		hiddenLayer++;
	}
}

Layer* NeuralNetwork::GetInputLayer()
{
	return mInputLayer;
}

std::list<Layer*> NeuralNetwork::GetHiddenLayers()
{
	return mHiddenLayers;
}

Layer* NeuralNetwork::GetOutputLayer()
{
	return mOutputLayer;
}

void NeuralNetwork::SetInputData(float inputList[])
{
	int itr = 0;
	for (Node* node : mInputLayer->GetNodes())
	{
		node->SetValue(inputList[itr]);
		itr++;
	}
}

void NeuralNetwork::SetFitnessValue(float _value)
{
	mFitnessValue = 10000 - _value;
}

bool NeuralNetwork::operator<(const NeuralNetwork& a) const
{
	return (mFitnessValue < a.mFitnessValue);
}

void NeuralNetwork::MakeIntoChild(NeuralNetwork* Parent1, NeuralNetwork* Parent2)
{

	//goes through all hidden layers. 1 of 10 transfers will be a random value instead. need some mutation.
	std::list<Layer*>::iterator LayerItrP1 = Parent1->mHiddenLayers.begin();
	std::list<Layer*>::iterator LayerItrP2 = Parent2->mHiddenLayers.begin();
	for (Layer* layer : mHiddenLayers)
	{
		std::list<Node*> P1Nodes = (*LayerItrP1)->GetNodes();
		std::list<Node*> P2Nodes = (*LayerItrP1)->GetNodes();
		std::list<Node*>::iterator NodeItrP1 = P1Nodes.begin();
		std::list<Node*>::iterator NodeItrP2 = P2Nodes.begin();
		for (Node* node : layer->GetNodes())
		{
			std::list<NodeConnection*> P1NC = (*NodeItrP1)->GetNodeConnections();
			std::list<NodeConnection*> P2NC = (*NodeItrP2)->GetNodeConnections();
			std::list<NodeConnection*>::iterator NodeConnectionItrP1 = P1NC.begin();
			std::list<NodeConnection*>::iterator NodeConnectionItrP2 = P2NC.begin();
			for (NodeConnection* nodeConnection : node->GetNodeConnections())
			{
				int Rand = rand() % 101;
				if (Rand <= 55)
					nodeConnection->SetWeight((*NodeConnectionItrP1)->GetWeight());
				else if (Rand <= 90)
					nodeConnection->SetWeight((*NodeConnectionItrP2)->GetWeight());
				else
				{
					float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					nodeConnection->SetWeight(r);
				}


				NodeConnectionItrP1++;
				NodeConnectionItrP2++;
			}


			int Rand = rand() % 101;
			if (Rand <= 55)
				node->SetBias((*NodeItrP1)->GetBias());
			else if (Rand <= 90)
				node->SetBias((*NodeItrP2)->GetBias());
			else
			{
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				node->SetBias(r);
			}

			NodeItrP1++;
			NodeItrP2++;
		}

		LayerItrP1++;
		LayerItrP2++;
	}


	//goes thorugh outputlayer
	std::list<Node*> P1Nodes = Parent1->mOutputLayer->GetNodes();
	std::list<Node*> P2Nodes = Parent2->mOutputLayer->GetNodes();
	std::list<Node*>::iterator NodeItrP1 = P1Nodes.begin();
	std::list<Node*>::iterator NodeItrP2 = P2Nodes.begin();
	for (Node* node : mOutputLayer->GetNodes())
	{

		int Rand = rand() % 11;
		if (Rand <= 4)
			node->SetBias((*NodeItrP1)->GetBias());
		else if (Rand <= 9)
			node->SetBias((*NodeItrP2)->GetBias());
		else
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			node->SetBias(r);
		}


		NodeItrP1++;
		NodeItrP2++;
	}
}

int NeuralNetwork::GetFitnessValue()
{
	return mFitnessValue;
}

int NeuralNetwork::GetOutput()
{
	ProcessAllData();

	float highestValue = -1.f;
	int output = -1;
	for (Node* node : mOutputLayer->GetNodes())
	{

		if (node->GetValue() > highestValue)
		{
			highestValue = node->GetValue();
			output = node->GetAssignedValue();
		}
	}
	return output; // returns a number from 1-max number of nodes in output layer. 
}

void NeuralNetwork::ProcessAllData()
{
	for (Node* node : mInputLayer->GetNodes())
	{
		for (NodeConnection* nodeConnection :node->GetNodeConnections())
		{
			nodeConnection->GetEndNode()->AddWeightedDataForProcessing(node->GetValue() * nodeConnection->GetWeight());
		}
	}

	for (Layer* layer : mHiddenLayers)
	{
		for (Node* node : layer->GetNodes())
		{
			node->ProcessAddedData();
			for (NodeConnection* nodeConnection : node->GetNodeConnections())
			{
				nodeConnection->GetEndNode()->AddWeightedDataForProcessing(node->GetValue() * nodeConnection->GetWeight());
			}
		}
	}

	//processes the data for the output layer.
	for (Node* node : mOutputLayer->GetNodes())
	{
		node->ProcessAddedData();
	}

}
