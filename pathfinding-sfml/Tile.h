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
	explicit Tile(const TileType& type = TileType::NONE, float speedFactor = 1.f);

	const TileType& GetTileType() const;
	const Vector2i& GetGridPosition() const;
	const Vector2i& GetLinkPosition() const;
	float GetSpeedFactor() const;

	void SetGridPosition(const Vector2i& gridPosition);
	void SetTileType(const TileType& type);
	void SetLink(const Vector2i& position);
	void SetSpeedFactor(float speedFactor);

	Delegate<const Tile&> onValueChange;

private:
	float m_speedFactor;
	TileType m_type;
	Vector2i m_gridPosition, m_link;
};

std::ostream& operator<<(std::ostream& os, const Tile& tile);