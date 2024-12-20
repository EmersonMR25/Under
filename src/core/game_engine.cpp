#include "game_engine.h"

GameEngine::GameEngine()
    : _mode(sf::VideoMode::getDesktopMode()),
      _player(sf::Vector2f(static_cast<float>(_mode.width), static_cast<float>(_mode.height)))
{
    initializeWindow(_mode.width, _mode.height, "Under");
    run();
} // GameEngine::GameEngine

GameEngine::~GameEngine() {} // GameEngine::~GameEngine

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
} // GameEngine::initializeWindow

sf::Vector2u GameEngine::getWindowSize() const
{
    return _window.getSize();
} // GameEngine::getWIndowSize

sf::View GameEngine::getViewArea() const
{
    return _viewArea;
} // GameEngine::getViewArea

void GameEngine::setViewArea(const sf::View &view)
{
    _viewArea = view;
    _window.setView(_viewArea);
} // GameEngine::setViweArea

bool GameEngine::isWindowOpen() const
{
    return _window.isOpen();
} // GameEngine::isWindowOpen

Player &GameEngine::getPlayer()
{
    return _player;
} // GameEngine::getPlayer

void GameEngine::render()
{
    _window.clear();
    _player.draw(_window);
    _window.display();
} // GameEngine::render

void GameEngine::update(const float &deltaTime)
{
    _player.update(deltaTime);
} // GameEngine::update

void GameEngine::_handleEvents(const float &deltaTime)
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
                _window.close();
            }
            _player.move(_event, deltaTime);
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
} // GameEngine::_handleEvents

void GameEngine::run()
{
    sf::Clock clock;
    // Main game loop
    while (isWindowOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        _handleEvents(deltaTime);
        update(deltaTime);
        render();
    }
} // GameEngine::run
