#include "Grid.h"
#include <sstream>
#include <random>
#include <ctime>  
#include <cmath>  
#include <list>  

using namespace sf;

Grid::Grid(sf::RenderWindow & window, int size) : m_window(window), gridSize(size)
{
	srand(time(0));
	sizeX = window.getSize().x/gridSize;	
	sizeY = window.getSize().y/gridSize;
}

void Grid::CreateGridFromGraph(Graph<std::string, int>* g ) {
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			g->nodeIndex(index)->SetPosition(j * sizeX + 0.5*sizeX, i * sizeY + 0.5*sizeY);
			int r = rand() % 5;
			if (r == 0 && index != 42 & index != 274) {
				g->nodeIndex(index)->SetAsObstacle();
			}
		}
	}
	g->SetStart(g->nodeIndex(42));
	g->SetGoal(g->nodeIndex(274));
}

void Grid::DrawFromGraph(Graph<std::string, int>* g) {
	RectangleShape background(Vector2f(m_window.getSize().x, m_window.getSize().y));
	background.setFillColor(Color(10, 175, 10));
	m_window.draw(background);
	Font font;
	int pathIndex = 0;
	if (!font.loadFromFile("Data/OpenSans.ttf")) {
		cout << "couldn't load file" << endl;
	}
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int index = i * gridSize + j;
			if (g->nodeIndex(index)->IsObtacle()) {
				RectangleShape square(Vector2f(sizeX, sizeY));
				square.setPosition(g->nodeIndex(index)->GetXPos() - +0.5*sizeX, g->nodeIndex(index)->GetYPos() - +0.5*sizeY);
				square.setFillColor(Color(128, 128, 128));
				m_window.draw(square);
			}
			g->nodeIndex(index)->sizeX = sizeX;
			g->nodeIndex(index)->sizeY = sizeY;
			if (g->nodeIndex(index)->IsPath()) {
				pathIndex = index;
			}
		}
	}
	if (g->foundGoal) {
		for (Node* node = g->nodeIndex(pathIndex); node != NULL; node = node->previous()) {
			CircleShape circle(4);
			circle.setFillColor(Color::Blue);
			circle.setPosition(node->GetXPos() - 2, node->GetYPos() - 2);
			m_window.draw(circle);
			if (node->previous()) {
				sf::VertexArray line(sf::LinesStrip, 2);
				line[0].position = sf::Vector2f(node->GetXPos(), node->GetYPos());
				line[0].color = sf::Color::Blue;
				line[1].position = sf::Vector2f(node->previous()->GetXPos(), node->previous()->GetYPos());
				line[1].color = sf::Color::Blue;
				m_window.draw(line);
			}
			if (node == g->GetStart()) { break; }
		}
	}
	CircleShape c(4);
	c.setFillColor(Color::Magenta);
	c.setPosition(g->GetStart()->GetXPos() - 2, g->GetStart()->GetYPos() - 2);
	m_window.draw(c);
	c.setFillColor(Color::Yellow);
	c.setPosition(g->GetGoal()->GetXPos() - 2, g->GetGoal()->GetYPos() - 2);
	m_window.draw(c);

}

Grid::~Grid()
{
}
