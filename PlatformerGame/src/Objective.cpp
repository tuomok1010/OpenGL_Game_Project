#include "Objective.h"
#include <iostream>

Objective::Objective(Player& player, ObjectiveType type, ObjectivePriority priority)
	:
	player(player),
	type(type),
	priority(priority),
	state(ObjectiveState::IN_PROGRESS)
{

}

Objective::~Objective()
{
}

void Objective::Update()
{
	CheckIfCompleted();
}

void Objective::CheckIfCompleted()
{
	switch (type)
	{
		case ObjectiveType::COLLECT_COIN:
		{
			for (auto& coin : coinsToCollect)
			{
				if (!coin->GetIsCollected())
				{
					state = ObjectiveState::IN_PROGRESS;
					return;
				}
			}
			state = ObjectiveState::COMPLETED;
			break;
		}
		case ObjectiveType::COLLECT_OBJECT:	// TODO add collect functionality to GameObjects
		{
			for (auto& obj : objectsToCollect)
			{
				if (!player.SimpleCollisionCheck(*obj))
				{
					state = ObjectiveState::IN_PROGRESS;
				}
			}
			state = ObjectiveState::COMPLETED;
			break;
		}
		case ObjectiveType::KILL_TARGET:
		{
			for (auto& target : targetsToKill)
			{
				if (!target->GetIsDead())
				{
					state = ObjectiveState::IN_PROGRESS;
					return;
				}
			}
			state = ObjectiveState::COMPLETED;
			break;
		}
		case ObjectiveType::MOVE_TO_LOCATION: // move some of this in the addlocationtomovefunc
		{
			if (player.SimpleCollisionCheck(locationToMoveToTriggerBox))
			{
				state = ObjectiveState::COMPLETED;
			}
			break;
		}
		default:
			state = ObjectiveState::IN_PROGRESS;
	}
}

void Objective::AddCoin(Coin* coinToCollect)
{
	coinsToCollect.emplace_back(coinToCollect);
}

void Objective::AddObject(GameObject* objectToCollect)
{
	objectsToCollect.emplace_back(objectToCollect);
}

void Objective::AddTargetToKill(Enemy* enemyToKill)
{
	targetsToKill.emplace_back(enemyToKill);
}

void Objective::AddLocationToMoveTo(glm::vec2 locationToMoveTo)
{
	this->locationToMoveTo = locationToMoveTo;
	locationToMoveToTriggerBox.size = glm::vec2(20.0f);
	locationToMoveToTriggerBox.position = glm::vec2(locationToMoveTo.x - locationToMoveToTriggerBox.size.x / 2.0f, locationToMoveTo.y);
}
