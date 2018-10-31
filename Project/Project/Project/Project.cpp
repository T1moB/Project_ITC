// Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	Game game;
	game.Init();

	while (game.IsRunning())
	{
		game.Update();
		game.Draw();
	}

	return 0;
}