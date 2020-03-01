#include "NodeConnection.h"

NodeConnection::NodeConnection(Node* _endNode, float _weight)
{
	mEndNode = _endNode;
	mWeight = _weight;
}

void NodeConnection::SetEndNode(Node* _endNode)
{
	mEndNode = _endNode;
}

Node* NodeConnection::GetEndNode()
{
	return mEndNode;
}

void NodeConnection::SetWeight(float _weight)
{
	mWeight = _weight;
}

float NodeConnection::GetWeight()
{
	return mWeight;
}
