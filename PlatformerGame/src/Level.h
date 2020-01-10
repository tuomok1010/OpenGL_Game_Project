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
#include "Spearman.h"
#include "Coin.h"

class Level
{
public:
	Level(SpriteRenderer& renderer, Player& player);
	~Level();

	void Load(const std::string& filePath, const std::string& backGroundPath = "");
	void ProcessLevelData();
	void Draw(Window& window, float deltaTime);
	GLboolean IsPlayerCollidingWithBlocks();
	void UpdateAssets(float deltaTime);
	GLboolean IsPlayerSpottedByEnemies();
	void RunEnemyBehaviour(float deltaTime);
	void SetAnimationToAllAliveEnemies(EnemyState newState);

	GLboolean gravityEnabled{ true };
	GLboolean levelComplete{ false };
	GLboolean quitGame{ false };

	void KillAllEnemies();

private:
	/*
		TODO consider refactoring. Maybe edit the GameObject class and make the coin inherit from it
	*/
	GLboolean CollisionCheck(Player& player, GameObject& obj);
	GLboolean CollisionCheck(Player& player, Coin& coin);
	GLboolean CollisionCheck(GameObject& obj1, GameObject& obj2);
private:
	std::vector<std::vector<GLchar>> levelData;
	std::vector<GameObject*> blocks;
	std::vector<GameObject*> assets;
	std::vector<Texture2D*> assetTextures{};

	std::vector<Enemy*> enemies{};

	std::vector<Coin*> coins{};

	Texture2D* backGround{};
	GLboolean hasClouds{ false };
	std::vector<Texture2D*> cloudTextures{};
	std::vector<glm::vec2> cloudPositions{};
	std::random_device rd;
	std::mt19937 rng;

	struct Cloud
	{
		Cloud(Texture2D& tex, glm::vec2 pos) : texture(tex), position(pos) {}
		Texture2D& texture;
		glm::vec2 position;
	};

	std::vector<Cloud*> clouds{};

	SpriteRenderer& renderer;
	Player& player;
};