#include "high_score_manager.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace arkanoid {

HighScoreManager::HighScoreManager(const std::string& filename)
: m_filename(filename)
{
    loadScores();
}

void HighScoreManager::loadScores()
{
    std::ifstream file(m_filename);
    if (!file) {
        std::cerr << "No high score file found, creating a new one.\n";
        return;
    }

    m_scores.clear();
    std::string name;
    int score;
    while (file >> name >> score) {
        m_scores.push_back({name, score});
    }

    sortScores();
}

void HighScoreManager::saveScores()
{
    std::ofstream file(m_filename);
    if (!file) {
        std::cerr << "Failed to save high scores!\n";
        return;
    }

    for (const auto& entry : m_scores) {
        file << entry.name << " " << entry.score << "\n";
    }
}

bool HighScoreManager::isHighScore(int score) const
{
    return (m_scores.size() < 10 || score > m_scores.back().score);
}

void HighScoreManager::addScore(const std::string& name, int score)
{
    if (!isHighScore(score)) return;

    std::string trimmedName = name.substr(0, 16);
    m_scores.push_back({trimmedName, score});
    sortScores();

    if (m_scores.size() > 10) {
        m_scores.pop_back();
    }

    saveScores();
}

std::vector<HighScoreEntry> HighScoreManager::getHighScores() const {
    return m_scores;
}

void HighScoreManager::sortScores() {
    std::sort(m_scores.begin(), m_scores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b) {
        return a.score > b.score; 
    });
}

}
