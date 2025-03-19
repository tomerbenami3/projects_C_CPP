#ifndef ARKANOID_BRICK_HPP
#define ARKANOID_BRICK_HPP

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Brick {

public:
    Brick(sf::Vector2f const& size, sf::Vector2f const& position, sf::Color const& color);

    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
    bool isDestroyed() const;
    void destroy();
    
private:
    sf::RectangleShape m_shape;
    bool m_destroyed;
};

} // namespace arkanoid

#endif // ARKANOID_BRICK_HPP
