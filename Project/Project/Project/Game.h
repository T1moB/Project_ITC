#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"

class Game
{
public:
	Game();
	void Init();
	void Update();
	void Draw();
	bool IsRunning();
	sf::RenderWindow m_window;
	Grid grid;
	/*Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();*/
private:
	
	//sf::RenderWindow window;
};

