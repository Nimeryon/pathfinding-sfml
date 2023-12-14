#include "Tile.h"

Tile::Tile(const TileType& type, float speedFactor) :
	m_type(type),
	m_speedFactor(speedFactor)
{}

const TileType& Tile::GetTileType() const { return m_type; }
const Vector2i& Tile::GetGridPosition() const { return m_gridPosition; }
const Vector2i& Tile::GetLinkPosition() const { return m_link; }
float Tile::GetSpeedFactor() const { return m_speedFactor; }

void Tile::SetGridPosition(const Vector2i& gridPosition)
{
	m_gridPosition = gridPosition;
}
void Tile::SetTileType(const TileType& type)
{
	m_type = type;
	onValueChange(*this);
}
void Tile::SetLink(const Vector2i& position) { m_link = position; }
void Tile::SetSpeedFactor(float speedFactor) { m_speedFactor = speedFactor; }

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
	switch (tile.GetTileType())
	{
	case TileType::START:
		return os << "START";
	case TileType::WALL:
		return os << "WALL";
	case TileType::PORTAL:
		return os << "PORTAL";
	case TileType::END:
		return os << "END";
	case TileType::NONE:
		return os << "NONE";
	}

	return os;
}