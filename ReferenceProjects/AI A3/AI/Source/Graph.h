#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Vector3.h"

struct Node;

struct Edge
{
	Node* origin;
	Node* destination;
	int cost;
};

struct Node
{
	Vector3 pos;
	std::vector<Edge* > Edges;
	int id;
};

struct QueueNode
{
	unsigned node;
	float cost;
};

class Graph
{
public:
	std::vector <Node*> m_nodes;
	std::vector <Edge*> m_edges;

	Graph();
	~Graph();
	void AddNode(Node* _node);
	void AddEdge(Edge* _edge);
	void Generate(unsigned key, unsigned size, float worldWidth, float worldHeight, float nodeScaleSize);
	Node* NearestNode(const Vector3 &pos);
};
#endif