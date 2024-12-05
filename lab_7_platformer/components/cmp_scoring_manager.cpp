#include "cmp_scoring_manager.h"

int ScoreManager::score = 0;

void ScoreManager::AddScore(int points) {
    score += points;
}

int ScoreManager::GetScore() {
    return score;
}

void ScoreManager::ResetScore() {
    score = 0;
}