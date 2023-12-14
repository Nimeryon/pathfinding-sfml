#pragma once
#include "Grid.h"
#include "Tile.h"

class TileGrid : public Grid<Tile>
{
public:
	TileGrid(const Vector2i& size);

	Vector2i GetStartPosition() const;
	Vector2i GetEndPosition() const;
	const TileType& GetTileType(const Vector2i& position) const;

	void SetTileType(const Vector2i& position, const TileType& tileType);

	void CreatePortal(const Vector2i& start, const Vector2i& end);

	void Init() override;
	void Reset();
};
