#include <iostream>

#include "Game.h"
#include "Grid.h"
#include "Tile.h"

int main()
{
    // Exemple
    Grid<Tile> grid(10, 10);
    grid.GetValue(0, 0).SetTileType(TileType::START);
    std::cout << grid;

    Game game("Default Scene");

    return EXIT_SUCCESS;
}