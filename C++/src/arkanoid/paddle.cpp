#include "paddle.hpp"
#include "input.hpp"

namespace arkanoid {

Paddle::Paddle(sf::Vector2f const& size, sf::Vector2f const& startPosition, float speed)
: m_shape(size)
, m_speed(speed)
{
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setPosition(startPosition);
}

void Paddle::update(float deltaTime, sf::RenderWindow const& window)
{
    if (Input::isLeftPressed()) {
        m_shape.move(sf::Vector2f(-m_speed * deltaTime, 0.f));
    }
    if (Input::isRightPressed()) {
        m_shape.move(sf::Vector2f(m_speed * deltaTime, 0.f));
    }

    sf::Vector2f position = m_shape.getPosition();
    sf::Vector2f size = m_shape.getSize();
    if (position.x < 0) {
        m_shape.setPosition(sf::Vector2f(0.f, position.y));
    } else if (position.x + size.x > window.getSize().x) {
        m_shape.setPosition(sf::Vector2f(window.getSize().x - size.x, position.y));
    }
}

void Paddle::render(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

const sf::Vector2f& Paddle::getPosition() const
{
    return m_shape.getPosition();
}

const sf::Vector2f& Paddle::getSize() const 
{
    return m_shape.getSize();
}

} // namespace arkanoid
