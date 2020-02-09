#include "ObjectivesList.h"

ObjectivesList::ObjectivesList()
{
}

ObjectivesList::~ObjectivesList()
{
}

void ObjectivesList::AddObjective(const Objective& objToAdd, ObjectivePriority priority)
{
	if (priority == ObjectivePriority::PRIMARY)
		objectivesPrimary.emplace_back(objToAdd);
	else if (priority == ObjectivePriority::SECONDARY)
		objectivesSecondary.emplace_back(objToAdd);
}

GLboolean ObjectivesList::CheckObjectives()
{
	GLboolean allPrimaryObjectivesComplete{ true };

	if (!objectivesPrimary.empty())
	{
		for (auto& objective : objectivesPrimary)
		{
			objective.Update();
			if (objective.GetState() != ObjectiveState::COMPLETED)
			{
				allPrimaryObjectivesComplete = false;
			}
		}
	}
	else
	{
		return false;
	}

	if (!objectivesSecondary.empty())
	{
		for (auto& objective : objectivesSecondary)
		{
			objective.Update();
			if (objective.GetState() != ObjectiveState::COMPLETED)
			{
				// if the player has not finished all secondary objectives at the end of the level, do not give him full score for the level
			}
		}
	}

	return allPrimaryObjectivesComplete;
}

void ObjectivesList::Clear()
{
	objectivesPrimary.clear();
	objectivesSecondary.clear();
}
