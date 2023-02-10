#include "RunnerGolem.h"

RunnerGolem::RunnerGolem(Vector2f _position) : GroundEnemy(_position, RUNNER_GOLEM_TEXTURE)
{
	// Set enemy's velocity
	UpdateVelocity(GROUND_ENEMY_VELOCITY * 2.0f);

	// Set enemy's sprite & settings
	setScale(GROUND_ENEMY_SCALE);

	// Set enemy's movement component
	mMoveComp = new StraightMoveComponent(this, mVelocity);

	// Set enemy's animation component
	mAnimComp = new AnimationComponent(this, .1f, "Assets/JSON/Golem_Walking_2.json");

	// Set enemy's collision component
	mCollisionComp = new CollisionComponent(this, CollisionTag::ENEMY, "Assets/JSON/Golem_Walking_2.json");

	UpdateXP(RUNNER_GOLEM_XP);
	mGivenScore = RUNNER_GOLEM_SCORE;
}

RunnerGolem::~RunnerGolem()
{
}
