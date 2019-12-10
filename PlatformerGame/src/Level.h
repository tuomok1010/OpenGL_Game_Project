#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "GameObject.h"

class Level
{
public:
	Level(Shader& shader, SpriteRenderer& renderer, Texture2D& blockTexture);
	~Level();

	void Load(const std::string& filePath);
	void ProcessLevelData();
	void Draw();

private:
	std::vector<std::vector<GLchar>> levelData;
	std::vector<GameObject> blocks;

	Shader& shader;
	SpriteRenderer& renderer;
	Texture2D& blockTexture;
};