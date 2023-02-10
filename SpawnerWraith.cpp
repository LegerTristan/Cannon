#include "SpawnerWraith.h"

SpawnerWraith::SpawnerWraith(const Vector2f _position)
	: FloatEnemy(_position, SPAWNER_WRAITH_TEXTURE)
{
	// Set enemy's sprite & settings
	setScale(FLOAT_ENEMY_SCALE);

	// Set enemy's velocity
	UpdateVelocity(FLOAT_ENEMY_VELOCITY * 1.5f);

	// Set enemy's movement component
	mMoveComp = new FloatMoveComponent(this, mVelocity);

	// Set enemy's animation component
	mAnimComp = new AnimationComponent(this, .1f, "Assets/JSON/Wraith_Walking_2.json");

	// Set enemy's collision component
	mCollisionComp = new CollisionComponent(this, CollisionTag::ENEMY, "Assets/JSON/Wraith_Walking_2.json");

	UpdateXP(SPAWNER_WRAITH_XP);
	mGivenScore = SPAWNER_WRAITH_SCORE;
}
