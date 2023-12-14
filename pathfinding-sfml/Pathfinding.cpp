#include "Pathfinding.h"

bool Pathfinding::ShouldBeIgnored(int x, int y, bool diagonal)
{
	std::vector<Vector2> mask = { {0,0} };

	if (!diagonal) mask = { {0, 0}, {-1,-1}, {-1,1}, {1,1}, {1,-1} };

	for (auto tile : mask)
		if (x == tile.x && y == tile.y) return true;
	return false;
}

std::vector<Node*> Pathfinding::GetNodeNeighbours(Grid<Node>& grid, Node* current_node, bool diagonal)
{
	std::vector<Node*> neighbour_nodes;
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (ShouldBeIgnored(i, j, diagonal)) continue;
			int nodeX = current_node->GetTileX() + i;
			int nodeY = current_node->GetTileY() + j;  
			if (!CheckPosition(grid, nodeX, nodeY)) continue;

			neighbour_nodes.emplace_back(&grid.GetValue(nodeX, nodeY)); 
		}

	return neighbour_nodes;
}

bool Pathfinding::CheckPosition(const Grid<Node>& grid, int x, int y)
{
	if (x >= grid.GetWidth() || x < 0 || y >= grid.GetHeight() || y < 0) return false;
	return true;
}

Grid<Node> Pathfinding::GeneratePathfindingGraph(TileGrid& grid)
{
	Grid<Node> nodes(grid.GetWidth(), grid.GetHeight());
	for (int y = 0; y < grid.GetHeight(); ++y)
		for (int x = 0; x < grid.GetWidth(); ++x)
		{
			Tile* tile = &grid.GetValue(x,y);

			if (grid.GetValue(x, y).GetTileType() == TileType::PORTAL)
				nodes.GetValue(x, y).SetTile(&grid.GetValue(tile->GetLinkPosition()));
			else nodes.GetValue(x, y).SetTile(&grid.GetValue(x, y));
			nodes.GetValue(x, y).SetPosition(x, y);
		}

	return nodes;
}

void Pathfinding::ResetGraph(Grid<Node>& graph)
{
	for (int y = 0; y < graph.GetHeight(); ++y)
		for (int x = 0; x < graph.GetWidth(); ++x)
			graph.GetValue(x, y).ResetNode();
}
