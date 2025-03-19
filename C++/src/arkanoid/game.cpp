#include "game.hpp"
#include "sound_manager.hpp"
#include "main_menu.hpp"
#include "topten_screen.hpp"

namespace arkanoid {

Game::Game(unsigned int width, unsigned int height, std::string const& title, sf::Font& font)
: m_window(sf::VideoMode(sf::Vector2u(width, height)), title)
, m_level(m_window.getSize(), font)
, m_highScoreManager("high_scores.txt")
{
    // m_window.setFramerateLimit(60);
}

void Game::run() {
    SoundManager::getInstance().playBackgroundMusic();
    MainMenu mainMenu(m_window, m_font);

    while (m_window.isOpen()) {
        while (auto event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                SoundManager::getInstance().stopBackgroundMusic();
                m_window.close();
            }
            mainMenu.handleInput(*event);
        }

        if (mainMenu.isPlaySelected()) {
            break;
        }

        if (mainMenu.isQuitSelected()) {
            SoundManager::getInstance().stopBackgroundMusic();
            m_window.close();
            return;
        }

        mainMenu.update();
        mainMenu.render();
    }

    if (m_showHighScores) {
            TopTenScreen topTenScreen(m_window, m_font, m_highScoreManager);
            topTenScreen.display();
            m_showHighScores = false;
    }

    while (m_window.isOpen()) {
        
        if(m_returnToMenu) {
            return;
        }

        float deltaTime = m_clock.restart().asSeconds();

        processEvents();

        if(!m_isPaused) {
            update(deltaTime);
        }

        render();
    }
}

void Game::processEvents() {
    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (event->is<sf::Event::KeyPressed>()) {
            const auto* keyEvent = event->getIf<sf::Event::KeyPressed>();

            if (keyEvent->scancode == sf::Keyboard::Scan::Escape) {
                m_returnToMenu = true;
            }
            if (keyEvent->scancode == sf::Keyboard::Scan::Space) {
                if (m_level.isWaitingForLaunch()) { 
                    m_level.launchBall(); 
                } else {
                    m_isPaused = !m_isPaused;
                }
            }
        }
    }
}

void Game::update(float deltaTime) {
    m_level.update(deltaTime, m_window);

    if (m_level.hasPlayerWon()) {
        m_showHighScores = true;
    }
}

void Game::render() {
    m_window.clear(sf::Color::Black);

    m_level.render(m_window);

    m_window.display();
}

} // namespace arkanoid
