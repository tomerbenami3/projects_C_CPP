#ifndef ARKANOID_GAME_OBJECT_HPP
#define ARKANOID_GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

namespace arkanoid {

class GameObject {
protected:
    sf::Vector2f m_position; // Position of the object
    sf::Vector2f m_size;     // Size of the object

public:
    virtual ~GameObject() = default;

    virtual void update(float deltaTime) = 0;

    virtual void render(sf::RenderWindow& window) const = 0;

    const sf::Vector2f& getPosition() const { return m_position; }
    const sf::Vector2f& getSize() const { return m_size; }

    void setPosition(const sf::Vector2f& position) { m_position = position; }
};

} // namespace arkanoid

#endif // ARKANOID_GAME_OBJECT_HPP
