#include "GridVisualizer.h"

#include <SFML/Graphics/RenderTarget.hpp>

GridVisualizer::GridVisualizer(Grid<Tile>* _grid, const Vector2& _offset, int _width, int _height) :
	grid(_grid),
	offset(_offset),
	width(_width),
	height(_height)
{
	if (_grid->GetWidth() > grid->GetHeight())
		tileSize = std::ceil(width / _grid->GetWidth());
	else tileSize = std::ceil(height / _grid->GetHeight());

	drawShape.setSize({ tileSize, tileSize });
	drawShape.setOutlineThickness(1);
	drawShape.setOutlineColor(sf::Color::White);
}

void GridVisualizer::Draw(sf::RenderTarget& target, sf::RenderStates states)
{
	for (int y = 0; y < grid->GetHeight(); ++y)
	{
		for (int x = 0; x < grid->GetWidth(); ++x)
		{
			drawShape.setPosition({offset.x + x * tileSize, offset.y + y* tileSize });
			drawShape.setFillColor(GetTileTypeColor(grid->GetValue(x, y).GetTileType()));
			target.draw(drawShape);
		}
	}
}

const Vector2& GridVisualizer::GetOffset() const { return offset; }
void GridVisualizer::SetOffset(const Vector2& _offset) { offset = _offset; }

sf::Color GridVisualizer::GetTileTypeColor(const TileType& tileType)
{
	switch (tileType)
	{
	case TileType::NONE:
		return sf::Color::Black;
	case TileType::START:
		return sf::Color::Green;
	case TileType::END:
		return sf::Color::Red;
	case TileType::WALL:
		return sf::Color(128, 128, 128);
	default:
		return sf::Color::Magenta;
	}
}
