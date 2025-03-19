#ifndef ARKANOID_GAME_HPP
#define ARKANOID_GAME_HPP

#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "paddle.hpp"
#include "level.hpp"

namespace arkanoid {

class Game {
public:
    Game(unsigned int width, unsigned int height, std::string const& title, sf::Font& font);
    ~Game() = default;
    void run();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Level m_level;
    sf::Font m_font;
    bool m_isPaused = false;
    bool m_returnToMenu = false;
    bool m_hasStarted = false;
    bool m_showHighScores = false;
    HighScoreManager m_highScoreManager;

    void processEvents();
    void update(float deltaTime);
    void render();

};

} // namespace arkanoid

#endif // ARKANOID_GAME_HPP
