#include "game_engine.h"

GameEngine::GameEngine()
    : _mode(sf::VideoMode::getDesktopMode()),
      _player(sf::Vector2f(static_cast<float>(_mode.width), static_cast<float>(_mode.height)))
{
    // Initialize the game window with default settings
    initializeWindow(_mode.width, _mode.height, "Under");
    this->run();
}

GameEngine::~GameEngine() {} // Destructor

void GameEngine::initializeWindow(unsigned int width, unsigned int height, const std::string &title)
{
    // Configure antialiasing settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create the window
    _window.create(sf::VideoMode(width, height), title, sf::Style::Fullscreen, settings);

    // Set up the default view area
    _viewArea = _window.getDefaultView();

    // Limit the frame rate
    _window.setFramerateLimit(120);
}

sf::Vector2u GameEngine::getWindowSize() const
{
    return _window.getSize();
}

sf::View GameEngine::getViewArea() const
{
    return _viewArea;
}

void GameEngine::setViewArea(const sf::View &view)
{
    _viewArea = view;
    _window.setView(_viewArea);
}

bool GameEngine::isWindowOpen() const
{
    return _window.isOpen();
}

Player &GameEngine::getPlayer()
{
    return _player;
}

void GameEngine::render()
{
    _window.clear();       // Clear the window
    _player.draw(_window); // Render the player
    _window.display();     // Display the frame
}

void GameEngine::update()
{
    _player.update(); // Update the player state
}

void GameEngine::_handleEvents()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
        {
            _window.close();
        }
        else if (_event.type == sf::Event::KeyPressed)
        {
            if (_event.key.code == sf::Keyboard::Escape)
            {
                _window.close(); // Exit if Escape is pressed
            }
            _player.move(_event); // Handle player movement
        }
        else if (_event.type == sf::Event::Resized)
        {
            _viewArea.setSize(
                static_cast<float>(_event.size.width),
                static_cast<float>(_event.size.height));
            _window.setSize(
                sf::Vector2u(_event.size.width, _event.size.height));
            _window.setView(_viewArea);
        }
    }
}

void GameEngine::run()
{
    // Main game loop
    while (isWindowOpen())
    {
        _handleEvents(); // Handle all events
        update();        // Update the game state
        render();        // Render the game frame
    }
}
