#pragma once
#include <ostream>

#include "Delegate.h"
#include "Vector2.h"

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

	Delegate<const Tile&> onValueChange;

private:
	TileType m_type;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);