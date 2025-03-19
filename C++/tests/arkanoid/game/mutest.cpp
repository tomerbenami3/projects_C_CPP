#include "mu_test.h"
#include <SFML/Graphics.hpp>
#include "game.hpp"

BEGIN_TEST(open_window)

    sf::Font font;
    if (!font.openFromFile("../../../resources/PermanentMarker-Regular.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // while (1) {
        arkanoid::Game game(800, 600, "Hapoel Yavneee\n", font);
        game.run();
    // }

END_TEST


BEGIN_SUITE(arkanoid tests)
    TEST(open_window)

END_SUITE

