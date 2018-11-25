#pragma once
#include "Graph.h"
#include <SFML/Graphics.hpp>
class MainGraph
{

	typedef GraphArc<std::string, int> Arc;
	typedef GraphNode<std::string, int> Node;

public:
	MainGraph();
	~MainGraph();
	void CreateGraph();
	void AStar();
	void ThetaStar(sf::Image image);
	vector<Vector2f> GetHitPoints() { return m_graph.hitPoints; }
	void Draw(sf::RenderWindow & window);
	void SetStartGoal(Vector2i pos);
	void SetAObstacle(Vector2i pos);
	Graph<std::string, int> m_graph;
};


