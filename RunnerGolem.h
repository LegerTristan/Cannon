#pragma once

#include "GroundEnemy.h"

const string RUNNER_GOLEM_TEXTURE = "Assets/Textures/Golem_Walking_2.png";	// Path of the texture

const float RUNNER_GOLEM_XP = 6.0f;											// XP given by ground enemies

const unsigned int RUNNER_GOLEM_SCORE = 7;									// Score given by grounds enemies

class RunnerGolem : public GroundEnemy
{
public:
	RunnerGolem(Vector2f position);
	~RunnerGolem();
};

