#ifndef ARKANOID_HIGH_SCORE_ENTRY_SCREEN_HPP
#define ARKANOID_HIGH_SCORE_ENTRY_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace arkanoid {

class HighScoreScreen {
public:
    HighScoreScreen(sf::RenderWindow& window, sf::Font& font, int score);
    std::string getPlayerName();

private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;
    sf::Text m_promptText;
    sf::Text m_nameText;
    std::string m_playerName;
};

}

#endif // ARKANOID_HIGH_SCORE_ENTRY_SCREEN_HPP
