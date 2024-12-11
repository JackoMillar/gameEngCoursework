//cmp_pathfinding.h
#pragma once
#include <ecm.h>
#include "astar.h"
//will use a list of nodes to traverse level.
//every second it will move to next position in level until 
//it reaches target destination

//it needs to keep track of path, index in path and
//amount of time passed since last move

class PathfindingComponent : public Component {
protected:
	//for keeping track of path
	std::vector<sf::Vector2i> _path;
	//index in path
	size_t _index = 0;
	//time passed since last move
	double _elapsed = 0.0;


public:
	void update(double) override;
	void render() override {}
	void setPath(std::vector<sf::Vector2i>& path);
	explicit PathfindingComponent(Entity* p);
	PathfindingComponent() = delete;
};