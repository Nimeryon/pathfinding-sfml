#pragma once

#include <SFML/Graphics.hpp>

#include "GridVisualizer.h"
#include "Scene.h"

class GameScene : public Scene
{
public:
    ~GameScene();

    void Init() override;
    void Draw(sf::RenderWindow& window) override;

protected:
    Grid<Tile>* grid;
    GridVisualizer* visualizer;
};
