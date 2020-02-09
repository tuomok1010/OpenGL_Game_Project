#pragma once

#include "Objective.h"

class ObjectivesList
{
private:
	std::vector<Objective> objectivesPrimary;
	std::vector<Objective> objectivesSecondary;
public:
	ObjectivesList();
	~ObjectivesList();

	void AddObjective(const Objective& objToAdd, ObjectivePriority priority);
	GLboolean CheckObjectives();
	void Clear();

	const std::vector<Objective>& GetPrimaryObjectives() const { return objectivesPrimary; }
	const std::vector<Objective>& GetSecondaryObjectives() const { return objectivesSecondary; }
};