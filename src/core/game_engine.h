/**
 * @file game_engine.h
 * @brief Defines the GameEngine class for managing the game environment.
 *
 * This header file contains the declaration of the GameEngine class, which handles
 * the main window, event processing, and interactions with the Player class and other game systems.
 */

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
    sf::RenderWindow _window; ///< Main rendering window for the game.
    sf::Event _event;         ///< Event handler for user input and window events.
    sf::VideoMode _mode;      ///< Screen resolution and video mode information.
    sf::View _viewArea;       ///< Defines the viewable area of the game.
    Player _player;           ///< Instance of the Player class, representing the player character.

    /**
     * @brief Processes window and user input events.
     */
    void _handleEvents();

public:
    /**
     * @brief Constructs the game environment and initializes all necessary systems.
     */
    GameEngine();

    /**
     * @brief Destructor for cleaning up game resources.
     */
    ~GameEngine();

    /**
     * @brief Runs the main game loop, updating and rendering all systems.
     */
    void run();

    /**
     * @brief Initializes the game window with specified dimensions.
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param title The title of the game window.
     */
    void initializeWindow(unsigned int width, unsigned int height, const std::string &title);

    /**
     * @brief Gets the current dimensions of the game window.
     * @return An sf::Vector2u containing the width and height of the window.
     */
    sf::Vector2u getWindowSize() const;

    /**
     * @brief Gets the viewable area of the game.
     * @return An sf::View object representing the current viewable area.
     */
    sf::View getViewArea() const;

    /**
     * @brief Sets the viewable area of the game.
     * @param view The sf::View object defining the new view area.
     */
    void setViewArea(const sf::View &view);

    /**
     * @brief Checks if the game window is open.
     * @return True if the window is open, false otherwise.
     */
    bool isWindowOpen() const;

    /**
     * @brief Gets a reference to the player object for external interactions.
     * @return A reference to the Player instance.
     */
    Player &getPlayer();

    /**
     * @brief Renders all game components, including the player and other visuals.
     */
    void render();

    /**
     * @brief Updates the game state, including the player and other systems.
     */
    void update();
};

#endif // GAME_ENGINE_H
