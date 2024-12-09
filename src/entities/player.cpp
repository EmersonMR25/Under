#include "player.h"

Player::Player(sf::Vector2f screenSize) : _screenSize(screenSize),
                                          _rectDimmesion(sf::Vector2f(200.0f, 200.0f)),
                                          _rectPosition(sf::Vector2f(static_cast<float>(screenSize.x / 2), (screenSize.y - _rectDimmesion.y)))
{
    std::cout << "Y resolution: " << screenSize.y << std::endl;
    this->_body.setPosition(_rectPosition);
    this->_body.setSize(_rectDimmesion);
    // this->_body.setPosition(sf::Vector2f(0.0f, 1080.0f));
    this->_body.setFillColor(sf::Color::Green);
} // Player::Player()

Player::~Player() {} // Player::~Player()

void Player::draw(sf::RenderWindow &window)
{
    window.draw(_body);
} // Player::draw()

void Player::move(sf::Event &_event)
{
    if (_event.key.code == sf::Keyboard::A)
    {
        _body.move(-10, 0);
    }
    if (_event.key.code == sf::Keyboard::W)
    {
        _body.move(0, -10);
    }
    if (_event.key.code == sf::Keyboard::S)
    {
        _body.move(0, 10);
    }
    if (_event.key.code == sf::Keyboard::D)
    {
        _body.move(10, 0);
    }
} // Player::move()

sf::Vector2f Player::getDimension() const
{
    return _body.getSize();
}

sf::Vector2f Player::getPosition() const
{
    return _body.getPosition();
}