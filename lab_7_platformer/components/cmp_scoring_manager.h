#pragma once

class ScoreManager {
public:
    static void AddScore(int amount);
    static int GetScore();
    static int GetHighScore();
    static void ResetScore();
    
private:
    static int score;
    static int highScore;
};
