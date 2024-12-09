#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
private:
    // Screen size
    sf::Vector2f _screenSize;
    // Recatagle information
    sf::RectangleShape _body;
    sf::Vector2f _rectDimmesion;
    sf::Vector2f _rectPosition;

private:
public:
    Player(sf::Vector2f screenSize);
    ~Player();
    void draw(sf::RenderWindow &window);
    void move(sf::Event &event);
    sf::Vector2f getDimension() const;
    sf::Vector2f getPosition() const;

    // Getters and Setters
};

#endif