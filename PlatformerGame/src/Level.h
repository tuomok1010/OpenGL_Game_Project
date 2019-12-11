#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "GameObject.h"
#include "Player.h"

class Level
{
public:
	Level(SpriteRenderer& renderer, Player& player);
	~Level();

	void Load(const std::string& filePath);
	void ProcessLevelData();
	void Draw();

private:
	std::vector<std::vector<GLchar>> levelData;
	std::vector<GameObject> blocks;
	std::vector<Texture2D*> textures{};

	SpriteRenderer& renderer;
	Player& player;
};