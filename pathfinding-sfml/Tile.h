#pragma once
#include <ostream>
#include "Vector2.h"

#include "Delegate.h"
#include "Vector2.h"

enum class TileType
{
	NONE,
	START,
	WALL,
	PORTAL,
	END
};

class Tile
{
public:
	Tile(const TileType& type = TileType::NONE);

	const TileType& GetTileType() const;

	void SetTileType(const TileType& type);
	void SetLink(const Vector2i pos);

	Vector2i GetLinkPos();

	Delegate<const Tile&> onValueChange;

private:
	TileType m_type;
	Vector2i m_link;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);