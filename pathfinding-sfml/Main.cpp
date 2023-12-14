#include <iostream>

#include "Astar.h"
#include "Game.h"
#include "Grid.h"
#include "Tile.h"
#include "Pathfinding.h"

int main()
{
    // Exemple
    TileGrid grid({10, 10});

    grid.GetValue(0, 0).SetTileType(TileType::START);
    grid.GetValue(9, 9).SetTileType(TileType::END);
    std::cout << grid;

    auto graph = Pathfinding::GeneratePathfindingGraph(grid);
    Node* start = &graph.GetValue(0, 0);
    Node* end = &graph.GetValue(9, 9);
    bool foundPath = Astar::FindAstarPath(graph, start, end, true);
    std::stack<Vector2i> path;
    if (foundPath)
        path = Astar::RetracePath(start, end);

    Game game("Default Scene");

    return EXIT_SUCCESS;
}