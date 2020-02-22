#pragma once
#include <vector>
#include "Vector3.h"



struct Node
{
	int nodeID;
	Vector3 pos;
};

struct Edge
{
	Node* from;
	Node* to;
	float cost;
};


class Graph
{
public:
	std::vector<Node*> m_nodes;
	std::vector<Edge*> m_edges;

	Graph();
	~Graph();
	void AddNode(Node* node);
	void AddEdge(Edge* edge);

	void Generate(unsigned key);

};