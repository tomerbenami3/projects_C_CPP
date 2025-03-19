#include "sound_manager.hpp"
#include <iostream>

namespace arkanoid {

SoundManager::SoundManager() {
    if (!m_backgroundMusic.openFromFile("../../../resources/basbusaday.wav")) {
        std::cerr << "Failed to load background music!\n";
    }
    m_backgroundMusic.setLooping(true);
}

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::playBackgroundMusic() {
    // if (m_backgroundMusic.getStatus() != sf::SoundStatus::Playing) {
        m_backgroundMusic.play();
    // }
}

void SoundManager::stopBackgroundMusic() {
    m_backgroundMusic.stop();
}

void SoundManager::setVolume(float volume) {
    m_backgroundMusic.setVolume(volume);
}

}
