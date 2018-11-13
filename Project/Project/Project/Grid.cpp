#include "Grid.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <random>
#include "Game.h"
#include <ctime>  

using namespace sf;

Game* _game;
int sizeX, sizeY, gridSize;
Grid::Grid(sf::RenderWindow & window) : m_window(window)
{
	srand(time(0));
	sizeX = window.getSize().x/10;	
	//sizeX = 80;	
	sizeY = window.getSize().y/10;
	//sizeY = 80;
	gridSize = 10;
	grid = new Vector2f[gridSize*gridSize];
	obstacles = new bool[gridSize*gridSize];
}


void Grid::CreateGrid() {
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			grid[index] = Vector2f(j * sizeX, i * sizeY);
			obstacles[index] = false;
			int r = (int)std::rand() % 10;
			if(r == 0)
				obstacles[index] = true;
		}
	}
}

void Grid::CreateGridFromGraph(Graph<std::string, int>* g ) {
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			grid[index] = Vector2f(j * sizeX, i * sizeY);
			g->nodeIndex(index)->SetPosition(j * sizeX, i * sizeY);
			obstacles[index] = false;
			int r = rand() % 5;
			if (r == 0 && index != 11 & index != 88) {
				obstacles[index] = true;
				g->nodeIndex(index)->SetAsObstacle();
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
			if (obstacles[index]) {
				RectangleShape square(Vector2f(sizeX, sizeY));
				square.setPosition(grid[index].x, grid[index].y);
				square.setFillColor(Color(128, 128, 128));
				m_window.draw(square);
			}
		}
	}
}

void Grid::DrawFromGraph(Graph<std::string, int>* g) {
	Font font;
	if (!font.loadFromFile("Data/OpenSans.ttf")) {
		cout << "couldn't load file" << endl;
	}
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			RectangleShape square(Vector2f(sizeX, sizeY));
			square.setPosition(g->nodeIndex(index)->GetXPos(), g->nodeIndex(index)->GetYPos());
			square.setFillColor(Color(10, 175, 10));
			if (g->nodeIndex(index)->IsObtacle()) {
				square.setFillColor(Color(128, 128, 128));
			}
			else if (g->nodeIndex(index)->IsPath()) {
				square.setFillColor(Color(0, 0, 255));
			}
			m_window.draw(square);
		}
	}
}

Grid::~Grid()
{
}
