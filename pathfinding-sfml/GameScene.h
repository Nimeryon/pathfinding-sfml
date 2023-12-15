#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Node.h"
#include "Scene.h"
#include "Vector2.h"

class GridVisualizer;
class TileGrid;

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene() override;

    void Init() override;
    void ProcessInput(const sf::Event& event) override;
    void Update(const sf::Time& dt) override;
    void ImGui(const sf::Time& dt) override;
    void Draw(sf::RenderWindow& window) override;

    void PlaceTile(bool processPortalPlacement = true);

    void GeneratePath();

protected:
    Vector2i windowSize;
    Vector2i imGuiWindowSize, imGuiWindowPosition;
    Vector2i mousePosition, mouseGridPosition, previousMouseGridPosition;
    bool isDrawing, isErasing, autoUpdateGraph, useDiagonal;
    std::string errorMessage;

    TileGrid* grid = nullptr;
    GridVisualizer* visualizer = nullptr;

    Grid<Node> pathFindingGraph;

    int currentTypeToPlace = 0;

    Vector2i portalGridPositionStart, portalGridPositionEnd;
    bool isCreatingPortal;
};
