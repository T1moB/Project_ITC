#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "NodeCreator.h"
#include "MainGraph.h"
#include <Windows.h>
#include <thread>

using namespace sf;

bool isPressed = false;
int range = 1;

Game::Game() : 
	m_window(VideoMode(1080, 720), "Pathfinding"/*, sf::Style::Fullscreen*/),
	grid(m_window)
{

}


void Game::Init() {
	
	//grid.CreateGrid();
	//NodeCreator nc;
	//nc.Create();
	mg.CreateGraph();
	grid.CreateGridFromGraph(&mg.m_graph);
	//mg.AStar();
}

void Game::Update() {

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
	if (GetKeyState('X') & 0x8000) {
		if (!isPressed) {
			mg.AStar();
			isPressed = true;
		}
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000) {
		if (!isPressed) {
			range++;
			isPressed = true;
		}
	}
	else if (GetKeyState(VK_ESCAPE) & 0x8000) {
		if (!isPressed) {
			m_window.close();
			isPressed = true;
		}
	}
	else {
		isPressed = false;
	}
}

void Game::Draw() {

	m_window.clear();
	grid.DrawFromGraph(&mg.m_graph);
	//grid.Draw();
	m_window.display();
}

bool Game::IsRunning() {
	return m_window.isOpen();
}

/*Game::~Game()
{
}*/
