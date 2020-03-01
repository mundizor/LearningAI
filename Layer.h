#include <list>
#include "Node.h"
#pragma once
class Layer
{
public:
	Layer();

	void AddNode(Node* node);
	std::list<Node*> GetNodes();
private:
	std::list<Node*> mLayerNodes;
	
};