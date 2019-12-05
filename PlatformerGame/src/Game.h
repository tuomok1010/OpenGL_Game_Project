#pragma once

#include <vector>

#include "Window.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture2D.h"

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
	std::vector<Shader*> shaders{};
};

