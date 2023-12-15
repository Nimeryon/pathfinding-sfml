#include "GridVisualizer.h"

#include <SFML/Graphics/RenderTarget.hpp>

GridVisualizer::GridVisualizer(Grid<Tile>* _grid, const Vector2& _offset, int _width, int _height) :
	grid(_grid),
	offset(_offset),
	viewSize(_width, _height)
{
	tileSize.x = static_cast<float>(viewSize.x) / static_cast<float>(_grid->GetWidth());
	tileSize.y = static_cast<float>(viewSize.y) / static_cast<float>(_grid->GetHeight());
}

void GridVisualizer::Draw(sf::RenderTarget& target, sf::RenderStates states)
{
	drawShape.setSize(tileSize);

	// Draw grid
	for (int y = 0; y < grid->GetHeight(); ++y)
	{
		for (int x = 0; x < grid->GetWidth(); ++x)
		{
			drawShape.setOutlineColor(sf::Color(200, 200, 200));
			drawShape.setOutlineThickness(1);

			drawShape.setPosition(GetPositionToDraw({x, y}));
			drawShape.setFillColor(GetTileTypeColor(grid->GetValue(x, y).GetTileType()));
			target.draw(drawShape);
		}
	}

	// Draw overed tile on top
	if (overedTile != Vector2i( - 1, -1 ))
	{
		drawShape.setOutlineColor(sf::Color::White);
		drawShape.setOutlineThickness(2);

		drawShape.setPosition(GetPositionToDraw(overedTile));
		drawShape.setFillColor(GetTileTypeColor(grid->GetValue(overedTile).GetTileType()));
		target.draw(drawShape);
	}

	// Draw path
	if (!path.empty())
	{
		sf::VertexArray lines(sf::PrimitiveType::LineStrip);

		const Vector2 halfTileSize = tileSize / 2.f;
		const Vector2 quarterTileSize = tileSize / 4.f;
		auto tempPath = path;
		int count = 0;
		while (!tempPath.empty())
		{
			const Astar::PathPosition& pathPosition = tempPath.top();
			if (pathPosition.teleported || count == 0 || count == path.size() - 1)
			{
				drawShape.setSize(halfTileSize);
				drawShape.setOutlineThickness(0);
				drawShape.setFillColor(sf::Color::Yellow);
				drawShape.setPosition(GetPositionToDraw(pathPosition.position) + quarterTileSize);
				target.draw(drawShape);
			}

			if (pathPosition.teleported)
			{
				target.draw(lines);
				lines.clear();
			}

			Vector2 position = GetPositionToDraw(pathPosition.position) + halfTileSize;
			lines.append({ position, sf::Color::Yellow });

			tempPath.pop();
			count++;
		}

		target.draw(lines);
	}
}

const std::stack<Astar::PathPosition>& GridVisualizer::GetPath() const { return path; }
const Vector2& GridVisualizer::GetTileSize() const { return tileSize; }
const Vector2i& GridVisualizer::GetOffset() const { return offset; }
const Vector2i& GridVisualizer::GetViewSize() const { return viewSize; }

void GridVisualizer::SetPath(const std::stack<Astar::PathPosition>& _path) { path = _path; }
void GridVisualizer::SetOffset(const Vector2i& _offset) { offset = _offset; }
void GridVisualizer::SetOveredTile(const Vector2i& mouseGridPosition) { overedTile = mouseGridPosition; }

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
	case TileType::PORTAL:
		return sf::Color::Blue;
	case TileType::WALL:
		return sf::Color(128, 128, 128);
	default:
		return sf::Color::Magenta;
	}
}

Vector2 GridVisualizer::GetPositionToDraw(Vector2i gridPosition) const
{
	return { offset.x + gridPosition.x * tileSize.x, offset.y + gridPosition.y * tileSize.y };
}