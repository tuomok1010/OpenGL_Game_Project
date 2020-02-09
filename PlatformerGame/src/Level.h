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
#include "ObjectivesList.h"
#include "Target.h"

class Level
{
public:
	Level(SpriteRenderer& renderer, PrimitiveRenderer& primitiveRenderer, Player& player);
	~Level();

	void Load(const std::string& filePath, const std::string& backGroundPath = "");
	void ProcessLevelData();
	void Draw(Window& window, float deltaTime);
	GLboolean IsPlayerSpottedByEnemies();
	void RunEnemyBehaviour(float deltaTime);
	void RunSpearmanBehaviour(Spearman& enemy, float deltaTime);
	void RunTargetBehaviour(Target& target, float deltaTime);
	void RunSpikeTrapBehaviour(SpikeTrap& spikeTrap);
	void RunPlatformBehaviour(GameObject& platform, GameObject& block);
	void RunCoinBehaviour(Coin& coin);
	void SetAnimationToAllAliveEnemies(EnemyState newState);
	void InitObjectives();
	void InitLevel0Objectives();
	void InitLevel1Objectives();

	void Update(GLfloat deltaTime);
	void ProcessPlayerCollisions(GameObject& obj);
	void ProcessEnemyCollisions(Enemy& enemy, GameObject& obj);
	void ProcessGameObjectCollisions(GameObject& object, GameObject& otherObject);

	const ObjectivesList& GetObjectivesList()const { return objectivesList; }

	GLboolean levelComplete{ false };
	GLboolean quitGame{ false };

	GLuint levelNumber;

private:
	std::vector<std::vector<GLchar>> levelData;
	std::vector<GameObject*> blocks;
	std::vector<GameObject*> assets;
	std::vector<GameObject*> checkPoints;
	std::vector<Texture2D*> assetTextures;
	std::vector<Enemy*> enemies;
	std::vector<Coin*> coins;

	Texture2D* backGround;
	GLboolean hasClouds;
	std::vector<Texture2D*> cloudTextures;
	std::vector<glm::vec2> cloudPositions;
	std::random_device rd;
	std::mt19937 rng;

	struct Cloud
	{
		Cloud(Texture2D& tex, glm::vec2 pos) : texture(tex), position(pos) {}
		Texture2D& texture;
		glm::vec2 position;
	};

	std::vector<Cloud*> clouds;

	SpriteRenderer& renderer;
	PrimitiveRenderer& primitiveRenderer;
	Player& player;
	
	ObjectivesList objectivesList;
};