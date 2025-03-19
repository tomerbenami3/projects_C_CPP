#include "main_menu.hpp"
#include <stdexcept>

namespace arkanoid
{
MainMenu::MainMenu(sf::RenderWindow& window, sf::Font& font)
: m_window(window)
, m_font("../../../resources/PermanentMarker-Regular.ttf")
, m_backgroundTexture("../../../resources/pexels-hngstrm-1901028.jpg")
, m_playSelected(false)
, m_quitSelected(false)
, m_titleText(font)
, m_playText(font)
, m_quitText(font)
{
    m_background.setSize(static_cast<sf::Vector2f>(window.getSize()));
    m_background.setTexture(&m_backgroundTexture);

    setupUI();
}

void MainMenu::handleInput(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        const auto* keyEvent = event.getIf<sf::Event::KeyPressed>();

        if (keyEvent->scancode == sf::Keyboard::Scan::Enter) {
            m_playSelected = true;
        }
        if (keyEvent->scancode == sf::Keyboard::Scan::Escape) {
            m_quitSelected = true;
        }
    }
}

void MainMenu::update() {
    
}

void MainMenu::render() {
    m_window.clear();
    m_window.draw(m_background);
    m_window.draw(m_titleText);
    m_window.draw(m_playText);
    m_window.draw(m_quitText);
    m_window.display();
}

bool MainMenu::isPlaySelected() const {
    return m_playSelected;
}

bool MainMenu::isQuitSelected() const {
    return m_quitSelected;
}

void MainMenu::initializeText(sf::Text& text, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setFont(m_font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
}

void MainMenu::setupUI() {
    initializeText(m_titleText, "ARKANOID", 90, sf::Color::White, 
                   {m_window.getSize().x / 3.f - 100.f, 100.f});

    initializeText(m_playText, "Play", 50, sf::Color::Green, 
                   {m_window.getSize().x / 2.f - 50.f, 250.f});

    initializeText(m_quitText, "Quit", 50, sf::Color::Red, 
                   {m_window.getSize().x / 2.f - 50.f, 350.f});
}


}