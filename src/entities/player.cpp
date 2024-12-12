#include "player.h"

Player::Player(const sf::Vector2f &screenSize)
    : _screenSize(screenSize),
      _rectDimension(sf::Vector2f(200.0f, 200.0f)),
      _rectPosition(sf::Vector2f(static_cast<float>(screenSize.x / 2), screenSize.y - 200.0f)),
      _velocity(sf::Vector2f(static_cast<float>(_SPEED), static_cast<float>(_SPEED)))
{
    _body.setPosition(_rectPosition);
    _body.setSize(_rectDimension);
    _body.setFillColor(sf::Color::Green);
} // Player::Player

Player::~Player() {} // Player::~Player

void Player::draw(sf::RenderWindow &window)
{
    window.draw(_body);
} // PLayer::Draw

void Player::update()
{
    _checkCollisions();
} // Player::_checkCollisions

void Player::move(const sf::Event &event, const float &deltaTime)
{
    // This prevents the player from suddenly stopping once another key is pressed
    _velocity.x = 0.0f;
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
        {
            _velocity.x -= static_cast<float>(_SPEED);
            //_body.move(static_cast<float>(-_SPEED), 0.0f);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            _velocity.x += static_cast<float>(_SPEED);
            // _body.move(static_cast<float>(_SPEED), 0.0f);
        }
        else if (event.key.code == sf::Keyboard::Space)
        {
            //_jump();
            //_body.move(0.0f, static_cast<float>(-_SPEED));
        }
    }

    // Update internal position after movement
    _body.move(_velocity * deltaTime);
    _rectPosition = _body.getPosition();
} // Player::move

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
} // Player::_checkCollisions

sf::Vector2f Player::getDimension() const
{
    return _body.getSize();
} // Player::getDimension

sf::Vector2f Player::getPosition() const
{
    return _body.getPosition();
} // Player::getPosition

void Player::setPosition(const sf::Vector2f &position)
{
    _body.setPosition(position);
    _rectPosition = position;
} // Player::setPosition

void Player::setDimension(const sf::Vector2f &dimension)
{
    _body.setSize(dimension);
    _rectDimension = dimension;
} // Player::serDimension

bool Player::getGroundLevel() const
{
    return (_rectPosition.y + _rectDimension.y) == _screenSize.y;
} // Player::getGroundLevel

void Player::setGroundLevel(const bool &event)
{
    // This should either be True or False
    _isGroundLevel = event;
} // Player::setGroundLevel
