#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class Player
 * @brief Represents the player character and handles its movement, collisions, and rendering.
 */
class Player
{
private:
    sf::Vector2f _screenSize;    ///< Dimensions of the game screen
    sf::RectangleShape _body;    ///< Graphical representation of the player
    sf::Vector2f _rectDimension; ///< Dimensions of the player's rectangle
    sf::Vector2f _rectPosition;  ///< Position of the player's rectangle

    /**
     * @brief Checks and resolves collisions with the screen boundaries.
     */
    void _checkCollisions();

public:
    /**
     * @brief Constructs a Player object with a specified screen size.
     * @param screenSize The dimensions of the screen.
     */
    Player(sf::Vector2f screenSize);

    /**
     * @brief Destructor for the Player class.
     */
    ~Player();

    /**
     * @brief Draws the player onto the provided render window.
     * @param window Reference to the SFML render window.
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Updates the player's state, including collision handling.
     */
    void update();

    /**
     * @brief Moves the player based on keyboard input.
     * @param event The SFML event containing keyboard input data.
     */
    void move(const sf::Event &event);

    /**
     * @brief Gets the player's current dimensions.
     * @return The dimensions of the player's rectangle.
     */
    sf::Vector2f getDimension() const;

    /**
     * @brief Gets the player's current position.
     * @return The position of the player's rectangle.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Sets the player's position.
     * @param position The new position of the player's rectangle.
     */
    void setPosition(const sf::Vector2f &position);

    /**
     * @brief Sets the player's dimensions.
     * @param dimension The new dimensions of the player's rectangle.
     */
    void setDimension(const sf::Vector2f &dimension);
};

#endif // PLAYER_H
