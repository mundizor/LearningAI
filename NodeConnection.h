
#ifndef NODECONNECTION_Included
#define NODECONNECTION_Included

#pragma once
#include "Node.h";

class Node;

class NodeConnection
{
public:
	NodeConnection(Node* _endNode, float _weight);
	void SetEndNode(Node* _endNode);
	Node* GetEndNode();
	void SetWeight(float _weight);
	float GetWeight();
private:
	Node* mEndNode;
	float mWeight;
};


#endif