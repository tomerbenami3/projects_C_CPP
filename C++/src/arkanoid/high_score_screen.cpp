#include "high_score_screen.hpp"
#include <SFML/Window/Event.hpp>

namespace arkanoid {


HighScoreScreen::HighScoreScreen(sf::RenderWindow& window, sf::Font& font, int score)
: m_window(window)
, m_font(font)
, m_playerName("") 
, m_promptText(font)
, m_nameText(font)
{

    m_promptText.setFont(m_font);
    m_promptText.setString("You got a High Score!\nEnter your name:");
    m_promptText.setCharacterSize(30);
    m_promptText.setFillColor(sf::Color::White);
    m_promptText.setPosition({100.f, 200.f});

    m_nameText.setFont(m_font);
    m_nameText.setCharacterSize(40);
    m_nameText.setFillColor(sf::Color::Yellow);
    m_nameText.setPosition({100.f, 300.f});
}

std::string HighScoreScreen::getPlayerName() 
{
    while (m_window.isOpen()) {
        while (auto event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
                return "";
            }

            if (event->is<sf::Event::TextEntered>()) {
                const auto* textEvent = event->getIf<sf::Event::TextEntered>(); 
                if (textEvent) {
                    if (textEvent->unicode == '\b' && !m_playerName.empty()) {
                        m_playerName.pop_back();
                    } else if (textEvent->unicode == '\r' || textEvent->unicode == '\n') {
                        return m_playerName;
                    } else if (m_playerName.size() < 16) {
                        m_playerName += static_cast<char>(textEvent->unicode);
                    }

                    m_nameText.setString(m_playerName);
                }
            }
        }

        m_window.clear();
        m_window.draw(m_promptText);
        m_window.draw(m_nameText);
        m_window.display();
    }

    return "";
}



}
