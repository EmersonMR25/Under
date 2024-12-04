#include "game_engine.h"

GameEngine::GameEngine() : _mode(sf::VideoMode::getDesktopMode())
{
    // Set settings for antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->_window.create(_mode, "Under", sf::Style::Default, settings);
    _viewArea = _window.getDefaultView();
    this->_window.setFramerateLimit(120);

    while (this->_window.isOpen())
    {
        std::cout << "Resolution: " << this->_window.getSize().x << "," << this->_window.getSize().y << std::endl;
        _handleEvents();
        this->_window.clear();
        this->_window.display();
    }
} // GameEngine::GameEngine()

GameEngine::~GameEngine() {} // Game::~Game()

void GameEngine::_handleEvents()
{
    while (this->_window.pollEvent(this->_event))
    {
        if (this->_event.type == sf::Event::Closed)
            _window.close();
        if (this->_event.type == sf::Event::KeyPressed)
        {
            if (this->_event.key.code == sf::Keyboard::Escape)
            {
                this->_window.close();
            }
        }
        if (this->_event.type == sf::Event::Resized)
        {
            _viewArea.setSize({static_cast<float>(_event.size.width),
                               static_cast<float>(_event.size.height)});
            _window.setSize(sf::Vector2u(this->_event.size.width, this->_event.size.height));
            _window.setView(_viewArea);
        }
    }
} // GameEngine::_handleEvents()