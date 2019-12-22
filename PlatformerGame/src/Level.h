#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

#include "SpikeTrap.h"
#include "Player.h"
#include "Window.h"

class Level
{
public:
	Level(SpriteRenderer& renderer, Player& player);
	~Level();

	void Load(const std::string& filePath, const std::string& backGroundPath = "");
	void ProcessLevelData();
	void Draw(Window& window);
	GLboolean isPlayerCollidingWithBlocks();
	void handlePlayerCollisionWithAssets();

	GLboolean gravityEnabled{ true };
	GLboolean levelComplete{ false };

private:
	GLboolean CollisionCheck(Player& player, GameObject& obj);
	GLboolean CollisionCheck(GameObject& obj1, GameObject& obj2);
private:
	std::vector<std::vector<GLchar>> levelData;
	std::vector<GameObject*> blocks;
	std::vector<GameObject*> assets;
	std::vector<Texture2D*> assetTextures{};

	Texture2D* backGround{};
	GLboolean hasClouds{ false };
	std::vector<Texture2D*> clouds{};
	std::vector<glm::vec2> cloudPositions{};
	std::random_device rd;
	std::mt19937 rng;

	SpriteRenderer& renderer;
	Player& player;
};