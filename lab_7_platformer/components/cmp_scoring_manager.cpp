#include "cmp_scoring_manager.h"

#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_health.h"
#include "../components/cmp_scoring.h"
//#include "../components/cmp_scoring_manager.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_state_machine.h"
//#include "../components/cmp_enemy_states.h"
#include "../components/steering_decisions.h"
#include "../components/steering_states.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include "../components/cmp_hurt_player.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <random>
#include <Box2D/Dynamics/b2Body.h>

int ScoreManager::score = 0;
int ScoreManager::highScore = 0;

void ScoreManager::AddScore(int points) {
    score += points;
    if (score > highScore)
    {
        highScore = score;
        cout << " Scene 1 Load\n\n\n\n" << endl;
    }
}

int ScoreManager::GetScore() {
    return score;
}

int ScoreManager::GetHighScore() {
    return highScore;
}

void ScoreManager::ResetScore() {
    score = 0;
}