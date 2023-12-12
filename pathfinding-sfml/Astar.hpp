#pragma once
#include <array>
#include <vector>

#include "Node.hpp"
#include "List.hpp"
#include "Grid.h"
#include "Variables.h"

namespace Astar 
{
	float GetNodeDistance(const Node& start_n, const Node& end_n);

	void ResetNode(Node& n);

	bool ShouldBeIgnored(int x, int y, bool diagonal);

	bool CheckPosition(int x, int y);

	std::vector<Node*> GetNodeNeighbours(const Grid<Node>& grid, Node* current_node, bool diagonal = true);

	Node* FindLowestF(std::vector<Node*> nodes);

	bool FindAstarPath(Node* start_n = nullptr, Node* end_n = nullptr);

}
