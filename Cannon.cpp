#include <iostream>
#include "Cannon.h"
#include "Utilities.h"
#include "ScalarUpgradeComponent.h"
#include "Game.h"
#include "Gauge.h"
#include "CannonBall.h"
#include "EntityFactory.h"
#include "TextureManager.h"

using namespace std;

Cannon::Cannon(Vector2f _position)
{

	// Set static part sprite and transform settings
	Texture* temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Cannon_StaticPart.png").get();
	setTexture(*temp, true);

	setOrigin(Vector2f(temp->getSize().x / 2, (temp->getSize().y / 2)));
	setPosition(_position);
	setScale(DEFAULT_SCALE);
	setRotation(DEFAULT_ROTATION);

	// Set sprite's texture and and transform settings
	temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Cannon_MovingPart.png").get();
	mMovingPartSprite.setTexture(*temp, true);

	mMovingPartSprite.setOrigin(Vector2f(temp->getSize().x / 2, (temp->getSize().y / 2)));
	mMovingPartSprite.setPosition(_position + MOVING_PART_OFFSET);
	mMovingPartSprite.setScale(DEFAULT_SCALE);
	mMovingPartSprite.setRotation(DEFAULT_ROTATION);

	// Set Gauge and shoot parameters
	mCannonGauge = new Gauge(false, Vector2f(40.0f, 550.0f));
	mIsCharging = false;

	// Set scalar upgrade component
	mFireLoadUp = new ScalarUpgradeComponent<Cannon, float>(this, &Cannon::GetFireLoadPower, mFirePower, 
		"Load speed increase !", "Assets/Textures/Up_Cannon_LoadSpeed.png", UpgradeType::ALLY);
}

Cannon::~Cannon()
{
	delete mCannonGauge;
}

Sprite Cannon::GetMovingPartSprite() const
{
	return mMovingPartSprite;
}

bool Cannon::GetPreparingFire() const
{
	return mIsCharging;
}

float Cannon::GetFireLoadPower(const float _upgradeValue) const
{
	return mFirePower + Game::GetInstance()->GetTimer()->GetDeltaTime() * (DEFAULT_LOAD_SPEED + _upgradeValue * LOAD_SPEED_SCALAR);
}

void Cannon::SetPreparingFire(const bool& _prepareFire)
{
	mIsCharging = _prepareFire;
}

void Cannon::SetMoveState(const CannonMove& _state)
{
	mMoveState = _state;
}

void Cannon::UpdateRotAngle()
{
	const float toAdd = (ADDING_ANGLE * Game::GetInstance()->GetTimer()->GetDeltaTime());

	if (mMoveState == CannonMove::UP)
		mMovingPartSprite.setRotation(
			Utilities::Clamp<float>(mMovingPartSprite.getRotation() - toAdd, MIN_CANNON_ROTATION, MAX_CANNON_ROTATION));
	else if (mMoveState == CannonMove::DOWN)
		mMovingPartSprite.setRotation(
			Utilities::Clamp<float>(mMovingPartSprite.getRotation() + toAdd, MIN_CANNON_ROTATION, MAX_CANNON_ROTATION));
}

void Cannon::Update(RenderWindow* _window)
{

	if (mIsCharging)
		UpdateFirePower();

	_window->draw(mMovingPartSprite);		// Necessary to draw the cannon in this order
	_window->draw(*this);					// to have the moving part on the right Z index

	// Update cannon gauge
	mCannonGauge->DrawGauge(_window);
}

void Cannon::UpdateFirePower()
{
	mFireLoadUp->ComputeValue();

	if (!mIsCharging)
		mIsCharging = true;

	mFirePower = Utilities::Clamp<float>(mFirePower, MIN_CANNON_FIRE_POWER, MAX_CANNON_FIRE_POWER);
	mCannonGauge->FillGauge((mFirePower - MIN_CANNON_FIRE_POWER) / (MAX_CANNON_FIRE_POWER - MIN_CANNON_FIRE_POWER));
}

void Cannon::LaunchCannonBall()
{
	if(Game::GetInstance()->GetTimer()->GetCurrentTime() >= mFireTime)
	{
		const float cosPos = cosf((mMovingPartSprite.getRotation() - ROTATION_OFFSET) * RADIAN_CONVERSION);
		const float sinPos = sinf((mMovingPartSprite.getRotation() - ROTATION_OFFSET) * RADIAN_CONVERSION);

		const Vector2f spawnPoint = mMovingPartSprite.getPosition() + Vector2f(cosPos, sinPos) * DIST_FROM_CANNON;

		EntityFactory::CreateEntity<CannonBall>(spawnPoint, Vector2f(cosPos, sinPos) * mFirePower);

		// After shoot, we reset all members tied to the shoot to prepare the next one
		mFireTime = Game::GetInstance()->GetTimer()->GetCurrentTime() + mFireRate;
		mIsCharging = false;
		mFirePower = MIN_CANNON_FIRE_POWER;
		mCannonGauge->FillGauge(0.0f);
	}
}

void Cannon::UpgradeSpeed()
{
	mFireLoadUp->UpRank();
}
