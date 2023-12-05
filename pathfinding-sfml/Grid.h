#pragma once
#include <ostream>
#include <vector>

#include "Vector2.h"

template<typename TileType>
class Grid
{
public:
	using tile_type = TileType;

	explicit Grid(int width = 0, int height = 0);
	Grid(const Vector2i& size);

	virtual ~Grid();

	int GetWidth() const;
	int GetHeight() const;

	int GetTileIndex(int x, int y) const;
	int GetTileIndex(const Vector2i& position) const;

	const std::vector<TileType>& GetTiles() const;
	const TileType& GetTile(int x, int y) const;
	const TileType& GetTile(const Vector2i& position) const;

	// void SetWidth(int width);
	// void SetHeight(int height);
	// void SetSize(int width, int height);
	// void SetSize(const Vector2i& size);

	void SetTile(int x, int y, const TileType& tile);
	void SetTile(const Vector2i& position, const TileType& tile);

protected:
	void Init();

	int m_width, m_height;
	std::vector<TileType> m_tiles;
};

template <typename TileType>
class Grid<TileType*>
{
public:
	using tile_type = TileType;

	explicit Grid(int width = 0, int height = 0);
	Grid(const Vector2i& size);

	virtual ~Grid();

	int GetWidth() const;
	int GetHeight() const;

	int GetTileIndex(int x, int y) const;
	int GetTileIndex(const Vector2i& position) const;

	const std::vector<TileType*>& GetTiles() const;
	const TileType* GetTile(int x, int y) const;
	const TileType* GetTile(const Vector2i& position) const;

	// void SetWidth(int width);
	// void SetHeight(int height);
	// void SetSize(int width, int height);
	// void SetSize(const Vector2i& size);

	void SetTile(int x, int y, const TileType* tile);
	void SetTile(const Vector2i& position, const TileType* tile);

protected:
	void Init();

	int m_width, m_height;
	std::vector<TileType*> m_tiles;
};

template<typename TileType>
std::ostream& operator<<(std::ostream& os, const Grid<TileType>& grid);

template<typename TileType>
std::ostream& operator<<(std::ostream& os, const Grid<TileType*>& grid);

#include "Grid.hxx"