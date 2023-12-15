#include "GameScene.h"

#include "Astar.h"
#include "Config.h"
#include "GridVisualizer.h"
#include "imgui.h"
#include "Pathfinding.h"
#include "TileGrid.h"

GameScene::GameScene() :
	isDrawing(false),
	isErasing(false),
	autoUpdateGraph(false),
	useDiagonal(true),
	isCreatingPortal(false)
{}
GameScene::~GameScene()
{
    delete grid;
    delete visualizer;
}

void GameScene::Init()
{
    constexpr int margin = 16;

    windowSize.x = Config::GetConfig<int>("Assets\\config.json", "Window", "Width");
    windowSize.y = Config::GetConfig<int>("Assets\\config.json", "Window", "Height");
    const int size = windowSize.y - 2 * margin;

    imGuiWindowSize = { windowSize.x - ( size + 3 * margin), size };
    imGuiWindowPosition = { size + 2 * margin, margin };

    grid = new TileGrid({25, 25});
    visualizer = new GridVisualizer(grid, { margin, margin }, size, size);

    pathFindingGraph = Pathfinding::GeneratePathfindingGraph(*grid);
}

void GameScene::ProcessInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        mousePosition = { event.mouseMove.x, event.mouseMove.y };
        if (mousePosition.x < visualizer->GetOffset().x ||
            mousePosition.x > visualizer->GetOffset().x + visualizer->GetViewSize().x ||
            mousePosition.y < visualizer->GetOffset().y ||
            mousePosition.y > visualizer->GetOffset().y + visualizer->GetViewSize().y)
        {
            mouseGridPosition = { -1, -1 };
        }
        else
        {
            mouseGridPosition = {
	            static_cast<int>((mousePosition.x - visualizer->GetOffset().x) / visualizer->GetTileSize().x),
	            static_cast<int>((mousePosition.y - visualizer->GetOffset().y) / visualizer->GetTileSize().y)
            };
        }

        visualizer->SetOveredTile(mouseGridPosition);

        if (isDrawing && previousMouseGridPosition != mouseGridPosition)
            PlaceTile(false);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        isDrawing = true;
    	if (event.mouseButton.button == sf::Mouse::Left)
            isErasing = false;
        else if (event.mouseButton.button == sf::Mouse::Right)
            isErasing = true;

        PlaceTile(false);
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        isDrawing = false;
        PlaceTile();

        if (autoUpdateGraph)
            GeneratePath();
    }
}

void GameScene::Update(const sf::Time& dt)
{
    previousMouseGridPosition = mouseGridPosition;
}

void GameScene::ImGui(const sf::Time& dt)
{
    ImGuiWindowFlags imFlags = 
          ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoFocusOnAppearing
        | ImGuiWindowFlags_NoNav;
    ImGui::SetNextWindowSize(imGuiWindowSize);
    ImGui::SetNextWindowPos(imGuiWindowPosition);
    ImGui::SetNextWindowBgAlpha(0.5f);

    ImGui::Begin("Tools", 0, imFlags);

    // Tile type selector

    const char* placableTypes[] = { "Wall", "Portal", "Start", "End" };
    ImGui::Combo("Tile Type", &currentTypeToPlace, placableTypes, IM_ARRAYSIZE(placableTypes));
    ImGui::Separator();

    // Buttons

    if (ImGui::Checkbox("Use diagonals", &useDiagonal))
        if (autoUpdateGraph)
			GeneratePath();

    if (ImGui::Checkbox("Auto update pathfinding", &autoUpdateGraph))
        GeneratePath();

    if (ImGui::Button("Generate path")) GeneratePath();
    ImGui::SameLine();
    if (ImGui::Button("Clear path"))
    {
        visualizer->SetPath({});
        autoUpdateGraph = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset"))
    {
        visualizer->SetPath({});
        grid->Reset();
        Pathfinding::ResetGraph(pathFindingGraph);
        errorMessage.clear();

        if (autoUpdateGraph)
            GeneratePath();
    }

    if (!errorMessage.empty())
        ImGui::TextColored({ 255, 0, 0, 255 }, errorMessage.c_str());

    ImGui::End();
}

void GameScene::Draw(sf::RenderWindow& window)
{
    visualizer->Draw(window, sf::RenderStates());
}

void GameScene::PlaceTile(bool processPortalPlacement)
{
    if (mouseGridPosition == Vector2i(-1, -1)) return;

    visualizer->SetPath({});

    if (!isErasing)
    {
        switch (currentTypeToPlace)
        {
        case 0:
            grid->SetTileType(mouseGridPosition, TileType::WALL);
            break;

        case 1:
            if (!processPortalPlacement) break;

            if (!isCreatingPortal)
            {
                isCreatingPortal = true;
                portalGridPositionStart = mouseGridPosition;
            }
            else
            {
                portalGridPositionEnd = mouseGridPosition;
                if (portalGridPositionStart != portalGridPositionEnd)
                {
                    grid->CreatePortal(portalGridPositionStart, portalGridPositionEnd);
                    isCreatingPortal = false;
                    portalGridPositionStart = { -1, -1 };
                    portalGridPositionEnd = { -1, -1 };
                }
            }
            break;

        case 2:
            grid->SetTileType(mouseGridPosition, TileType::START);
            break;

        case 3:
            grid->SetTileType(mouseGridPosition, TileType::END);
            break;

        default:
            grid->SetTileType(mouseGridPosition, TileType::NONE);
            break;
        }
    }
    else grid->SetTileType(mouseGridPosition, TileType::NONE);
}

void GameScene::GeneratePath()
{
    pathFindingGraph = Pathfinding::GeneratePathfindingGraph(*grid);
    if (grid->GetStartPosition() == Vector2i(-1, -1) || grid->GetEndPosition() == Vector2i(-1, -1))
    {
        errorMessage = "No start or end point detected on the grid please place one of each.";
        return;
    }

    if (Astar::FindAstarPath(pathFindingGraph, grid->GetStartPosition(), grid->GetEndPosition(), useDiagonal))
    {
        errorMessage.clear();
        visualizer->SetPath(Astar::RetracePath(pathFindingGraph, grid->GetStartPosition(), grid->GetEndPosition()));
    }
    else
    {
        errorMessage = "No path found between start and end position.";
    }
}
