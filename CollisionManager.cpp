#include "CollisionManager.h"
#include "LevelState.h"
#include "WaveManager.h"
#include "Game.h"
#include "ScoreManager.h"
#include "Enemy.h"
#include "CannonBall.h"
#include "Player.h"

CollisionManager::CollisionManager()
{
	mPhysicCheckRate = PHYSIC_CHECK_RATE;
	mLastCheckTime = mCurrentTime = Game::GetInstance()->GetTimer()->GetCurrentTime();
}

bool CollisionManager::HasToCheckPhysic()
{
	mCurrentTime += Game::GetInstance()->GetTimer()->GetDeltaTime();
	return mCurrentTime > mLastCheckTime +  mPhysicCheckRate;
}

void CollisionManager::SetLastCheckTime()
{
	mLastCheckTime = Game::GetInstance()->GetTimer()->GetCurrentTime();

}

void CollisionManager::UpdateCollision(vector<class Entity*>& _entities)
{
	CollisionComponent* ballCollision, * enemyCollision;

 	for (unsigned int i = 0; i < _entities.size(); ++i)
	{
		ballCollision = _entities[i]->GetCollisionComp();

		if (ballCollision->GetCollisionTag() == CollisionTag::BALL)
		{
			bool stillNoCollide = true;

			for (unsigned int j = 0; j < _entities.size() && stillNoCollide; ++j)
			{
				enemyCollision = _entities[j]->GetCollisionComp();

				if (enemyCollision->GetCollisionTag() == CollisionTag::ENEMY && ballCollision->CollideWith(enemyCollision))
				{
					HandleEntityCollision(_entities, j, i);
					stillNoCollide = false;
					--i;
				}
			}
		}
		
	}
}

void CollisionManager::HandleEntityCollision(std::vector<Entity*>& _entities, unsigned int& j, unsigned int i)
{
	_entities[i]->DecreaseLife();
	_entities[j]->DecreaseLife();
	Entity* tempRef = nullptr;

	if (!_entities[i]->HasLife())
	{
		tempRef = _entities[i];
		tempRef->Die();
		delete tempRef;

		if (j > i)
			j--;
	}

	if (!_entities[j]->HasLife())
	{
		tempRef = _entities[j];
		static_cast<Enemy*>(tempRef)->KillByPlayer();
		delete tempRef;
	}
}
