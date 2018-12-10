#include "Game.h"
#include "Grid.h"
#include "NodeCreator.h"
#include "MainGraph.h"
#include <Windows.h>
#include <thread>

using namespace sf;

bool isPressed = false;
bool mouseIsPressed = false;

Game::Game() : m_window(VideoMode(1080, 720), "Pathfinding"/*, sf::Style::Fullscreen*/),
grid(m_window, GRAPHSIZE), mg(GRAPHSIZE)
{

}


void Game::Init() {
	//NodeCreator nc;
	//nc.Create2(GRAPHSIZE);
	m_window.setFramerateLimit(60);
	mg.CreateGraph();
	grid.CreateGridFromGraph(&mg.m_graph);
}

void Game::Update() {

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
	if (Mouse::isButtonPressed(Mouse::Left)) {
		if (!mouseIsPressed) {
			mg.SetStartGoal(Mouse::getPosition(m_window));
			mouseIsPressed = true;
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right)) {
		if (!mouseIsPressed) {
			mg.SetAObstacle(Mouse::getPosition(m_window));
			mouseIsPressed = true;
		}
	}
	else {
		mouseIsPressed = false;
	}
	if (GetKeyState('X') & 0x8000) {
		if (!isPressed) {
			mg.AStar();
			isPressed = true;
		}
	}
	else if (GetKeyState('Z') & 0x8000) {
		if (!isPressed) {
			Vector2u windowSize = m_window.getSize();
			Texture texture;
			texture.create(windowSize.x, windowSize.y);
			texture.update(m_window);
			Image image = texture.copyToImage();
			mg.ThetaStar(image);
			isPressed = true;
		}
	}
	else if (GetKeyState('A') & 0x8000) {
		if (!isPressed) {
			Vector2u windowSize = m_window.getSize();
			Texture texture;
			texture.create(windowSize.x, windowSize.y);
			texture.update(m_window);
			Image image = texture.copyToImage();
			mg.Run(image);
			isPressed = true;
		}
	}
	else if (GetKeyState('C') & 0x8000) {
		if (!isPressed) {
			Vector2u windowSize = m_window.getSize();
			Texture texture;
			texture.create(windowSize.x, windowSize.y);
			texture.update(m_window);
			Image image = texture.copyToImage();
			mg.LazyThetaStar(image);
			isPressed = true;
		}
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000) {
		if (!isPressed) {
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
	//mg.Draw(m_window);
	m_window.display();
}

bool Game::IsRunning() {
	return m_window.isOpen();
}

