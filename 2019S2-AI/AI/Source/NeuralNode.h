#pragma once
#include <vector>

struct NeuralNode
{
	std::vector<float> weights;
	float output;
	float z;
	float alpha;
	NeuralNode() {};
	~NeuralNode() {};
};

float operator* (const std::vector<float>& lhs, const std::vector<float>& rhs)
{
	float total = 0.f;

	for (int i = 0; i < lhs.size(); i++)
	{
		total += lhs[i] * rhs[i];
	}
	return total;
}
