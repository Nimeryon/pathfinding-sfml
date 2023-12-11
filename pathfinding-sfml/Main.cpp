#include <iostream>

#include "Game.h"
#include "Grid.h"
#include "Tile.h"

int main()
{
    // Exemple
    Grid<Tile> grid(10, 10);
    grid.SetValue(0, 0, TileType::START);
    grid.SetValue(9, 9, TileType::END);
    std::cout << grid;

    Game game("Default Scene");

    return EXIT_SUCCESS;
}