#include "Astar.h"
#include "Pathfinding.h"

Astar::PathPosition::PathPosition(const Vector2i& _position, bool _teleported) :
	position(_position),
	teleported(_teleported)
{}

std::stack<Astar::PathPosition> Astar::RetracePath(Node* start_n, Node* end_n)
{
	std::stack<PathPosition> path;
	Node* node = end_n;

	path.push(end_n->GetPosition());
	while (*node != *start_n)
	{
		node->m_path = true;
		node = node->m_parent;
		if (node->GetType() == TileType::PORTAL)
			path.push({ node->GetTile()->GetGridPosition(), true });
		path.push(node->GetPosition());
	}

	return path;
}

std::stack<Astar::PathPosition> Astar::RetracePath(Grid<Node>& grid, const Vector2i& startPosition, const Vector2i& endPosition)
{
	return RetracePath(&grid.GetValue(startPosition), &grid.GetValue(endPosition));
}

Node* Astar::FindLowestF(std::vector<Node*>& nodes)
{
	Node* lowest_f = nodes.front();
	int i = 0;
	for (auto n : nodes)
	{
		if (n->GetF() < lowest_f->GetF())
		{
			lowest_f = n;
			i++;
		}
	}

	nodes.erase(nodes.begin() + i);
	return lowest_f;
}

bool Astar::FindAstarPath(Grid<Node>& grid, const Vector2i& startPosition, const Vector2i& endPosition, bool diagonal)
{
	Node* start_n = &grid.GetValue(startPosition);
	Node* end_n = &grid.GetValue(endPosition);
	if (!start_n || !end_n)
		return false;

	std::vector<Node*> openNet;
	std::vector<Node*> closedNet;

	Node* current_n = start_n;
	openNet.emplace_back(start_n);

	current_n->SetH(start_n->GetNodeDistance(end_n));

	while (openNet.size() > 0)
	{
		Node* n = FindLowestF(openNet);
		closedNet.emplace_back(n);

		std::vector<Node*> neighbours = Pathfinding::GetNodeNeighbours(grid, n, diagonal);

		if (n == end_n) return true;
		
		for (auto* node : neighbours)
		{
			if (!node->IsWalkable()) continue;

			if (std::find(closedNet.begin(), closedNet.end(), node) != closedNet.end())
				continue;

			if (std::find(openNet.begin(), openNet.end(), node) != openNet.end())
			{
				float temp_g = n->GetG() + node->GetNodeDistance(n);

				if (temp_g < node->GetG())
				{
					node->SetParent(n);
					node->SetG(temp_g);
				}
			}
			else
			{
				node->SetParent(n);
				node->SetH(node->GetNodeDistance(end_n));

				openNet.emplace_back(node);
			}
		}

	}

	return false;
}