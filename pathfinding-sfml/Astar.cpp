#include "Astar.h"

float Astar::GetNodeDistance(Node* const start_n, Node* const end_n)
{
	sf::Vector2<int> startPos = { start_n->GetX(), start_n->GetY() };
	sf::Vector2<int> endPos = { end_n->GetX(), end_n->GetY() };
	
	float distance_x = (startPos.x - endPos.x);
	float distance_y = (startPos.y - endPos.y);

	return std::max(abs(distance_x), abs(distance_y)) + std::min(abs(distance_x), abs(distance_y)) * (sqrt(2) - 1);
}

void ResetNode(Node& n)
{
	n.SetG(0);
	n.SetH(0);
	n.parent = nullptr;
}

void Astar::retracePath(Node* const start_n, Node* const end_n)
{
	Node* node = end_n;
	while (*node != *start_n)
	{
		node->path = true;
		node = node->parent;
	}
}

std::vector<Node*> Astar::GetNodeNeighbours(Grid<Node>& grid, Node* current_node, bool diagonal)
{
	std::vector<Node*> neighbour_nodes;

	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (ShouldBeIgnored(i, j, diagonal)) continue;
			int nodeX = current_node->GetX() + i;
			int nodeY = current_node->GetY() + j;
			if (!CheckPosition(grid, nodeX, nodeY)) continue;

			/*neighbour_nodes.emplace_back(grid.GetValue(nodeX, nodeY));*/
		}

	return neighbour_nodes;
}

bool Astar::CheckPosition(Grid<Node>& grid, int x, int y)
{
	if (x > SIZE_X || x<0 || y>SIZE_Y || y < 0) return false;
	return true;
}

bool Astar::ShouldBeIgnored(int x, int y, bool diagonal)
{
	std::vector<Vector2> mask = { {0,0} };

	if (!diagonal) mask = { {0, 0}, {-1,-1}, {-1,1}, {1,1}, {1,-1} };

	for (auto tile : mask)
		if (x == tile.x && y == tile.y) return true;
	return false;
}

Node* Astar::FindLowestF(std::vector<Node*> nodes)
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

bool Astar::FindAstarPath(Grid<Node>& grid, Node* start_n, Node* end_n, bool diagonal = true)
{
	if (!start_n || !end_n)
		return false;

	std::vector<Node*> openNet;
	std::vector<Node*> closedNet;

	Node* current_n = start_n;
	openNet.emplace_back(start_n);

	current_n->SetH(GetNodeDistance(start_n, end_n));


	while (openNet.size() > 0)
	{
		current_n = openNet.front();
		Node* n = FindLowestF(openNet);
		closedNet.emplace_back(n);

		std::vector<Node*> neighbours = GetNodeNeighbours(grid, n, diagonal);

		if (n == end_n)
		{
			retracePath(start_n, end_n);
			return true;
		}
		
		for (auto* node : neighbours)
		{
			if (!node->walkable) continue;

			if (std::find(closedNet.begin(), closedNet.end(), node) != closedNet.end())continue;

			else if (std::find(openNet.begin(), openNet.end(), node) != openNet.end())
			{
				float temp_g = n->GetG() + GetNodeDistance(node, n);


				if (temp_g < node->GetG())
				{
					node->parent = n;
					node->SetG(temp_g);
				}
			}
			else
			{
				node->parent = n;
				node->SetH(GetNodeDistance(node, end_n));

				openNet.emplace_back(node);
			}
		}

	}

	return false;
}
