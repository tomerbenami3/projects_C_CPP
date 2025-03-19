#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Bouncing Ball");
    window.setFramerateLimit(60);

    // Create the ball
    sf::CircleShape ball(10.f);  // Radius of 10
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(sf::Vector2f(400.f, 300.f));  // Initial position

    // Ball velocity
    sf::Vector2f velocity(5.f, 3.f);  // Initial speed (x, y)

    // Game loop
    while (window.isOpen()) {
        // Handle events
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {  // Check if the event is a "Closed" event
                window.close();
            }
        }

        // Move the ball
        ball.move(velocity);

        // Check collisions with window boundaries
        if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= 800)
            velocity.x = -velocity.x;  // Reverse X direction
        if (ball.getPosition().y <= 0 || ball.getPosition().y + ball.getRadius() * 2 >= 600)
            velocity.y = -velocity.y;  // Reverse Y direction

        // Clear the window and draw the ball
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }

    return 0;
}
