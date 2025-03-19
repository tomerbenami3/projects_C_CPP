#ifndef ARKANOID_INPUT_HPP
#define ARKANOID_INPUT_HPP

#include <SFML/Window/Keyboard.hpp>

namespace arkanoid {

class Input {
public:
    
    static bool isKeyPressed(sf::Keyboard::Key key);

    static bool isLeftPressed();
    static bool isRightPressed();
};

} // namespace arkanoid

#endif // ARKANOID_INPUT_HPP
