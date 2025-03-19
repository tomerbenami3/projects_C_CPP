#include "input.hpp"

namespace arkanoid {

bool Input::isKeyPressed(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

bool Input::isLeftPressed() {
    return isKeyPressed(sf::Keyboard::Key::Left);
}

bool Input::isRightPressed() {
    return isKeyPressed(sf::Keyboard::Key::Right);
}

} // namespace arkanoid
