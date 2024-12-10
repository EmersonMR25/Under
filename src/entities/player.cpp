#include "player.h"

Player::Player(sf::Vector2f screenSize)
    : _screenSize(screenSize),
      _rectDimension(sf::Vector2f(200.0f, 200.0f)),
      _rectPosition(sf::Vector2f(static_cast<float>(screenSize.x / 2), screenSize.y - 200.0f))
{
    _body.setPosition(_rectPosition);
    _body.setSize(_rectDimension);
    _body.setFillColor(sf::Color::Green);
}

Player::~Player() {}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(_body);
}

void Player::update()
{
    _checkCollisions();
}

void Player::move(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
        {
            _body.move(-10.0f, 0.0f);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            _body.move(10.0f, 0.0f);
        }
        else if (event.key.code == sf::Keyboard::W)
        {
            _body.move(0.0f, -10.0f);
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            _body.move(0.0f, 10.0f);
        }
    }

    // Update internal position after movement
    _rectPosition = _body.getPosition();
}

void Player::_checkCollisions()
{
    sf::Vector2f position = _body.getPosition();

    // Constrain within screen boundaries
    if (position.x < 0)
        position.x = 0;
    if (position.y < 0)
        position.y = 0;
    if (position.x + _rectDimension.x > _screenSize.x)
        position.x = _screenSize.x - _rectDimension.x;
    if (position.y + _rectDimension.y > _screenSize.y)
        position.y = _screenSize.y - _rectDimension.y;

    _body.setPosition(position);
}

sf::Vector2f Player::getDimension() const
{
    return _body.getSize();
}

sf::Vector2f Player::getPosition() const
{
    return _body.getPosition();
}

void Player::setPosition(const sf::Vector2f &position)
{
    _body.setPosition(position);
    _rectPosition = position;
}

void Player::setDimension(const sf::Vector2f &dimension)
{
    _body.setSize(dimension);
    _rectDimension = dimension;
}
