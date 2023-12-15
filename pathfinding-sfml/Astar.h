#pragma once
#include <vector>
#include <stack>

#include "Node.h"
#include "Grid.h"

namespace Astar 
{
	struct PathPosition
	{
		PathPosition(const Vector2i& _position, bool _teleported = false);

		Vector2i position;
		bool teleported;
	};

	std::stack<PathPosition> RetracePath(Node* start_n, Node* end_n);
	std::stack<PathPosition> RetracePath(Grid<Node>& grid, const Vector2i& startPosition, const Vector2i& endPosition);

	Node* FindLowestF(std::vector<Node*>& nodes);

	bool FindAstarPath(Grid<Node>& grid, const Vector2i& startPosition, const Vector2i& endPosition, bool diagonal = true);
}
