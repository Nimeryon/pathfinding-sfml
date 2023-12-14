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

    grid.SetTileType({0, 0}, TileType::START);
    grid.SetTileType({9, 9}, TileType::END);
    grid.CreatePortal({ 1, 1 }, { 8, 8 });
    for (int i = 0; i < 10; ++i)
        grid.SetTileType({ 4, i }, TileType::WALL);
    std::cout << grid;

    auto graph = Pathfinding::GeneratePathfindingGraph(grid);
    Node* start = &graph.GetValue(grid.GetStartPosition());
    Node* end = &graph.GetValue(grid.GetEndPosition());
    bool foundPath = Astar::FindAstarPath(graph, start, end, true);
    std::stack<Vector2i> path;
    if (foundPath)
        path = Astar::RetracePath(start, end);

    Game game("Default Scene");

    return EXIT_SUCCESS;
}