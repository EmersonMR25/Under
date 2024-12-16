#pragma once

#ifndef PLAYER_H
#define PLAYER_H

// Global Constanst
#define _GRAVITY 200.0f
#define _JUMP_STRENGHT 100.0f
#define _SPEED 600.0f

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class Player
 * @brief Represents the player character and handles its movement, collisions, and rendering.
 */
class Player
{
private:
    sf::Vector2f _screenSize;
    sf::RectangleShape _body;
    sf::Vector2f _rectDimension;
    sf::Vector2f _rectPosition;
    bool _isGroundLevel;
    sf::Vector2f _speed;

private:
    void _checkCollisions();

public:
    // Construcctors
    Player(const sf::Vector2f &screenSize);
    ~Player();
    // Public member functions
    void draw(sf::RenderWindow &window);
    void update();
    void move(const sf::Event &event, const float &deltaTime);
    // Getters and Setters
    sf::Vector2f getDimension() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);
    void setDimension(const sf::Vector2f &dimension);
    bool getGroundLevel() const;
    void setGroundLevel(const bool &state);
};

#endif // PLAYER_H
