#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
private:
    sf::RectangleShape _body;
    sf::Vector2f _rectDimmesion;
    sf::Vector2f _rectPosition;

private:
public:
    Player();
    ~Player();
    void draw(sf::RenderWindow &window);
    void move(sf::Event &event);
    void setInitialPosition(const sf::Vector2f &begPosition);
    sf::Vector2f getDimension() const;
    sf::Vector2f getPosition() const;

    // Getters and Setters
};

#endif