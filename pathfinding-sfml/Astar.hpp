#pragma once
#include <array>
#include <vector>

#include "Node.hpp"
#include "List.hpp"
#include "Grid.h"
#include "Variables.h"

float GetNodeDistance(const Node& start_n, const Node& end_n);

std::vector<Node*> GetNodeNeighbours(std::vector<Node>& nodes, Node* current_node, bool diagonal = true);

void ResetNode(Node& n);

bool FindAstarPath(Node* start_n = nullptr, Node* end_n = nullptr);
