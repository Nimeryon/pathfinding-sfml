#include <format>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

void DrawFPSMeter(const sf::Time& deltaTime)
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
    ImGui::Text(std::format("{} FPS", floorf(1.f / deltaTime.asSeconds())).c_str());
    ImGui::End();
}

int main()
{
    // Create default window
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML & ImGUI Template");

    // Initialize ImGUI
    if (!ImGui::SFML::Init(window))
        return EXIT_FAILURE;

    // Create test circle shape
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Create deltaTime clock
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        // Poll window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Pass events to ImGUI
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Restart clock to get deltaTime
        sf::Time deltaTime = deltaClock.restart();
        // Update ImGUI
    	ImGui::SFML::Update(window, deltaTime);

        // Render FPSMeter
        DrawFPSMeter(deltaTime);

        // Clear window buffer
        window.clear();

        // Draw our circle shape
        window.draw(shape);

        // Render ImGui last before displaying window
        ImGui::SFML::Render(window);
        window.display();
    }

    // Shutting down ImGUI before closing everything
    ImGui::SFML::Shutdown(window);

    return EXIT_SUCCESS;
}