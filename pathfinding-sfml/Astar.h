#pragma once
#include <array>
#include <vector>

#include "Node.h"
#include "List.h"
#include "Grid.h"
#include "Variables.h"

namespace Astar 
{
	void ResetNode(Node& n);

	bool ShouldBeIgnored(int x, int y, bool diagonal);

	float GetNodeDistance(Node* const start_n, Node* const end_n);

	void retracePath(Node* const start_n, Node* const end_n);

	std::vector<Node*> GetNodeNeighbours(Grid<Node>& grid, Node* current_node, bool diagonal = true);

	bool CheckPosition(Grid<Node>& grid, int x, int y);

	Node* FindLowestF(std::vector<Node*> nodes);

	bool FindAstarPath(Grid<Node>& grid, Node* start_n, Node* end_n, bool diagonal);

}
