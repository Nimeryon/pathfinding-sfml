#pragma once

struct Node
{
	Node(unsigned m_x, unsigned m_y) : x(m_x), y(m_y) {}

	struct
	{
		unsigned x, y;

		int cost_f = 0; //g + h
		int cost_g = 0;
		int cost_h = 0;

		Node* parent = nullptr;

	};

	bool operator == (const Node& n) const
	{
		return x == n.x && y == n.y;
	}

	bool operator != (const Node& n) const
	{
		return x != n.x || y != n.y;
	}
};