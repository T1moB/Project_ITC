#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <ctime>  

using namespace sf;

Game* _game;
int sizeX, sizeY, gridSize;
Grid::Grid(sf::RenderWindow & window) : m_window(window)
{
	
	sizeX = window.getSize().x/10;	
	//sizeX = 108;	
	sizeY = window.getSize().y/10;
	//sizeY = 72;
	gridSize = 10;
	grid = new Vector2f[gridSize*gridSize];
	obstacles = new bool[gridSize*gridSize];
	srand(time(0));
}


void Grid::CreateGrid() {
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			//RectangleShape square(Vector2f(sizeX,sizeY));
			grid[index] = Vector2f(j * sizeX, i * sizeY);
			//square.move(Vector2f(j + 0.5*sizeX, i + 0.5*sizeY));
			//square.setFillColor(Color(128, 128, 128));
			obstacles[index] = false;
			int r = (int)std::rand() % 10;
			if(r == 0)
				obstacles[index] = true;
		}
	}
}

void Grid::CreateGridFromGraph(Graph<std::string, int> g ) {
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			grid[index] = Vector2f(j * sizeX, i * sizeY);
			g.nodeIndex(index)->SetPosition(j * sizeX, i * sizeY);
			obstacles[index] = false;
			int r = (int)std::rand() % 10;
			if (r == 0) {
				obstacles[index] = true;
				//g.nodeIndex(index)->SetAsObstacle();
			}
		}
	}

}

void Grid::Draw() {
	RectangleShape background(Vector2f(m_window.getSize().x, m_window.getSize().y));
	background.setFillColor(Color(10,175,10));
	m_window.draw(background);
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			if (obstacles[i*sizeY + j]) {
				RectangleShape square(Vector2f(sizeX, sizeY));
				square.setPosition(grid[i*gridSize + j]);
				square.setFillColor(Color(128, 128, 128));
				m_window.draw(square);
			}
		}
	}
}

void Grid::DrawFromGraph(Graph<std::string, int> g) {
	RectangleShape background(Vector2f(m_window.getSize().x, m_window.getSize().y));
	background.setFillColor(Color(10, 175, 10));
	m_window.draw(background);
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			if (g.nodeIndex(index)->IsObtacle()) {
				RectangleShape square(Vector2f(sizeX, sizeY));
				square.setPosition(g.nodeIndex(index)->GetXPos(), g.nodeIndex(index)->GetXPos());
				square.setFillColor(Color(128, 128, 128));
				m_window.draw(square);
			}
		}
	}
}

Grid::~Grid()
{
}
