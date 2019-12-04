#pragma once

#include "Window.h"
#include "Shader.h"

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
	Shader tempShader;
};

