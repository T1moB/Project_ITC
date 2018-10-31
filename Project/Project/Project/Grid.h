#pragma once
#include <SFML/Graphics.hpp>
class Grid
{
public:
	Grid(sf::RenderWindow & window);
	~Grid();
	void CreateGrid();
	void Draw();
	sf::Vector2f *grid;
	bool *obstacles;
private:
	sf::RenderWindow & m_window;
};

