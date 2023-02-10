#include "Enemy.h"
#include "LevelState.h"
#include "WaveManager.h"
#include "ScoreManager.h"
#include "Player.h"
#include "ScalarUpgradeComponent.h"

float Enemy::mGlobalVelocity = 1.0f;
ScalarUpgradeComponent<Enemy, float>* Enemy::mSpeedUp = nullptr;

float Enemy::mGlobalXP = 0.0f;
ScalarUpgradeComponent<Enemy, float>* Enemy::mXPUp = nullptr;

short Enemy::mGlobalLife = 0;
ScalarUpgradeComponent<Enemy, short>* Enemy::mLifeUp = nullptr;

Enemy::Enemy(const Vector2f _position, const Texture* _enemyTexture) : Entity(_position, _enemyTexture)
{
 	if (!mSpeedUp)
	{
		mSpeedUp = new ScalarUpgradeComponent<Enemy, float>(this, &Enemy::ComputeGlobalVelocity,
			Enemy::mGlobalVelocity, "Move speed increase !", "Assets/Textures/Up_Enemy_Speed.png", UpgradeType::ENEMY);
	}

	if (!mXPUp)
	{
		mXPUp = new ScalarUpgradeComponent<Enemy, float>(this, &Enemy::ComputeGlobalXP,
			Enemy::mGlobalXP, "XP increase !", "Assets/Textures/Up_Enemy_XP.png", UpgradeType::ALLY);
	}

	if (!mLifeUp)
	{
		mLifeUp = new ScalarUpgradeComponent<Enemy, short>(this, &Enemy::ComputeGlobalLife,
			Enemy::mGlobalLife, "Enemies life increase !", "Assets/Textures/Up_Enemy_Life.png", UpgradeType::ENEMY);
	}

	// Set enemy's collision component
	mCollisionComp = nullptr;

	// Set enemy's animation component

	mAnimComp = nullptr;

	mXP = 0;
	mGivenScore = 0;
	UpdateLife(DEFAULT_ENEMY_LIFE);
}

Enemy::~Enemy()
{
	if (mAnimComp)
		delete mAnimComp;
}

float Enemy::GetXP() const
{
	return mXP;
}

unsigned int Enemy::GetScore() const
{
	return mGivenScore;
}

float Enemy::ComputeGlobalVelocity(const float _upgradeValue) const
{
	return DEFAULT_ENEMY_VELOCITY_BONUS + _upgradeValue * ENEMY_VELOCITY_SCALAR;
}

float Enemy::ComputeGlobalXP(const float _upgradeValue) const
{
	return ENEMY_XP_SCALAR * _upgradeValue;
}

short Enemy::ComputeGlobalLife(const float _upgradeValue) const
{
	return DEFAULT_ENEMY_LIFE + _upgradeValue;
}

void Enemy::UpdateVelocity(const Vector2f& _baseVelocity)
{
	mVelocity = _baseVelocity * mGlobalVelocity;
}

void Enemy::UpdateXP(const float& _baseXP)
{
	mXP = _baseXP + mGlobalXP;
}

void Enemy::UpdateLife(const short& _baseLife)
{
	mLife = _baseLife + mGlobalLife;
}

void Enemy::Update(RenderWindow* _window)
{
	mAnimComp->UpdateAnimSprite();
	
	if (!mMoveComp->Move())
	{
		KillByGame();
		delete this;
	}
	else
	{
		mCollisionComp->SetHitBox({(float)getPosition().x, (float)getPosition().y, (float)getTextureRect().width, (float)getTextureRect().height});
		_window->draw(*this);
		_window->draw(mCollisionComp->GetHitBox());
	}
}

void Enemy::KillByPlayer()
{
	LevelState::GetInstance()->GetPlayer()->IncreaseXP(GetXP());
	LevelState::GetInstance()->GetScoreManager()->AddScore(GetScore());
	Die();
}

void Enemy::KillByGame()
{
	LevelState::GetInstance()->ReduceHP(1);
	Die();
}

void Enemy::Die()
{
	Entity::Die();

	LevelState::GetInstance()->GetWaveManager()->DecreaseEnemyNbr();
}
