#include "FloatMoveComponent.h"
#include "ScalarUpgradeComponent.h"
#include "Game.h"
#include "Utilities.h"
#include "LevelState.h"

ScalarUpgradeComponent<FloatMoveComponent, float>* FloatMoveComponent::mVariationUp = nullptr;
float FloatMoveComponent::mFloatVariation = 10.0f;

FloatMoveComponent::FloatMoveComponent(Entity* _entity, Vector2f _velocity)
	: MoveComponent(_entity, _velocity)
{
 	if (!mVariationUp)
		mVariationUp = new ScalarUpgradeComponent<FloatMoveComponent, float>(this, &FloatMoveComponent::ComputeFloatVariation,
			FloatMoveComponent::mFloatVariation, "Float movement increased !", "Assets/Textures/Up_FloatEnemy_Variation.png",
			UpgradeType::ENEMY, 4);

}

float FloatMoveComponent::ComputeFloatVariation(const float _upgradeValue) const
{
	return DEFAULT_FLOAT_VARIATION + (FLOAT_VARIATION_SCALAR * _upgradeValue);
}

Vector2f FloatMoveComponent::GetTrajectory()
{
	mCurrentTime = Game::GetInstance()->GetTimer()->GetCurrentTime();
	float elapsedTime = (mCurrentTime - mInitialTime) * FLOW_SPEED;

	Vector2f currentVelocity = Vector2f(mVelocity.x * elapsedTime, sinf(elapsedTime) * mFloatVariation);

	return currentVelocity;
}

bool FloatMoveComponent::Move()
{
	mOwner->setPosition(mInitialPos + GetTrajectory());

	if (IsOwnerOutsideScreen())
	{
		LevelState::GetInstance()->RemoveEntity(mOwner);
		return false;
	}

	return true;
}