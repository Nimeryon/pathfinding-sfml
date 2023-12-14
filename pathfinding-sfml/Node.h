#pragma once
#include "Vector2.h"
#include "Tile.h"

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

    Node(){}

    int GetX() const { return m_position.x; }
    int GetY() const { return m_position.y; }
    const Vector2i& GetPosition() const { return m_position; }

    int GetF() const { return m_cost_g + m_cost_h; }
    int GetG() const { return m_cost_g; }
    int GetH() const { return m_cost_h; }

    float GetNodeDistance(const Node* node) const;
    int GetTileX() const { return m_Tile->GetGridPosition().x; }
    int GetTileY() const { return m_Tile->GetGridPosition().y; }

    float GetNodeDistance(Node* const node);

    void SetG(int cost_g) { m_cost_g = cost_g; }
    void SetH(int cost_h) { m_cost_h = cost_h; }

    void SetParent(Node* parentNode) { m_parent = parentNode; }
    void SetTile(Tile* tile) { m_Tile = tile; }

    void SetPosition(Vector2i pos) { m_position = pos; }
    void SetPosition(int x,int y) { m_position.x = x; m_position.y = y; }


    bool isWalkable() { return m_Tile->GetTileType() != TileType::WALL; }
    bool isPortal() { return m_Tile->GetTileType() == TileType::PORTAL; }
    TileType GetType() { return m_Tile->GetTileType(); }

    void ResetNode();

    bool m_path = false;
    Node* m_parent = nullptr;

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
    Vector2i m_position = { -1, -1 };
    Tile* m_Tile = nullptr;

    int m_cost_g = 0;
    int m_cost_h = 0;
    int m_cost_multiplier = 1;
};