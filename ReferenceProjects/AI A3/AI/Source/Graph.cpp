#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::AddNode(Node* _node)
{
	_node->id = m_nodes.size();
	m_nodes.push_back(_node);
}

void Graph::AddEdge(Edge* _edge)
{
	_edge->cost = abs((_edge->destination->pos - _edge->origin->pos).Length());
	m_edges.push_back(_edge);
}

void Graph::Generate(unsigned key, unsigned size, float worldWidth, float worldHeight, float nodeScaleSize)
{
	//generate nodes
	for (int i = 0; i < size; ++i)
	{
		//Generate a node in a random location in the map
		float randXPos, randYPos;
		while (true)
		{
			randXPos = Math::RandFloatMinMax(nodeScaleSize, worldWidth - nodeScaleSize);
			randYPos = Math::RandFloatMinMax(nodeScaleSize, worldHeight - nodeScaleSize);

			bool isOverlap = false;
			for (int j = 0; j < m_nodes.size(); ++j)
			{
				if ((m_nodes[j]->pos - Vector3(randXPos, randYPos, 0)).Length() < nodeScaleSize * 4)
				{
					isOverlap = true;
					break;
				}					
			}

			if (!isOverlap)
				break;
		}

		Node* newNode = new Node();
		newNode->pos.Set(randXPos, randYPos, 0);
		newNode->id = i;
		m_nodes.push_back(newNode);
	}

	//Link the nodes
	for (int i = 0; i < m_nodes.size(); ++i)
	{
		Node* currNode = m_nodes[i];
		
		for (int j = 0; j < m_nodes.size(); ++j)
		{
			if (j == m_nodes.size() - 1 && currNode->Edges.size() == 0)
			{
				Edge* newEdge = new Edge();
				newEdge->origin = currNode;

				if (currNode == m_nodes[j])
					newEdge->destination = m_nodes[j - 1];
				else
					newEdge->destination = m_nodes[j];

				currNode->Edges.push_back(newEdge);
				newEdge->destination->Edges.push_back(newEdge);
				AddEdge(newEdge);
			}
			else
			{
				if (Math::RandIntMinMax(1, 4) == 1 && currNode != m_nodes[j])
				{
					Edge* newEdge = new Edge();
					newEdge->origin = currNode;
					newEdge->destination = m_nodes[j];

					currNode->Edges.push_back(newEdge);
					newEdge->destination->Edges.push_back(newEdge);
					AddEdge(newEdge);
				}
			}
		}
	}
}

Node* Graph::NearestNode(const Vector3 &pos)
{
	Node* targetNode = NULL;
	float lowestDist = FLT_MAX;

	for (int i = 0; i < m_nodes.size(); ++i)
	{
		float dist = (m_nodes[i]->pos - pos).Length();
		if (dist < lowestDist)
		{
			lowestDist = dist;
			targetNode = m_nodes[i];
		}
	}

	return targetNode;
}