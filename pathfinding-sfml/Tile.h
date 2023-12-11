#pragma once
#include <ostream>

enum class TileType
{
	NONE,
	START,
	WALL,
	END
};

class Tile
{
public:
	Tile(const TileType& type = TileType::NONE);

	const TileType& GetTileType() const;

	void SetTileType(const TileType& type);

private:
	TileType m_type;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);