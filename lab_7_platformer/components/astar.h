//astar.h
//pathfinding decision making behaviour
#pragma once

#include <engine.h>
#include <vector>

//vector with starting position and target position
std::vector<sf::Vector2i> pathFind(sf::Vector2i start, sf::Vector2i finish);