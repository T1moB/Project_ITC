#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <ctime>  

using namespace sf;

Game* _game;
int sizeX, sizeY;
Grid::Grid(sf::RenderWindow & window) : m_window(window)
{
	
	sizeX = window.getSize().x/10;	
	//sizeX = 108;	
	sizeY = window.getSize().y/10;
	//sizeY = 72;
	grid = new Vector2f[sizeX*sizeY];
	obstacles = new bool[sizeX*sizeY];
	srand(time(0));
}


void Grid::CreateGrid() {
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			//RectangleShape square(Vector2f(sizeX,sizeY));
			grid[i*sizeY + j] = Vector2f(j * sizeX, i * sizeY);
			//square.move(Vector2f(j + 0.5*sizeX, i + 0.5*sizeY));
			//square.setFillColor(Color(128, 128, 128));
			obstacles[i*sizeY + j] = false;
			int r = (int)std::rand() % 6;
			if(r == 2)
				obstacles[i*sizeY + j] = true;
		}
	}
}

void Grid::Draw() {
	RectangleShape background(Vector2f(m_window.getSize().x, m_window.getSize().y));
	background.setFillColor(Color(10,175,10));
	m_window.draw(background);
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (obstacles[i*sizeY + j]) {
				RectangleShape square(Vector2f(sizeX, sizeY));
				square.setPosition(grid[i*sizeY + j]);
				square.setFillColor(Color(128, 128, 128));
				m_window.draw(square);
			}
		}
	}
}

Grid::~Grid()
{
}
