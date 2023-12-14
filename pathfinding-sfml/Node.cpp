#include "Node.h"

void Node::ResetNode() 
{
	SetG(0);
	SetH(0);
	SetParent(nullptr);
	m_path = false;
}

float Node::GetNodeDistance(Node* const node)
{
	sf::Vector2<int> startPos = { GetX(), GetY()};
	sf::Vector2<int> endPos = { node->GetX(), node->GetY() };

	float distance_x = (startPos.x - endPos.x);
	float distance_y = (startPos.y - endPos.y);

	return std::max(abs(distance_x), abs(distance_y)) + std::min(abs(distance_x), abs(distance_y)) * (sqrt(2) - 1);
}
