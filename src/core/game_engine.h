#pragma once

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <vector>
#include "../entities/player.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

/**
 * @class GameEngine
 * @brief Manages the core game loop, rendering, and player interactions.
 *
 * The GameEngine class is responsible for initializing the game window, managing
 * events, rendering graphical components, and updating game systems, including
 * player controls.
 */
class GameEngine
{
private:
    sf::RenderWindow _window;
    sf::Event _event;
    sf::VideoMode _mode;
    sf::View _viewArea;
    Player _player;

private:
    void _handleEvents(const float &deltaTime);

public:
    // Constructors
    GameEngine();
    ~GameEngine();
    // Public functions
    void run();
    void initializeWindow(unsigned int width, unsigned int height, const std::string &title);
    sf::Vector2u getWindowSize() const;
    // Getters and Setters
    sf::View getViewArea() const;
    void setViewArea(const sf::View &view);
    bool isWindowOpen() const;
    Player &getPlayer();
    void render();
    void update(const float &deltaTime);
};

#endif // GAME_ENGINE_H
