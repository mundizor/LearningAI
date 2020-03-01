#include "Node.h"

Node::Node()
{
	mBias = 0.f;
	mValue = 0.f;
	mAssignedValue = 0;
}

Node::Node(float _value, float _bias)
{
	mBias = _bias;
	mValue = _value;
}

Node::Node(int _AssignedValue)
{
	mAssignedValue = _AssignedValue;
	mBias = 0.f;
	mValue = 0.f;
}

void Node::SetValue(float _value)
{
	mValue = _value;
}

float Node::GetValue()
{
	return mValue;
}

void Node::SetBias(float _value)
{
	mBias = _value;
}

float Node::GetBias()
{
	return mBias;
}

void Node::AddNodeConnection(NodeConnection* _nodeConnection)
{
	mNodeConnectionsList.push_back(_nodeConnection);
}

std::list<NodeConnection*> Node::GetNodeConnections()
{
	return mNodeConnectionsList;
}

void Node::AddWeightedDataForProcessing(float _value)
{
	mWeightedValues.push_back(_value);
}

void Node::ProcessAddedData()
{
	float totalValue = 0.f;
	for (float weightedValue : mWeightedValues)
	{
		totalValue += weightedValue;
	}
	totalValue += mBias;

	mValue = totalValue;


	//clears the values so they are empty for the next time we process this node.
	mWeightedValues.clear();
}

int Node::GetAssignedValue()
{
	return mAssignedValue;
}
