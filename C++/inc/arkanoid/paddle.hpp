#ifndef ARKANOID_PADDLE_HPP
#define ARKANOID_PADDLE_HPP

#include <SFML/Graphics.hpp>

namespace arkanoid {

class Paddle {

public:
    Paddle(sf::Vector2f const& size, sf::Vector2f const& startPosition, float speed);
    ~Paddle() = default;
    void update(float deltaTime, sf::RenderWindow const& window);

    void render(sf::RenderWindow& window) const;

    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;

private:
    sf::RectangleShape m_shape;
    float m_speed;
};

} // namespace arkanoid

#endif // ARKANOID_PADDLE_HPP
