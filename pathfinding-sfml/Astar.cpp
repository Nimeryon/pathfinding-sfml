#include <array>
#include <vector>

#include "Astar.hpp"
#include "List.hpp"

float GetNodeDistance(const Node& start_n, const Node& end_n)
{
	float distance_x = end_n.x - start_n.x;
	float distance_y = end_n.y - start_n.y;

	return std::max(abs(distance_x), abs(distance_y)) + std::min(abs(distance_x), abs(distance_y)) * (sqrt(2) - 1);
}

bool FindAstarPath()
{
	return 0;
}