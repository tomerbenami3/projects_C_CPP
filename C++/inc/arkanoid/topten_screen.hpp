#ifndef TOP_TEN_SCREEN_HPP
#define TOP_TEN_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "high_score_manager.hpp"

namespace arkanoid {

class TopTenScreen {
public:
    TopTenScreen(sf::RenderWindow& window, sf::Font& font, const HighScoreManager& scoreManager);
    void display();
    void setupUI();

private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;
    const HighScoreManager& m_scoreManager;
    sf::Text m_titleText;
    std::vector<sf::Text> m_scoreTexts;

};

}

#endif // TOP_TEN_SCREEN_HPP
