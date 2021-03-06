// Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

int main()
{
	//Game game = Game::GetInstance();
	Game::GetInstance().Init();

	while (Game::GetInstance().IsRunning())
	{
		Game::GetInstance().Update();
		Game::GetInstance().Draw();
	}

	return 0;
}