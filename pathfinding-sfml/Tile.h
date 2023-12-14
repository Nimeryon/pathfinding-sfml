#pragma once
#include <ostream>

#include "Vector2.h"
#include "Delegate.h"

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
	const Vector2i& GetGridPosition() const;
	const Vector2i& GetLinkPosition() const;

	void SetGridPosition(const Vector2i& gridPosition);
	void SetTileType(const TileType& type);
	void SetLink(const Vector2i& position);

	Delegate<const Tile&> onValueChange;

private:
	TileType m_type;
	Vector2i m_gridPosition, m_link;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);