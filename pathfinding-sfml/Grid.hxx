#pragma once
#include <cassert>

#include "Vector2.h"
#include "Grid.h"

///////////////////////////
// Grid without pointers //
///////////////////////////

template <typename TileType>
Grid<TileType>::Grid(int width, int height) :
	m_width(width),
	m_height(height)
{
	Init();
}

template <typename TileType>
Grid<TileType>::Grid(const Vector2i& size) :
	Grid(size.x, size.y)
{}

template <typename TileType>
Grid<TileType>::~Grid()
{
	m_tiles.clear();
}

template <typename TileType>
int Grid<TileType>::GetWidth() const { return m_width; }

template <typename TileType>
int Grid<TileType>::GetHeight() const { return m_height; }

template <typename TileType>
int Grid<TileType>::GetTileIndex(int x, int y) const { return y * m_width + x; }

template <typename TileType>
int Grid<TileType>::GetTileIndex(const Vector2i& position) const { return GetTileIndex(position.x, position.y); }

template <typename TileType>
const std::vector<TileType>& Grid<TileType>::GetTiles() const { return m_tiles; }

template <typename TileType>
const TileType& Grid<TileType>::GetTile(int x, int y) const { return m_tiles[GetTileIndex(x, y)]; }

template <typename TileType>
const TileType& Grid<TileType>::GetTile(const Vector2i& position) const { return GetTile(position.x, position.y); }

template <typename TileType>
void Grid<TileType>::SetTile(int x, int y, const TileType& tile)
{
	assert(x >= 0 && x < m_width && y >= 0 && y < m_height);

	m_tiles[GetTileIndex()] = tile;
}

template <typename TileType>
void Grid<TileType>::SetTile(const Vector2i& position, const TileType& tile) { SetTile(position.x, position.y, tile); }

template <typename TileType>
void Grid<TileType>::Init()
{
	m_tiles.reserve(m_width * m_height);
	for (int y = 0; y < m_height; ++y)
		for (int x = 0; x < m_width; ++x)
			m_tiles.push_back(TileType());
}

template <typename TileType>
std::ostream& operator<<(std::ostream& os, const Grid<TileType>& grid)
{
	for (int y = 0; y < grid.GetHeight(); ++y)
	{
		for (int x = 0; x < grid.GetWidth(); ++x)
		{
			os << grid.GetTile(x, y);
			if (x != grid.GetWidth() - 1)
				os << ", ";
		}

		if (y != grid.GetHeight() - 1)
			os << std::endl;
	}

	return os;
}

////////////////////////
// Grid with pointers //
////////////////////////

template <typename TileType>
Grid<TileType*>::Grid(int width, int height) :
	m_width(width),
	m_height(height)
{
	Init();
}

template <typename TileType>
Grid<TileType*>::Grid(const Vector2i& size) :
	Grid(size.x, size.y)
{}

template <typename TileType>
Grid<TileType*>::~Grid()
{
	for (int i = 0; i < m_width * m_height; ++i)
	{
		delete m_tiles[i];
		m_tiles[i] = nullptr;
	}

	m_tiles.clear();
}

template <typename TileType>
int Grid<TileType*>::GetWidth() const { return m_width; }

template <typename TileType>
int Grid<TileType*>::GetHeight() const { return m_height; }

template <typename TileType>
int Grid<TileType*>::GetTileIndex(int x, int y) const { return y * m_width + x; }

template <typename TileType>
int Grid<TileType*>::GetTileIndex(const Vector2i& position) const { return GetTileIndex(position.x, position.y); }

template <typename TileType>
const std::vector<TileType*>& Grid<TileType*>::GetTiles() const { return m_tiles; }

template <typename TileType>
const TileType* Grid<TileType*>::GetTile(int x, int y) const { return m_tiles[GetTileIndex(x, y)]; }

template <typename TileType>
const TileType* Grid<TileType*>::GetTile(const Vector2i& position) const { return GetTile(position.x, position.y); }

template <typename TileType>
void Grid<TileType*>::SetTile(int x, int y, const TileType* tile)
{
	assert(x >= 0 && x < m_width && y >= 0 && y < m_height);

	delete m_tiles[GetTileIndex(x, y)];
	m_tiles[GetTileIndex(x, y)] = tile;
}

template <typename TileType>
void Grid<TileType*>::SetTile(const Vector2i& position, const TileType* tile) { SetTile(position.x, position.y, tile); }

template <typename TileType>
void Grid<TileType*>::Init()
{
	m_tiles.reserve(m_width * m_height);
	for (int y = 0; y < m_height; ++y)
		for (int x = 0; x < m_width; ++x)
			m_tiles.push_back(new TileType());
}

template <typename TileType>
std::ostream& operator<<(std::ostream& os, const Grid<TileType*>& grid)
{
	for (int y = 0; y < grid.GetHeight(); ++y)
	{
		for (int x = 0; x < grid.GetWidth(); ++x)
		{
			os << *grid.GetTile(x, y);
			if (x != grid.GetWidth() - 1)
				os << ", ";
		}

		if (y != grid.GetHeight() - 1)
			os << std::endl;
	}

	return os;
}