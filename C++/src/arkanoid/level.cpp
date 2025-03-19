#include "level.hpp"
#include "brick.hpp"
#include "high_score_manager.hpp"
#include "high_score_screen.hpp"
#include "topten_screen.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace arkanoid {

Level::Level(sf::Vector2u const& windowSize, sf::Font& font)
: m_ball(10.f, {400.f, 300.f}, {200.f, 150.f})
, m_paddle({100.f, 20.f}, {windowSize.x / 2.f - 50.f, windowSize.y - 50.f}, 300.f)
, m_waitingforLaunch(true)
, m_hasWon(false)
, m_lives(3)
, m_score(0)
, m_livesText(font)
, m_scoreText(font)
, m_winText(font)
, m_font(font)
, m_hasLost(false)
, m_gameOverText(font)
, m_highScoreManager("high_scores.txt")
 {

    setupUI(windowSize);
    restartLevel();

}

void Level::update(float deltaTime, sf::RenderWindow& window)
{   
    if (m_hasLost) {
        if (m_gameOverClock.getElapsedTime().asSeconds() > 20) {
            window.close();
        }
        return;
    }

    if (m_lives <= 0) {
        m_hasLost = true;
        m_gameOverClock.restart();
        return;
    }

    if (m_hasWon) {
        if (m_winClock.getElapsedTime().asSeconds() > 5) {
            enterHighScore(window);
            restartLevel();
        }
        return;
    }

    if (areAllBricksDestroyed()) {
        m_hasWon = true;
        m_winClock.restart();
        return;
    }


    if(m_waitingforLaunch) {
        m_ball.resetOnPaddle(m_paddle);
    } else {
        m_ball.update(deltaTime);
        m_ball.handleCollision(window.getSize());
        m_ball.handlePaddleCollision(m_paddle);
        
        if(m_ball.handleBottomCollision(window.getSize())) {
            --m_lives;
            m_livesText.setString("Lives: " + std::to_string(m_lives));
            m_waitingforLaunch = true;
            return;
        }

        for (Brick& brick : m_bricks) {
            if (!brick.isDestroyed() && m_ball.checkCollision(brick)) {
                brick.destroy();
                m_score += 40;
                m_scoreText.setString("Score: " + std::to_string(m_score));
                m_ball.reflect();
                break;
            }
        }
    }

    m_paddle.update(deltaTime, window);
}

void Level::restartLevel() {
    m_hasWon = false;
    m_waitingforLaunch = true;
    m_lives = 3;
    m_score = 0;
    m_winClock.restart(); 

    m_ball.resetOnPaddle(m_paddle);

    m_bricks.clear();
    const sf::Vector2f brickSize(80.f, 20.f);
    const float spacing = 10.f;
    const sf::Vector2f gridOffset(100.f, 50.f);
    const std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::White, sf::Color::Green};

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 5; ++col) {
            float x = gridOffset.x + col * (brickSize.x + spacing);
            float y = gridOffset.y + row * (brickSize.y + spacing);
            m_bricks.emplace_back(brickSize, sf::Vector2f(x, y), colors[row]);
        }
    }

    m_livesText.setString("Lives: " + std::to_string(m_lives));
    m_scoreText.setString("Score: " + std::to_string(m_score));
}


bool Level::areAllBricksDestroyed() const {
    for (const Brick& brick : m_bricks) {
        if (!brick.isDestroyed()) {
            return false;
        }
    }
    return true;
}

void Level::render(sf::RenderWindow& window) const {

    window.draw(m_livesText);
    window.draw(m_scoreText);

    if (m_hasLost) {
        window.draw(m_gameOverText);
    } else if (m_hasWon) {
        window.draw(m_winText);
    } else {
        m_ball.render(window);
        m_paddle.render(window);

        for (const Brick& brick : m_bricks) {
            brick.render(window);
        }
    }
}

void Level::initializeText(sf::Text& text, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setFont(m_font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
}

void Level::setupUI(sf::Vector2u const& windowSize) {

    initializeText(m_livesText, "Lives: " + std::to_string(m_lives), 25, sf::Color::White,
                   {windowSize.x - 120.f, 10.f});

    initializeText(m_scoreText, "Score: " + std::to_string(m_score), 25, sf::Color::White,
                   {10.f, 10.f});

    sf::FloatRect winBounds = m_winText.getGlobalBounds();
    initializeText(m_winText, "You Won!", 70, sf::Color::Yellow,
                   {windowSize.x / 4.f - winBounds.size.x / 2.f, windowSize.y / 2.f - winBounds.size.y / 2.f});

    sf::FloatRect lostBounds = m_gameOverText.getGlobalBounds();
    initializeText(m_gameOverText, "Game Over", 70, sf::Color::Red,
                   {windowSize.x / 4.f - lostBounds.size.x / 2.f, windowSize.y / 2.f - lostBounds.size.y / 2.f});
}

bool Level::isWaitingForLaunch() const {
    return m_waitingforLaunch;
}

void Level::launchBall() {
    if (m_waitingforLaunch) {
        m_waitingforLaunch = false;
        m_ball.setVelocity({200, -300});
    }
}

void Level::checkHighScore(sf::RenderWindow& window) {
    if (m_highScoreManager.isHighScore(m_score)) {
        HighScoreScreen entryScreen(window, m_font, m_score);
        std::string playerName = entryScreen.getPlayerName();
        
        if (!playerName.empty()) {
            m_highScoreManager.addScore(playerName, m_score);
            m_showHighScores = true;
        }
    }
}

void Level::enterHighScore(sf::RenderWindow& window) {
    if (m_highScoreManager.isHighScore(m_score)) {
        HighScoreScreen entryScreen(window, m_font, m_score);
        std::string playerName = entryScreen.getPlayerName();
        if (!playerName.empty()) {
            m_highScoreManager.addScore(playerName, m_score);
            m_showHighScores = true;
        }
    }
}

bool Level::hasPlayerWon() const
{
    return m_showHighScores;
}


} // namespace arkanoid
