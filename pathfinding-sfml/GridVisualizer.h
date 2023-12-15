#pragma once

#include <stack>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Astar.h"
#include "Grid.h"
#include "Tile.h"

class Tile;

class GridVisualizer
{
public:
    explicit GridVisualizer(Grid<Tile>* _grid, const Vector2& _offset = { 0, 0 }, int _width = 500, int _height = 500);

    void Draw(sf::RenderTarget& target, sf::RenderStates states);


    const std::stack<Astar::PathPosition>& GetPath() const;
    const Vector2& GetTileSize() const;
    const Vector2i& GetOffset() const;
    const Vector2i& GetViewSize() const;

    void SetPath(const std::stack<Astar::PathPosition>& _path);
    void SetOffset(const Vector2i& _offset);
    void SetOveredTile(const Vector2i& mouseGridPosition);

private:
    static sf::Color GetTileTypeColor(const TileType& tileType);

    Vector2 GetPositionToDraw(Vector2i gridPosition) const;

    Grid<Tile>* grid;
    std::stack<Astar::PathPosition> path;

    sf::RectangleShape drawShape;
    Vector2 tileSize;
    Vector2i offset;
    Vector2i viewSize;
    Vector2i overedTile;
};
