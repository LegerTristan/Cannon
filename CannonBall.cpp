#include "TimeManager.h"
#include "CannonBall.h"
#include "Game.h"
#include "ScalarUpgradeComponent.h"

Vector2f CannonBall::mBallScale = Vector2f(0.2f, 0.2f);
short CannonBall::mMaxBallLife = 1;
ScalarUpgradeComponent<CannonBall, Vector2f>* CannonBall::mScaleUp = nullptr;
ScalarUpgradeComponent<CannonBall, short>* CannonBall::mLifeUp = nullptr;

CannonBall::CannonBall(const Vector2f _position, const Vector2f _velocity)
	: Entity(_position, Game::GetInstance()->GetTextureManager()->GetTexture(CANNON_BALL_TEXTURE).get())
{
	if (!mScaleUp)
		mScaleUp = new ScalarUpgradeComponent<CannonBall, Vector2f>(this, &CannonBall::ComputeScale, mBallScale,
			"Balls are bigger !", "Assets/Textures/Up_Bigger_Ball.png", UpgradeType::ALLY, 3);

	if (!mLifeUp)
		mLifeUp = new ScalarUpgradeComponent<CannonBall, short>(this, &CannonBall::ComputeLife, mMaxBallLife, 
			"Can hit more enemies !", "Assets/Textures/Up_Perforation_Ball.png", UpgradeType::ALLY, 2);

	// Set sprite's texture and and transform settings
	setScale(mBallScale);

	// Set movement component
	mMoveComp = new ParabolicMoveComponent(this, _velocity);

	// Set collision component
	mCollisionComp = new CollisionComponent(this, CollisionTag::BALL, "Assets/JSON/CannonBall.json");

	// Set cannon's ball life
	mLife = mMaxBallLife;
}

Vector2f CannonBall::ComputeScale(const float _upgradeValue) const
{
	const float computedValue = DEFAULT_BALL_SCALE + _upgradeValue / BALL_SCALE_SCALAR;
	return Vector2f(computedValue, computedValue);
}

short CannonBall::ComputeLife(const float _upgradeRank) const
{
	return DEFAULT_BALL_LIFE + static_cast<short>(_upgradeRank);
}

void CannonBall::Update(RenderWindow* _window)
{
	if (!mMoveComp->Move())
		delete this;
	else
	{
		mCollisionComp->SetHitBox({ (float)getPosition().x, (float)getPosition().y, (float)getTextureRect().width, (float)getTextureRect().height });
		_window->draw(*this);
		_window->draw(mCollisionComp->GetHitBox());
	}
}
