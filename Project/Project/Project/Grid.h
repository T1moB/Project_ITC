#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
class Grid
{
	typedef GraphArc<std::string, int> Arc;
	typedef GraphNode<std::string, int> Node;

public:
	Grid(sf::RenderWindow & window, int size);
	~Grid();
	void CreateGrid();
	void CreateGridFromGraph(Graph<std::string, int> *g);
	void Draw();
	void DrawFromGraph(Graph<std::string, int> *g);
	sf::Vector2f *grid;
	bool *obstacles;
private:
	sf::RenderWindow & m_window;
	int sizeX, sizeY;
	int gridSize;
};

