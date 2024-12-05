#include "cmp_scoring_manager.h"

// Initally set score to 0
int ScoreManager::score = 0;

void ScoreManager::AddScore(int points) {
    // Add Points to Score
    score += points;
}

int ScoreManager::GetScore() {
    // Return score
    return score;
}

void ScoreManager::ResetScore() {
    // Set Score to 0
    score = 0;
}