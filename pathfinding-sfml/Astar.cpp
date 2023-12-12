#include "Astar.hpp"

float GetNodeDistance(Node* const start_n, Node* const end_n)
{
	sf::Vector2<unsigned> startPos = { start_n->x, start_n->y };
	sf::Vector2<unsigned> endPos = { end_n->x, end_n->y };
	
	float distance_x = (startPos.x - endPos.x);
	float distance_y = (startPos.y - endPos.y);

	return std::max(abs(distance_x), abs(distance_y)) + std::min(abs(distance_x), abs(distance_y)) * (sqrt(2) - 1);
}

void ResetNode(Node& n)
{
	n.cost_f = 0;
	n.cost_g = 0;
	n.cost_h = 0;
	n.parent = nullptr;
}

void retracePath(Node* const start_n, Node* const end_n)
{
	Node* node = end_n;
	while (*node != *start_n)
	{
		node->path = true;
		node = node->parent;
	}
}

std::vector<Node*> GetNodeNeighbours(Grid<Node>& grid, Node* current_node, bool diagonal)
{
	std::vector<Node*> neighbour_nodes;
	neighbour_nodes.reserve(9);

#pragma region Deprecated
	/*
if (!diagonal) {
	auto n = [&nodes, &neighbour_nodes, &current_node](int x, int y) {
		const int X = current_node->x + x;
		const int Y = current_node->y + y;

		if (X > SIZE_X - 1 || Y > SIZE_Y - 1 || X < 0 || Y < 0)
			return;

		const int index = Y * SIZE_X + X;

		if (index >= nodes.size() || index < 0)
			return;

		auto* node = &nodes[index];

		neighbour_nodes.push_back(node);
	};

	for (int y = -1; y <= 1; y++) {
		if (y == 0)
			continue;
		n(0, y);
	}

	for (int x = -1; x <= 1; x++) {
		if (x == 0)
			continue;
		n(x, 0);
	}

	return neighbour_nodes;
}

for (int y = -1; y <= 1; y++) {
	for (int x = -1; x <= 1; x++) {
		if (x == 0 && y == 0)
			continue;

		const int X = current_node->x + x;
		const int Y = current_node->y + y;

		if (X > SIZE_X - 1 || Y > SIZE_Y - 1 || X < 0 || Y < 0)
			continue;

		const int index = Y * SIZE_X + X;

		if (index >= nodes.size() || index < 0)
			continue;

		auto* node = &nodes[index];

		neighbour_nodes.push_back(node);
	}
}
*/
#pragma endregion

	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (ShouldBeIgnored(i, j, diagonal)) continue;
			unsigned nodeX = current_node->x + i;
			unsigned nodeY = current_node->y + j;
			if (!CheckPosition(nodeX, nodeY)) continue;

			neighbour_nodes.emplace_back(grid.GetValue(nodeX, nodeY));
		}

	return neighbour_nodes;
}

bool CheckPosition(int x, int y)
{
	if (x > SIZE_X || x<0 || y>SIZE_Y || y < 0) return false;
	return true;
}

bool ShouldBeIgnored(int x, int y, bool diagonal)
{
	std::vector<Vector2> mask = { {0,0} };

	if (!diagonal) mask = { {0, 0}, {-1,-1}, {-1,1}, {1,1}, {1,-1} };

	for (auto tile : mask)
		if (x == tile.x && y == tile.y) return true;
	return false;
}

Node* FindLowestF(std::vector<Node*> nodes)
{
	Node* lowest_f = nodes.front();
	int i = 0;
	for (auto n : nodes)
	{
		if (n->cost_f < lowest_f->cost_f)
		{
			lowest_f = n;
			i++;
		}
	}
	nodes.erase(nodes.begin() + i);
	return lowest_f;
}

bool FindAstarPath(Grid<Node>& grid, Node* start_n, Node* end_n, bool diagonal = true)
{
	if (!start_n || !end_n)
		return false;

	std::vector<Node*> openNet;
	std::vector<Node*> closedNet;

	Node* current_n;
	openNet.emplace_back(start_n);

	current_n->cost_h = GetNodeDistance(start_n, end_n);
	current_n->cost_f = current_n->cost_h;

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
				float temp_g = n->cost_g + GetNodeDistance(node, n);


				if (temp_g < node->cost_g)
				{
					node->parent = n;
					node->cost_g = temp_g;
					node->cost_f = node->cost_g + node->cost_h;
				}
			}
			else
			{
				node->parent = n;
				node->cost_h = GetNodeDistance(node, end_n);
				node->cost_f = node->cost_g + node->cost_h;

				openNet.emplace_back(node);
			}
		}
		//Find lowest f cost node n
		//Add n to closedNet and remove from openNEt
		//...
	}

	return false;
}