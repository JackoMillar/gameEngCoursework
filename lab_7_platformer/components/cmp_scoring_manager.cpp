#include "cmp_scoring_manager.h"
#include <iostream>
using namespace std;

int ScoreManager::score = 0;
int ScoreManager::highScore = 0;

void ScoreManager::AddScore(int points) {
    // Add Points to Score
    score += points;
    if (score > highScore)
    {
        highScore = score;
        cout << " Scene 1 Load\n\n\n\n" << endl;
    }
}

int ScoreManager::GetScore() {
    // Return score
    return score;
}

int ScoreManager::GetHighScore() {
    return highScore;
}

void ScoreManager::ResetScore() {
    // Set Score to 0
    score = 0;
}