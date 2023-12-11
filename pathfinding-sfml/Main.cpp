#include <iostream>

#include "Game.h"
#include "Grid.h"
#include "Tile.h"
#include "Variables.h"

int main()
{
    // Exemple
    Grid<Tile> grid(SIZE_X, SIZE_Y);
    grid.SetValue(0, 0, TileType::START);
    grid.SetValue(9, 9, TileType::END);
    std::cout << grid;

    Game game("Default Scene");

    return EXIT_SUCCESS;
}