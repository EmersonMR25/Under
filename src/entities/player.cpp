#include "player.h"

Player::Player(const sf::Vector2f &screenSize)
    : _screenSize(screenSize),
      _rectDimension(sf::Vector2f(200.0f, 200.0f)),
      _rectPosition(sf::Vector2f(static_cast<float>(screenSize.x / 2), screenSize.y - 200.0f)),
      _speed(sf::Vector2f(0.0f, 0.0f)),
      _isGroundLevel(true),
      _acceleration(0.0f, 0.0f)
{
    _body.setPosition(_rectPosition);
    _body.setSize(_rectDimension);
    _body.setFillColor(sf::Color::Green);
} // Player::Player

Player::~Player() {} // Player::~Player

void Player::draw(sf::RenderWindow &window)
{
    window.draw(_body);
} // Player::draw

void Player::update(const float &deltaTime)
{
    if (!_isGroundLevel)
    {
        _jump(deltaTime);
    }
    else
    {
        _speed.x = 0.0f; // Reset horizontal speed when grounded
    }

    _checkCollisions();
    _body.setPosition(_rectPosition);
} // Player::update

void Player::move(const sf::Event &event, const float &deltaTime)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A && !_isGroundLevel)
        {
            _speed.x = -_SPEED;
        }
        else if (event.key.code == sf::Keyboard::D && !_isGroundLevel)
        {
            _speed.x = _SPEED;
        }
        else if (event.key.code == sf::Keyboard::Space && _isGroundLevel)
        {
            _isGroundLevel = false;
            _acceleration.y = -_JUMP_STRENGTH;
        }
    }

    // Update horizontal position for ground movement
    if (_isGroundLevel)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
        {
            _body.move(-_SPEED * deltaTime, 0.0f);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
        {
            _body.move(_SPEED * deltaTime, 0.0f);
        }
    }

    _rectPosition = _body.getPosition();
} // Player::move

void Player::_jump(const float &deltaTime)
{
    // Update velocity with acceleration (Verlet integration)
    _speed += _acceleration * deltaTime;

    // Update position with velocity
    _rectPosition += _speed * deltaTime;

    // Apply gravity
    _acceleration.y += _GRAVITY * deltaTime;

    // Adjust horizontal position based on directional input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _speed.x = -_SPEED;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _speed.x = _SPEED;
    }
    else
    {
        _speed.x = 0.0f;
    }

    _body.setPosition(_rectPosition);
} // Player::_jump

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
    {
        position.y = _screenSize.y - _rectDimension.y;
        _isGroundLevel = true;
        _acceleration.y = 0.0f;
        _speed.y = 0.0f;
    }

    _body.setPosition(position);
    _rectPosition = position;
} // Player::_checkCollisions

sf::Vector2f Player::_newAcceleration(const sf::Vector2f &oldAcceleration, const float &deltaTime)
{
    sf::Vector2f newAcceleration = oldAcceleration;
    newAcceleration.y += _GRAVITY * deltaTime;
    return newAcceleration;
} // Player::_newAcceleration
