#include "ball.hpp"
#include "brick.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


namespace arkanoid
{

Ball::Ball(float radius, sf::Vector2f const& start_position, sf::Vector2f const& start_velocity)
: m_shape(radius)
, m_velocity(start_velocity)
{
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(start_position);
}

void Ball::update(float deltaTime)
{
    m_shape.move(m_velocity * deltaTime);
}

void Ball::handleCollision(sf::Vector2u const& windowSize)
{
    sf::Vector2f position = m_shape.getPosition();
    float radius = m_shape.getRadius();

    if (position.x <= 0 || position.x + 2 * radius >= windowSize.x) {
        m_velocity.x = -m_velocity.x;
    }

    if (position.y <= 0 || position.y + 2 * radius >= windowSize.y) {
        m_velocity.y = -m_velocity.y;
    }
}

void Ball::handlePaddleCollision(Paddle const& paddle)
{
    sf::Vector2f ballPosition = m_shape.getPosition();
    float radius = m_shape.getRadius();

    sf::Vector2f paddlePosition = paddle.getPosition();
    sf::Vector2f paddleSize = paddle.getSize();

    bool collisionX = ballPosition.x + 2 * radius >= paddlePosition.x &&
                      ballPosition.x <= paddlePosition.x + paddleSize.x;
    bool collisionY = ballPosition.y + 2 * radius >= paddlePosition.y &&
                      ballPosition.y <= paddlePosition.y + paddleSize.y;

    if (collisionX && collisionY) {
        m_velocity.y = -std::abs(m_velocity.y);

        float paddleCenter = paddlePosition.x + paddleSize.x / 2.f;
        float ballCenter = ballPosition.x + radius;
        float offset = (ballCenter - paddleCenter) / (paddleSize.x / 2.f);

        m_velocity.x = offset * 300.f;
    }
}

void Ball::render(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

const sf::Vector2f& Ball::getPosition() const
{
    return m_shape.getPosition();
}

float Ball::getRadius() const
{
    return m_shape.getRadius();
}

void Ball::resetOnPaddle(Paddle const& paddle)
{
    sf::Vector2f paddlePosition = paddle.getPosition();
    sf::Vector2f paddleSize = paddle.getSize();

    m_shape.setPosition(sf::Vector2f(
        paddlePosition.x + paddleSize.x / 2.f - m_shape.getRadius(),
        paddlePosition.y - 2 * m_shape.getRadius()
    ));

    m_velocity = {0.f, 0.f};
}


void Ball::setPosition(sf::Vector2f const& position)
{
    m_shape.setPosition(position);
}

void Ball::setVelocity(sf::Vector2f const& velocity)
{
    m_velocity = velocity;
}

bool Ball::checkCollision(Brick const& brick)
{
    sf::Vector2f ballPosition = m_shape.getPosition();
    float radius = m_shape.getRadius();

    sf::Vector2f brickPosition = brick.getPosition();
    sf::Vector2f brickSize = brick.getSize();

    bool collisionX = ballPosition.x + 2 * radius >= brickPosition.x &&
                      ballPosition.x <= brickPosition.x + brickSize.x;
    bool collisionY = ballPosition.y + 2 * radius >= brickPosition.y &&
                      ballPosition.y <= brickPosition.y + brickSize.y;

    return collisionX && collisionY;
}

bool Ball::handleBottomCollision(sf::Vector2u const& windowSize)
{
    sf::Vector2f position = m_shape.getPosition();
    float radius = m_shape.getRadius();

    if (position.y + 2 * radius >= windowSize.y) {
        return true;
    }
}

void Ball::reflect()
{
    m_velocity.y = -m_velocity.y;
    m_velocity.x += (rand() % 20 - 10);
}

} // namespace arkanoid
