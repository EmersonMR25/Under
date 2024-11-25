#include "game_engine.h"

GameEngine::GameEngine() : _mode(sf::VideoMode::getDesktopMode())
{
    // Set settings for antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    this->_window.create(_mode, "Under", sf::Style::Default, settings);
    _viewArea = _window.getDefaultView();
    this->_window.setFramerateLimit(120);

    // Load the font settings
    _loadFont();
    while (this->_window.isOpen())
    {
        std::cout << "Resolution: " << this->_window.getSize().x << "," << this->_window.getSize().y << std::endl;
        _handleEvents();
        this->_window.clear();
        this->_window.draw(this->_text);
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

bool GameEngine::_loadFont()
{
    if (!this->_font.loadFromFile("../assets/fonts/super.ttf"))
    {
        std::cout << "Error: Could not load font!" << std::endl;
        return false;
    }
    this->_text.setFont(this->_font);
    this->_text.setString("Hello, world!");
    this->_text.setCharacterSize(50);
    this->_text.setFillColor(sf::Color::Red);
    this->_text.setPosition(10, 10);
    std::cout << "Font loaded successfully!" << std::endl;
    return true;
}