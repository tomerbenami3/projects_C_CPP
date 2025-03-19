#ifndef ARKANOID_BALL_HPP
#define ARKANOID_BALL_HPP

#include <SFML/Graphics.hpp>
#include "paddle.hpp"
#include "brick.hpp"

namespace arkanoid {

class Ball {

public:
    Ball(float radius, sf::Vector2f const& start_position, sf::Vector2f const& start_velocity);
    ~Ball() = default;
    void update(float delta_time);

    void handleCollision(sf::Vector2u const& window_size);
    void handlePaddleCollision(Paddle const& paddle);
    bool handleBottomCollision(sf::Vector2u const& windowSize);


    void render(sf::RenderWindow& window) const;

    const sf::Vector2f& getPosition() const;
    float getRadius() const;
    void resetOnPaddle(Paddle const& paddle);
    void setPosition(sf::Vector2f const& position);
    void setVelocity(sf::Vector2f const& velocity);

    bool checkCollision(Brick const& brick);
    void reflect();

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
};

} // namespace arkanoid

#endif // ARKANOID_BALL_HPP
