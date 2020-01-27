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
#include "Objective.h"

class Level
{
public:
	Level(SpriteRenderer& renderer, PrimitiveRenderer& primitiveRenderer, Player& player);
	~Level();

	void Load(const std::string& filePath, const std::string& backGroundPath = "");
	void ProcessLevelData();
	void Draw(Window& window, float deltaTime);
	void Update(float deltaTime);
	GLboolean IsPlayerSpottedByEnemies();
	void RunEnemyBehaviour(float deltaTime);
	void RunSpearmanBehaviour(Spearman& enemy, float deltaTime);
	void SetAnimationToAllAliveEnemies(EnemyState newState);
	void InitObjectives();
	GLboolean CheckObjectives();	// returns true if all primary objecives are complete

	void ProcessCollisions();
	void ProcessPlayerCollisions(GameObject& obj);
	void ProcessEnemyCollisions(Enemy& enemy, GameObject& obj);

	const std::vector<Objective>& GetPrimaryObjectives()const { return objectivesPrimary; }
	const std::vector<Objective>& GetSecondaryObjectives()const { return objectivesSecondary; }

	GLboolean levelComplete{ false };
	GLboolean quitGame{ false };

	GLuint levelNumber{};

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
	PrimitiveRenderer& primitiveRenderer;
	Player& player;

	std::vector<Objective> objectivesPrimary{};
	std::vector<Objective> objectivesSecondary{};
};