#pragma once
#include <array>
#include <vector>
#include <stack>

#include "Node.h"
#include "Grid.h"
#include "Pathfinding.h"


namespace Astar 
{
	std::stack<Vector2i> RetracePath(Node* const start_n, Node* const end_n);

	Node* FindLowestF(std::vector<Node*> nodes);

	bool FindAstarPath(Grid<Node>& grid, Node* start_n, Node* end_n, bool diagonal);
}
