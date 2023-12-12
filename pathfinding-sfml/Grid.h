#pragma once
#include <ostream>
#include <vector>

#include "Vector2.h"

template<typename Type>
class Grid
{
public:
	using type = Type;

	explicit Grid(int width = 0, int height = 0);
	Grid(const Vector2i& size);

	virtual ~Grid();

	int GetWidth() const;
	int GetHeight() const;

	int GetIndex(int x, int y) const;
	int GetIndex(const Vector2i& position) const;

	const std::vector<Type>& GetGrid() const;
	Type& GetValue(int x, int y);
	Type& GetValue(const Vector2i& position);

	void SetValue(int x, int y, const Type& tile);
	void SetValue(const Vector2i& position, const Type& tile);

protected:
	void Init();

	int m_width, m_height;
	std::vector<Type> m_grid;
};

template <typename Type>
class Grid<Type*>
{
public:
	using type = Type;

	explicit Grid(int width = 0, int height = 0);
	Grid(const Vector2i& size);

	virtual ~Grid();

	int GetWidth() const;
	int GetHeight() const;

	int GetIndex(int x, int y) const;
	int GetIndex(const Vector2i& position) const;

	const std::vector<Type*>& GetGrid() const;
	Type* GetValue(int x, int y);
	Type* GetValue(const Vector2i& position);

	void SetValue(int x, int y, const Type* tile);
	void SetValue(const Vector2i& position, const Type* tile);

protected:
	void Init();

	int m_width, m_height;
	std::vector<Type*> m_grid;
};

template<typename Type>
std::ostream& operator<<(std::ostream& os, Grid<Type>& grid);

template<typename Type>
std::ostream& operator<<(std::ostream& os, Grid<Type*>& grid);

#include "Grid.hxx"