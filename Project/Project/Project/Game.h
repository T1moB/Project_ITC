#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "MainGraph.h"

#define GRAPHSIZE 20

class Game
{
public:
	static Game& GetInstance() {
		//if (!instance)
		//	instance = Game;
		static Game instance;
		return instance;
	}
	void Init();
	void Update();
	void Draw();
	bool IsRunning();
	sf::RenderWindow m_window;
	Grid grid;
	MainGraph mg;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	//~Game();
private:
	Game();
};

