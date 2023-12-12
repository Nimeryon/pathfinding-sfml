#include "Tile.h"

Tile::Tile(const TileType& type) :
	m_type(type)
{}

const TileType& Tile::GetTileType() const { return m_type; }

void Tile::SetTileType(const TileType& type) { m_type = type; }

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
	switch (tile.GetTileType())
	{
		case TileType::START:
			return os << "START";
		case TileType::WALL:
			return os << "WALL";
		case TileType::END:
			return os << "END";
		case TileType::NONE:
			return os << "NONE";
	}

	return os;
}