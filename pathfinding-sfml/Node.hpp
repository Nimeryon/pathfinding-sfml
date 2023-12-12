#pragma once

enum class NodeType
{
	StartingNode, TargetedNode, PathNode, ObstacleNode, None
};


struct Node
{
	Node(unsigned m_x, unsigned m_y) : x(m_x), y(m_y) {}

	struct
	{
		unsigned x, y;

		bool walkable	= true;
		bool path		= false;

		int cost_f = 0; //g + h
		int cost_g = 0;
		int cost_h = 0;

		Node* parent = nullptr;
		NodeType type;
	};

#pragma region Operator
	bool operator == (const Node& n) const
	{
		return x == n.x && y == n.y;
	}

	bool operator != (const Node& n) const
	{
		return x != n.x || y != n.y;
	}

	inline bool operator < (const Node& n)
	{
		return cost_f < n.cost_f;
	}
#pragma endregion

	
};