#include "Grid.h"
#include <sstream>
#include <random>
#include <ctime>  
#include <list>  

using namespace sf;

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
			g->nodeIndex(index)->SetPosition(j * sizeX + 0.5*sizeX, i * sizeY + 0.5*sizeY);
			obstacles[index] = false;
			int r = rand() % 5;
			if (r == 0 && index != 11 & index != 88) {
				obstacles[index] = true;
				g->nodeIndex(index)->SetAsObstacle();
				/*list<Arc> arcs = g->nodeIndex(index)->arcList();
				typedef list<Arc> arclist;
				auto it = arcs.begin();
				for (; it != arcs.end(); ++it)
				{
					Arc arc = *it;
					Node* neighbour = arc.node();
					neighbour->removeArc(g->nodeIndex(index));
				}*/
			}
		}
	}
	g->SetStart(g->nodeIndex(11));
	g->SetGoal(g->nodeIndex(88));
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
			square.setPosition(g->nodeIndex(index)->GetXPos() - +0.5*sizeX, g->nodeIndex(index)->GetYPos() - +0.5*sizeY);
			square.setFillColor(Color(10, 175, 10));
			if (g->nodeIndex(index)->IsObtacle()) {
				square.setFillColor(Color(128, 128, 128));
			}
			g->nodeIndex(index)->sizeX = sizeX;
			g->nodeIndex(index)->sizeY = sizeY;
			m_window.draw(square);
			CircleShape c(10);
			c.setFillColor(Color::Magenta);
			c.setPosition(g->GetStart()->GetXPos() - 5, g->GetStart()->GetYPos() - 5);
			m_window.draw(c);
			c.setFillColor(Color::Yellow);
			c.setPosition(g->GetGoal()->GetXPos() - 5, g->GetGoal()->GetYPos() - 5);
			m_window.draw(c);
			if (g->nodeIndex(index)->IsPath()) {
				//square.setFillColor(Color(10, 10, 255));
				for (Node* node = g->nodeIndex(index); node != NULL; node = node->previous()) {
					CircleShape circle(10);
					circle.setFillColor(Color::Blue);
					circle.setPosition(node->GetXPos() - 5, node->GetYPos() - 5);
					m_window.draw(circle);
					if (node->previous()) {
						sf::VertexArray line(sf::LinesStrip, 2);
						line[0].position = sf::Vector2f(node->GetXPos(), node->GetYPos());
						line[0].color = sf::Color::Blue;
						line[1].position = sf::Vector2f(node->previous()->GetXPos(), node->previous()->GetYPos());
						line[1].color = sf::Color::Blue;
						m_window.draw(line);
					}
				}
			}
		}
	}

}

Grid::~Grid()
{
}
