#ifndef ARKANOID_HIGH_SCORE_MANAGER_HPP
#define ARKANOID_HIGH_SCORE_MANAGER_HPP

#include <vector>
#include <string>

namespace arkanoid {

struct HighScoreEntry {
    std::string name;
    int score;
};

class HighScoreManager {
public:
    HighScoreManager(const std::string& filename);
    
    void loadScores();
    void saveScores();
    bool isHighScore(int score) const;
    void addScore(const std::string& name, int score);
    std::vector<HighScoreEntry> getHighScores() const;

private:
    std::string m_filename;
    std::vector<HighScoreEntry> m_scores;

    void sortScores();
};

}

#endif // ARKANOID_HIGH_SCORE_MANAGER_HPP
