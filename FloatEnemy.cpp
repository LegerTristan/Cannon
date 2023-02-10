#include "FloatEnemy.h"
#include "Game.h"

FloatEnemy::FloatEnemy(const Vector2f& _position) 
	: Enemy(_position, Game::GetInstance()->GetTextureManager()->GetTexture(FLOAT_ENEMY_TEXTURE).get())
{
	// Set enemy's velocity
	UpdateVelocity(FLOAT_ENEMY_VELOCITY);

	// Set enemy's sprite & settings
	setScale(FLOAT_ENEMY_SCALE);

	// Set enemy's movement component
	mMoveComp = new FloatMoveComponent(this, mVelocity);
	
	// Set enemy's animation component
	mAnimComp = new AnimationComponent(this, .1f, "Assets/JSON/Wraith_Walking_1.json");

	// Set enemy's collision component
	mCollisionComp = new CollisionComponent(this, CollisionTag::ENEMY, "Assets/JSON/Wraith_Walking_1.json");

	UpdateXP(FLOAT_ENEMY_XP);
	mGivenScore = FLOAT_ENEMY_SCORE;
}

FloatEnemy::FloatEnemy(const Vector2f& _position, const string& _texturePath)
	: Enemy(_position, Game::GetInstance()->GetTextureManager()->GetTexture(_texturePath).get())
{

	// Set enemy's sprite & settings
	setScale(FLOAT_ENEMY_SCALE);

	// Set enemy's movement component
	mMoveComp = new FloatMoveComponent(this, mVelocity);
}
