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
	const Type& GetValue(int x, int y) const;
	const Type& GetValue(const Vector2i& position) const;

	void SetValue(int x, int y, const Type& tile);
	void SetValue(const Vector2i& position, const Type& tile);

protected:
	virtual void Init();

	int m_width, m_height;
	std::vector<Type> m_grid;
};

#include "Grid.hxx"