#ifndef ARKANOID_MAIN_MENU_HPP
#define ARKANOID_MAIN_MENU_HPP

#include <SFML/Graphics.hpp>

namespace arkanoid
{

class MainMenu {
public:
    MainMenu(sf::RenderWindow& window, sf::Font& font);
    void handleInput(const sf::Event& event);
    void update();
    void render();

    bool isPlaySelected() const;
    bool isQuitSelected() const;
    void initializeText(sf::Text& text, const std::string& content, unsigned int size, sf::Color color, sf::Vector2f position);

private:
    sf::RenderWindow& m_window;
    sf::Texture m_backgroundTexture;
    sf::RectangleShape m_background;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_playText;
    sf::Text m_quitText;

    bool m_playSelected;
    bool m_quitSelected;

    void setupUI();
};

}

#endif // ARKANOID_MAIN_MENU_HPP
