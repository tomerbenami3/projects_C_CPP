#include "topten_screen.hpp"
#include <sstream>

namespace arkanoid {

TopTenScreen::TopTenScreen(sf::RenderWindow& window, sf::Font& font, const HighScoreManager& scoreManager)
: m_window(window)
, m_font(font)
, m_titleText(font)
, m_scoreManager(scoreManager)
{
    setupUI();
}

void TopTenScreen::setupUI() {
    m_titleText.setFont(m_font);
    m_titleText.setString("Top 10 High Scores");
    m_titleText.setCharacterSize(50);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setPosition({200.f, 50.f});

    std::vector<HighScoreEntry> scores = m_scoreManager.getHighScores();
    for (size_t i = 0; i < scores.size() && i < 10; ++i) {
        sf::Text text(m_font);
        text.setFont(m_font);
        std::stringstream ss;
        ss << (i + 1) << ". " << scores[i].name << " - " << scores[i].score;
        text.setString(ss.str());
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition({250.f, 120.f + (i * 40.f)});
        m_scoreTexts.push_back(text);
    }
}

void TopTenScreen::display() {
    while (m_window.isOpen()) {
        while (auto event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }
            if (event->is<sf::Event::KeyPressed>()) {
                return;
            }
        }

        m_window.clear();
        m_window.draw(m_titleText);
        for (const auto& text : m_scoreTexts) {
            m_window.draw(text);
        }
        m_window.display();
    }
}

}
