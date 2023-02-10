#pragma once

#include "FloatEnemy.h"

const string SPAWNER_WRAITH_TEXTURE = "Assets/Textures/Wraith_Walking_2.png";		// Path of the texture

const float SPAWNER_WRAITH_XP = 10.0f;											// XP of floating enemy
const unsigned int SPAWNER_WRAITH_SCORE = 12;										// Score of floating enemy

class SpawnerWraith : public FloatEnemy
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	SpawnerWraith(const Vector2f position);
	~SpawnerWraith() {}
};

