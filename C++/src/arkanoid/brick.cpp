#include "brick.hpp"

namespace arkanoid {

Brick::Brick(sf::Vector2f const& size, sf::Vector2f const& position, sf::Color const& color)
: m_destroyed(false) 
{
    m_shape.setSize(size);
    m_shape.setFillColor(color);
    m_shape.setPosition(position);
}

void Brick::update(float deltaTime) {
}

void Brick::render(sf::RenderWindow& window) const 
{
    if (!m_destroyed) {
        window.draw(m_shape);
    }
}

const sf::Vector2f& Brick::getPosition() const 
{
    return m_shape.getPosition();
}

const sf::Vector2f& Brick::getSize() const 
{
    return m_shape.getSize();
}

bool Brick::isDestroyed() const 
{
    return m_destroyed;
}

void Brick::destroy() 
{
    m_destroyed = true;
}


} // namespace arkanoid
