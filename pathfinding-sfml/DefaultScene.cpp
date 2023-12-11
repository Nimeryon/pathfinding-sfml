#include "DefaultScene.h"

#include <format>

#include "imgui.h"

void DefaultScene::Init()
{
    shape.setRadius(100.f);
    shape.setFillColor(sf::Color::Green);
}

void DefaultScene::ImGui(const sf::Time& dt)
{
    // Stylizing overlay
    ImGuiWindowFlags imFlags = ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoFocusOnAppearing
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoMouseInputs
        | ImGuiWindowFlags_NoNav;
    ImGui::SetNextWindowPos({ 4, 4 });
    ImGui::SetNextWindowBgAlpha(0.5f);

    // Creating overlay
    ImGui::Begin("FPS Overlay", 0, imFlags);
    ImGui::Text(std::format("{} FPS", floorf(1.f / dt.asSeconds())).c_str());
    ImGui::End();
}

void DefaultScene::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}