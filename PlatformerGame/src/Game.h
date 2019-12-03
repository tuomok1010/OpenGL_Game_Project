#pragma once

#include "Window.h"

class Game
{
public:
	Game(int scrnWidth, int scrnHeight);
	~Game();

	void Run();

public:
private:
private:
	Window mainWindow;
};

