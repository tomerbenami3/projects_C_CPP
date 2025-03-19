#ifndef ARKANOID_SOUND_MANAGER_HPP
#define ARKANOID_SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>

namespace arkanoid {


class SoundManager {
public:
    static SoundManager& getInstance();
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    void playBackgroundMusic();
    void stopBackgroundMusic();
    void setVolume(float volume);

private:
    SoundManager();
    sf::Music m_backgroundMusic;

};

}

#endif // ARKANOID_SOUND_MANAGER_HPP
