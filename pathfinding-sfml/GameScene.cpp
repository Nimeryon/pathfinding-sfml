#include "GameScene.h"
#include "GridVisualizer.h"

GameScene::~GameScene()
{
    delete grid;
    delete visualizer;
}

void GameScene::Init()
{
    grid = new Grid<Tile>(100, 100);
    grid->GetValue(0, 0).SetTileType(TileType::START);
    grid->GetValue(9, 9).SetTileType(TileType::END);

    visualizer = new GridVisualizer(grid, { 50, 50 });
}

void GameScene::Draw(sf::RenderWindow& window)
{
    visualizer->Draw(window, sf::RenderStates());
}