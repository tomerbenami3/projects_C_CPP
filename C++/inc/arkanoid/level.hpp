#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.hpp"
#include "brick.hpp"
#include "paddle.hpp"
#include "high_score_manager.hpp"
#include "high_score_screen.hpp"

namespace arkanoid {

class Level {

public:
    Level(sf::Vector2u const& windowSize, sf::Font& font);

    void update(float deltaTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window) const;
    bool areAllBricksDestroyed() const;
    void restartLevel();
    void initializeText(sf::Text& text, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position);
    void setupUI(sf::Vector2u const& windowSize);
    bool isWaitingForLaunch() const;
    void launchBall();
    void checkHighScore(sf::RenderWindow& window);
    void enterHighScore(sf::RenderWindow& window);
    bool hasPlayerWon() const;

private:
    Ball m_ball;
    Paddle m_paddle;
    std::vector<Brick> m_bricks;
    bool m_waitingforLaunch;
    bool m_hasWon;
    int m_lives;
    int m_score;
    sf::Text m_livesText;
    sf::Text m_scoreText;
    sf::Text m_winText;
    sf::Font& m_font;
    bool m_hasLost;
    sf::Text m_gameOverText;
    sf::Clock m_gameOverClock;
    sf::Clock m_winClock;
    HighScoreManager m_highScoreManager;
    bool m_showHighScores = false;
    
};

} // namespace arkanoid

#endif // LEVEL_HPP
