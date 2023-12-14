#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Grid.h"
#include "Tile.h"

class Tile;

class GridVisualizer
{
public:
    explicit GridVisualizer(Grid<Tile>* _grid, const Vector2& _offset = { 0, 0 }, int _width = 500, int _height = 500);

    void Draw(sf::RenderTarget& target, sf::RenderStates states);

    const Vector2& GetOffset() const;
    void SetOffset(const Vector2& _offset);

private:
    static sf::Color GetTileTypeColor(const TileType& tileType);

    Grid<Tile>* grid;

    sf::RectangleShape drawShape;
    Vector2 offset;
    int width, height;
    float tileSize;
};
