#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#include "Coin.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"

enum class ObjectiveType
{
	COLLECT_COIN,
	COLLECT_OBJECT,
	KILL_TARGET,
	MOVE_TO_LOCATION
};

enum class ObjectivePriority
{
	PRIMARY,
	SECONDARY
};

enum class ObjectiveState
{
	IN_PROGRESS,
	COMPLETED,
	FAILED,
	LOCKED	// TODO implement this. Objectives that are blocked cannot be completed until all previous ones are completed
};

class Objective
{
public:
	Objective(Player& player, ObjectiveType type, ObjectivePriority priority);
	~Objective();

	void Update();
	void CheckIfCompleted();

	void AddCoin(Coin* coinToCollect);
	void AddObject(GameObject* objectToCollect);
	void AddTargetToKill(Enemy* enemyToKill);
	void AddLocationToMoveTo(glm::vec2 locationToMoveTo);

	std::string GetName() const { return name; }
	ObjectiveState GetState()const { return state; }

	void SetName(std::string newName) { name = newName; }

private:
	Player& player;

	ObjectiveState state;
	std::string name{};

	std::vector<Coin*> coinsToCollect;
	std::vector<GameObject*> objectsToCollect;
	std::vector<Enemy*> targetsToKill;
	glm::vec2 locationToMoveTo{};
	CollisionBox locationToMoveToTriggerBox;

	ObjectiveType type;
	ObjectivePriority priority;
};