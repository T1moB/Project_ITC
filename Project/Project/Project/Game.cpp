#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "NodeCreator.h"
#include "MainGraph.h"

using namespace sf;

Game::Game() : 
	m_window(VideoMode(1080, 720), "SFML works!"/*, sf::Style::Fullscreen*/),
	grid(m_window)
{

}


void Game::Init() {
	
	grid.CreateGrid();
	//NodeCreator nc;
	//nc.Create();
	mg.CreateGraph();
	//grid.CreateGridFromGraph(mg.m_graph);
	//mg.AStar();
}

void Game::Update() {

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::Draw() {

	m_window.clear(sf::Color::Black);
	//grid.DrawFromGraph(mg.m_graph);
	//grid.Draw();
	m_window.display();
}

bool Game::IsRunning() {
	return m_window.isOpen();
}

/*Game::~Game()
{
}*/
