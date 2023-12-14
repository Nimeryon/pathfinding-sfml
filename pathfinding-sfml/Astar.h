#pragma once
#include <vector>
#include <stack>

#include "Node.h"
#include "Grid.h"

namespace Astar 
{
	std::stack<Vector2i> RetracePath(Node* start_n, Node* end_n);

	Node* FindLowestF(std::vector<Node*>& nodes);

	bool FindAstarPath(Grid<Node>& grid, Node* start_n, Node* end_n, bool diagonal);
}
