#pragma once
#include<vector>
#include"Node.h"

struct List : private std::vector<Node*>
{
public:
	using vector::push_back;
	using vector::operator[];
	using vector::begin;
	using vector::end;
	using vector::size;

	List() = default;

	List(Node* n) {
		push_back(n);
	};

	List(const std::vector<Node*>& n) {
		operator=(n);
	};
	virtual ~List() {};

	bool contains(const Node& n) const {
		for (int i = 0; i < size(); i++)
			if (*operator[](i) == n)
				return true;
		return false;
	}

	void remove(size_t iterator) {
		erase(begin() + iterator);
	}
private:
	typedef std::vector<Node*> vector;
};