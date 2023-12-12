#pragma once
#include <cassert>

#include "Vector2.h"
#include "Grid.h"

///////////////////////////
// Grid without pointers //
///////////////////////////

template <typename Type>
Grid<Type>::Grid(int width, int height) :
	m_width(width),
	m_height(height)
{
	Init();
}

template <typename Type>
Grid<Type>::Grid(const Vector2i& size) :
	Grid(size.x, size.y)
{}

template <typename Type>
Grid<Type>::~Grid()
{
	m_grid.clear();
}

template <typename Type>
int Grid<Type>::GetWidth() const { return m_width; }

template <typename Type>
int Grid<Type>::GetHeight() const { return m_height; }

template <typename Type>
int Grid<Type>::GetIndex(int x, int y) const { return y * m_width + x; }

template <typename Type>
int Grid<Type>::GetIndex(const Vector2i& position) const { return GetIndex(position.x, position.y); }

template <typename Type>
const std::vector<Type>& Grid<Type>::GetGrid() const { return m_grid; }

template <typename Type>
Type& Grid<Type>::GetValue(int x, int y) { return m_grid[GetIndex(x, y)]; }

template <typename Type>
Type& Grid<Type>::GetValue(const Vector2i& position) { return GetValue(position.x, position.y); }

template <typename Type>
void Grid<Type>::SetValue(int x, int y, const Type& tile)
{
	assert(x >= 0 && x < m_width && y >= 0 && y < m_height);

	m_grid[GetIndex(x, y)] = tile;
}

template <typename Type>
void Grid<Type>::SetValue(const Vector2i& position, const Type& tile) { SetValue(position.x, position.y, tile); }

template <typename Type>
void Grid<Type>::Init()
{
	m_grid.reserve(m_width * m_height);
	for (int y = 0; y < m_height; ++y)
		for (int x = 0; x < m_width; ++x)
			m_grid.push_back(Type());
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, Grid<Type>& grid)
{
	for (int y = 0; y < grid.GetHeight(); ++y)
	{
		for (int x = 0; x < grid.GetWidth(); ++x)
		{
			os << grid.GetValue(x, y);
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

template <typename Type>
Grid<Type*>::Grid(int width, int height) :
	m_width(width),
	m_height(height)
{
	Init();
}

template <typename Type>
Grid<Type*>::Grid(const Vector2i& size) :
	Grid(size.x, size.y)
{}

template <typename Type>
Grid<Type*>::~Grid()
{
	for (int i = 0; i < m_width * m_height; ++i)
	{
		delete m_grid[i];
		m_grid[i] = nullptr;
	}

	m_grid.clear();
}

template <typename Type>
int Grid<Type*>::GetWidth() const { return m_width; }

template <typename Type>
int Grid<Type*>::GetHeight() const { return m_height; }

template <typename Type>
int Grid<Type*>::GetIndex(int x, int y) const { return y * m_width + x; }

template <typename Type>
int Grid<Type*>::GetIndex(const Vector2i& position) const { return GetIndex(position.x, position.y); }

template <typename Type>
const std::vector<Type*>& Grid<Type*>::GetGrid() const { return m_grid; }

template <typename Type>
Type* Grid<Type*>::GetValue(int x, int y) { return m_grid[GetIndex(x, y)]; }

template <typename Type>
Type* Grid<Type*>::GetValue(const Vector2i& position) { return GetValue(position.x, position.y); }

template <typename Type>
void Grid<Type*>::SetValue(int x, int y, const Type* tile)
{
	assert(x >= 0 && x < m_width && y >= 0 && y < m_height);

	delete m_grid[GetIndex(x, y)];
	m_grid[GetIndex(x, y)] = tile;
}

template <typename Type>
void Grid<Type*>::SetValue(const Vector2i& position, const Type* tile) { SetTile(position.x, position.y, tile); }

template <typename Type>
void Grid<Type*>::Init()
{
	m_grid.reserve(m_width * m_height);
	for (int y = 0; y < m_height; ++y)
		for (int x = 0; x < m_width; ++x)
			m_grid.push_back(new Type());
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, Grid<Type*>& grid)
{
	for (int y = 0; y < grid.GetHeight(); ++y)
	{
		for (int x = 0; x < grid.GetWidth(); ++x)
		{
			os << *grid.SetValue(x, y);
			if (x != grid.GetWidth() - 1)
				os << ", ";
		}

		if (y != grid.GetHeight() - 1)
			os << std::endl;
	}

	return os;
}