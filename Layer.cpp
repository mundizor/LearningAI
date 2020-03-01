#include "Layer.h"

Layer::Layer()
{
	mLayerNodes = std::list<Node*>();
}

void Layer::AddNode(Node* node)
{
	mLayerNodes.push_back(node);
}

std::list<Node*> Layer::GetNodes()
{
	return mLayerNodes;
}
