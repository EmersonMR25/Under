/**
 * @file game.h
 * @brief Defines the Game class for managing the particle simulation system
 *
 * This header file contains the declaration of the Game class which handles
 * the main window, event processing, and particle system management for
 * the physics simulation.
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
 * @class Game
 * @brief Controls the main simulation environment and particle system
 *
 * The Game class manages the simulation window, processes user input events,
 * and coordinates the particle system. It serves as the main controller
 * for the entire application.
 */
class GameEngine
{
private:
    sf::RenderWindow _window; ///< Main rendering window for the simulation
    sf::Event _event;         ///< Event handler for user input and window events
    sf::VideoMode _mode;      ///< Get devide's screen resolutions
    sf::View _viewArea;       ///< Get the viewable area
    Player _player;           ///< player class
private:
    /**
     * @brief Processes window and user input events
     */
    void _handleEvents();

    /**
     * @brief Check bounds for possition of player
     */
    void _checkBounds();

public:
    /**
     * @brief Constructs the game environment and initializes systems
     */
    GameEngine();

    /**
     * @brief Destructor for cleaning up game resources
     */
    ~GameEngine();
};

#endif // GAME_H