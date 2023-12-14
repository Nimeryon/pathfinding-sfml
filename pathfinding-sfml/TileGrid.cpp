#include "TileGrid.h"

TileGrid::TileGrid(const Vector2i& size) : Grid(size)
{
	Init();
}

Vector2i TileGrid::GetStartPosition() const
{
	for (int y = 0; y < GetHeight(); ++y)
		for (int x = 0; x < GetWidth(); ++x)
			if (GetValue(x, y).GetTileType() == TileType::START)
				return { x, y };

	return { -1, -1 };
}
Vector2i TileGrid::GetEndPosition() const
{
	for (int y = 0; y < GetHeight(); ++y)
		for (int x = 0; x < GetWidth(); ++x)
			if (GetValue(x, y).GetTileType() == TileType::END)
				return { x, y };

	return { -1, -1 };
}
const TileType& TileGrid::GetTileType(const Vector2i& position) const { return GetValue(position).GetTileType(); }

void TileGrid::SetTileType(const Vector2i& position, const TileType& tileType)
{
	GetValue(position).SetTileType(tileType);
}

void TileGrid::CreatePortal(const Vector2i& start, const Vector2i& end)
{
	SetTileType(start, TileType::PORTAL);
	GetValue(start).SetLink(end);

	SetTileType(end, TileType::PORTAL);
	GetValue(end).SetLink(start);
}

void TileGrid::Init()
{
	Grid::Init();

	for (int y = 0; y < GetHeight(); ++y)
		for (int x = 0; x < GetWidth(); ++x)
			GetValue(x, y).SetGridPosition({ x, y });

	GetValue(0, 0).SetTileType(TileType::START);
	GetValue(GetWidth() - 1, GetHeight() - 1).SetTileType(TileType::END);
}
void TileGrid::Reset()
{
	for (int y = 0; y < GetHeight(); ++y)
		for (int x = 0; x < GetWidth(); ++x)
			GetValue(x, y).SetTileType(TileType::NONE);

	GetValue(0, 0).SetTileType(TileType::START);
	GetValue(GetWidth() - 1, GetHeight() - 1).SetTileType(TileType::END);
}
