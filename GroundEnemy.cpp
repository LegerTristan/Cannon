#include "GroundEnemy.h"
#include "Game.h"

GroundEnemy::GroundEnemy(const Vector2f& _position) 
	: Enemy(_position, Game::GetInstance()->GetTextureManager()->GetTexture(GROUND_ENEMY_TEXTURE).get())
{
	// Set enemy's velocity
	UpdateVelocity(GROUND_ENEMY_VELOCITY);

	// Set enemy's sprite & settings
	setScale(GROUND_ENEMY_SCALE);

	// Set enemy's movement component
	mMoveComp = new StraightMoveComponent(this, mVelocity);

	// Set enemy's animation component
	mAnimComp = new AnimationComponent(this, .1f, "Assets/JSON/Golem_Walking_1.json");

	// Set enemy's collision component
	mCollisionComp = new CollisionComponent(this, CollisionTag::ENEMY, "Assets/JSON/Golem_Walking_1.json");

	UpdateXP(GROUND_ENEMY_XP);
	mGivenScore = GROUND_ENEMY_SCORE;
}

GroundEnemy::GroundEnemy(const Vector2f& _position, const string& _texturePath)
	: Enemy(_position, Game::GetInstance()->GetTextureManager()->GetTexture(_texturePath).get())
{
	// Set enemy's movement component
	mMoveComp = nullptr;

	// Set enemy's animation component
	mAnimComp = nullptr;

	// Set enemy's collision component
	mCollisionComp = nullptr;

	mGivenScore = GROUND_ENEMY_SCORE;
}