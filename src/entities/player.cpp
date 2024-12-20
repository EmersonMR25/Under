#include "player.h"

Player::Player(const sf::Vector2f &screenSize)
    : _screenSize(screenSize),
      _rectDimension(sf::Vector2f(200.0f, 200.0f)),
      _rectPosition(sf::Vector2f(static_cast<float>(screenSize.x / 2), screenSize.y - 200.0f)),
      _speed(sf::Vector2f(static_cast<float>(_SPEED), static_cast<float>(_SPEED))),
      _isGroundLevel(true), // Change this once level mangr is implemenated bc it will be false
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
} // PLayer::Draw

void Player::update(const float &deltaTime)
{
    if (!_isGroundLevel)
    {
        _jump(deltaTime);
    }
    _checkCollisions();
    _body.setPosition(_rectPosition);
} // Player::_checkCollisions

void Player::move(const sf::Event &event, const float &deltaTime)
{
    // This prevents the player from suddenly stopping once another key is pressed
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::A)
        {
            _body.move(-1 * _speed.x * deltaTime, 0.0f);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            _body.move(1 * _speed.x * deltaTime, 0.0f);
        }
        else if (event.key.code == sf::Keyboard::Space && _isGroundLevel)
        {
            _isGroundLevel = false;
            _acceleration.y = -_JUMP_STRENGTH;
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            _body.move(0.0f, 1 * _GRAVITY * deltaTime);
        }
    }

    // Update internal position after movement
    //_body.move(_rectPosition);
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
    // Check if player is on the ground because we want to jump again
    if (position.y == _screenSize.y - _rectDimension.y)
    {
        _isGroundLevel = true;
        _acceleration.y = 0.0f;
        _speed.y = 0.0f;
    }
    // Once the body collides with the boundaries, they will update.
    // There are separeate functions than the setPosition from the move() function
    _body.setPosition(position);
    _rectPosition = position;
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

void Player::_jump(const float &deltaTime)
{
    sf::Vector2f newAcceleration = _newAcceleration(_acceleration, deltaTime);
    sf::Vector2f newSpeed = _speed + 0.5f * (_acceleration + newAcceleration) * deltaTime;
    _rectPosition += newSpeed * deltaTime + 0.5f * _acceleration * deltaTime * deltaTime;
    _speed = newSpeed;
    _acceleration = newAcceleration;
    _body.setPosition(_rectPosition);
} // PLayer::_jump()

sf::Vector2f Player::_newAcceleration(const sf::Vector2f &oldAcceleration, const float &deltaTime)
{
    sf::Vector2f newAcceleration = oldAcceleration;
    newAcceleration.y += _GRAVITY * deltaTime;
    return newAcceleration;
} // Player::_newAcceleration()