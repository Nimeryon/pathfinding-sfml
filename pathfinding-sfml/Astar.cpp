#include "Astar.hpp"

float GetNodeDistance(const Node& start_n, const Node& end_n)
{
	float distance_x = end_n.x - start_n.x;
	float distance_y = end_n.y - start_n.y;

	return std::max(abs(distance_x), abs(distance_y)) + std::min(abs(distance_x), abs(distance_y)) * (sqrt(2) - 1);
}

void ResetNode(Node& n)
{
	n.cost_f = 0;
	n.cost_g = 0;
	n.cost_h = 0;
	n.parent = nullptr;
}

std::vector<Node*> GetNodeNeighbours(std::vector<Node>& nodes, Node* current_node, bool diagonal = true)
{
	std::vector<Node*> neighbour_nodes;

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

	return neighbour_nodes;
}

bool FindAstarPath(std::vector<Node>& node, Node* start_n, Node* end_n, bool diagonal = true)
{
	if (!start_n || !end_n)
		return false;

	List openNet(start_n);
	List closedNet;

	Node* node;

	while (openNet.size() > 0)
	{
		//Find lowest f cost node n
		//Add n to closedNet and remove from openNEt
		//...
	}


	return 0;
}