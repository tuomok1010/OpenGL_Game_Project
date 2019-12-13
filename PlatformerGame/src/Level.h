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
	GLboolean isPlayerCollidingWithBlocks();

private:
	GLboolean CollisionCheck(Player& player, GameObject& obj);
	GLboolean CollisionCheck(GameObject& obj1, GameObject& obj2);
private:
	std::vector<std::vector<GLchar>> levelData;
	std::vector<GameObject> blocks;
	std::vector<Texture2D*> textures{};

	SpriteRenderer& renderer;
	Player& player;
};