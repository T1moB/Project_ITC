#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
class Grid
{
public:
	Grid(sf::RenderWindow & window);
	~Grid();
	void CreateGrid();
	void CreateGridFromGraph(Graph<std::string, int> g);
	void Draw();
	void DrawFromGraph(Graph<std::string, int> g);
	sf::Vector2f *grid;
	bool *obstacles;
private:
	sf::RenderWindow & m_window;
};

