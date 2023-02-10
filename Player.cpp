#include <string>

#include "Player.h"
#include "Constants.h"
#include "HUD.h"
#include "Game.h"

Player::Player()
{
	// Set player's level
	mCurrentLevel = 1;
	mCurrentXP = 0.0f;
	mMaxXP = MAX_XP_START;

	// Set player's life bar
	mLifeBar = new LifeBar({ WINDOW_WIDTH / 2 - LIFEBAR_POS.x, LIFEBAR_POS.y});

	// Set player's level display
	mLevelText = Text();
	mLevelText.setFillColor(Color::Black);
	mLevelText.setCharacterSize(LEVEL_CHARACTER_SIZE);
	mLevelText.setOrigin({ mLevelText.getCharacterSize() / 2.0f, mLevelText.getCharacterSize() / 2.0f });
	mLevelText.setPosition({ (WINDOW_WIDTH / 2) - TEXT_POS.x, TEXT_POS.y });
	mLevelText.setFont(*HUD::GetGameFont());
	mLevelText.setString("Lv" + std::to_string(mCurrentLevel));

	// Set level's gauge
	mLevelGauge = new Gauge(true, { (WINDOW_WIDTH / 2) - GAUGE_POS.x, GAUGE_POS.y }, GAUGE_SIZE, GAUGE_COLOR);
}

Player::~Player()
{
	delete mLifeBar;
	delete mLevelGauge;
}

LifeBar* Player::GetLifeBar() const
{
	return mLifeBar;
}

void Player::IncreaseLevel()
{
	mCurrentLevel++;
	mMaxXP *= XP_SCALAR;

	// Display the new current level
	mLevelText.setString("LV" + std::to_string(mCurrentLevel));
	Game::GetInstance()->UpdateUpgradeMenu(true);
}

void Player::IncreaseXP(const float& _amount)
{
	mCurrentXP += _amount;

	if (mCurrentXP >= mMaxXP)
	{
		const float tempXP = mCurrentXP - mMaxXP;
		IncreaseLevel();
		mCurrentXP = tempXP;
	}

	mLevelGauge->FillGauge(mCurrentXP / mMaxXP);
}

void Player::DrawPlayerInfo(RenderWindow* _window)
{
	mLifeBar->DrawHP(_window);
	_window->draw(mLevelText);
	mLevelGauge->DrawGauge(_window);
}
