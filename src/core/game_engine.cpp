#include "game_engine.h"

GameEngine::GameEngine()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    _window.create(sf::VideoMode(500.0f, 500.0f), "Under", sf::Style::Default, settings);
    _window.setFramerateLimit(120);

    while (_window.isOpen())
    {
        _handleEvents();
        _window.clear();
        _window.display();
    }
} // GameEngine::GameEngine()

GameEngine::~GameEngine() {} // Game::~Game()

void GameEngine::_handleEvents()
{
    while (_window.pollEvent(this->_event))
    {
        if (this->_event.type == sf::Event::Closed)
            _window.close();
        if (this->_event.type == sf::Event::KeyPressed)
        {
            if (this->_event.key.code == sf::Keyboard::Escape)
            {
                _window.close();
            }
        }
    }
} // GameEngine::_handleEvents()