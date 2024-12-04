#include "player.h"

Player::Player() : _rectDimmesion(sf::Vector2i(100, 100))
{
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
        _body.move(-5, 0);
    }
    if (_event.key.code == sf::Keyboard::W)
    {
        _body.move(0, -5);
    }
    if (_event.key.code == sf::Keyboard::S)
    {
        _body.move(0, 5);
    }
    if (_event.key.code == sf::Keyboard::D)
    {
        _body.move(5, 0);
    }
} // Player::move()

void Player::setInitialPosition(const sf::Vector2f &begPosition)
{
    std::cout << "setInitialPosition : " << begPosition.x << begPosition.y << std::endl;
    _body.setPosition(begPosition);
} // Player::setInitialPosition();

sf::Vector2f Player::getDimension() const
{
    return _body.getSize();
}