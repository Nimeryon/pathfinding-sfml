#pragma once
#include <vector>

#include "Node.h"
#include "Grid.h"
#include "TileGrid.h"

namespace Pathfinding
{
	bool ShouldBeIgnored(int x, int y, bool diagonal);

	std::vector<Node*> GetNodeNeighbours(Grid<Node>& grid, Node* current_node, bool diagonal = true);

	bool CheckPosition(const Grid<Node>& grid, int x, int y);

	Grid<Node> GeneratePathfindingGraph(TileGrid& grid);

	void ResetGraph(Grid<Node>& graph);
}
