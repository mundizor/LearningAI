
#ifndef NODE_Included
#define NODE_Included

#pragma once
#include "NodeConnection.h"
#include <list>

class NodeConnection;

class Node
{
public:
	Node();
	Node(float _value, float _bias);
	Node(int _AssignedValue);

	void SetValue(float _value);
	float GetValue();
	void SetBias(float _value);
	float GetBias();
	void AddNodeConnection(NodeConnection* _nodeConnection);
	std::list<NodeConnection*> GetNodeConnections();

	void AddWeightedDataForProcessing(float _value);
	void ProcessAddedData();

	int GetAssignedValue();
private:
	float mValue;
	float mBias;
	int mAssignedValue;
	std::list<float> mWeightedValues;

	std::list<NodeConnection*> mNodeConnectionsList;
};

#endif