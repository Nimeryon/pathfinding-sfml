#pragma once
#include "Vector2.h"

class Node
{
public:
    Node(const Vector2i& position) :
        m_position(position),
        m_cost_g(0),
        m_cost_h(0)
    {}

    Node(int x, int y) : 
        m_position( x, y ),
        m_cost_g(0),
        m_cost_h(0)
    {}

    int GetX() const { return m_position.x; }
    int GetY() const { return m_position.y; }
    const Vector2i& GetPosition() const { return m_position; }

    int GetF() const { return m_cost_g + m_cost_h; }
    int GetG() const { return m_cost_g; }
    int GetH() const { return m_cost_h; }

    void SetG(int cost_g) { m_cost_g = cost_g; }
    void SetH(int cost_h) { m_cost_h = cost_h; }

    bool walkable = true;
    bool path = false;
    Node* parent = nullptr;

#pragma region Operator
    bool operator == (const Node& n) const
    {
        return m_position == n.GetPosition();
    }

    bool operator != (const Node& n) const
    {
        return m_position != n.GetPosition();;
    }

    bool operator < (const Node& n) const
    {
        return GetF() < n.GetF();
    }
#pragma endregion

private:
    Vector2i m_position;

    int m_cost_g;
    int m_cost_h;
};