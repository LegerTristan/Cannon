#include <iostream>
#include <string>
#include "HUD.h"
#include "Constants.h"
#include "Game.h"

using namespace std;

Font* HUD::mFont = nullptr;

HUD::HUD()
{
	// Set sprite's texture and settings
	Texture* temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Cloud.png").get();
	mBackground.setTexture(*temp);
	mBackground.setOrigin(Vector2f(temp->getSize().x / 2.0f, temp->getSize().y / 2.0f));
	mBackground.setPosition(Vector2f(WINDOW_WIDTH / 2, -HUD_Y_OFFSET));

	// Set game's font
	mFont = new Font();
	mFont->loadFromFile("Assets/Font/SUPER_BOOM.ttf");

	// Set wave's text
	mWaveText = new FlickerText("WAVE INCOMING");
	mWaveText->setFillColor(Color::Red);
	mWaveText->setCharacterSize(HUD_CHARACTER_SIZE);
	mWaveText->setOrigin(Vector2f(mWaveText->getCharacterSize() / 2.0f, mWaveText->getCharacterSize() / 2.0f));
	mWaveText->setPosition(Vector2f((WINDOW_WIDTH / 2) - WAVE_TEXT_OFFSET.x, WAVE_TEXT_OFFSET.y));
	mWaveText->setFont(*mFont);

	// Set timer's text
	mTimerText = Text();
	mTimerText.setFillColor(Color::Black);
	mTimerText.setCharacterSize(HUD_CHARACTER_SIZE);
	mTimerText.setOrigin(Vector2f(mTimerText.getCharacterSize() / 2.0f, mTimerText.getCharacterSize() / 2.0f));
	mTimerText.setPosition(Vector2f((WINDOW_WIDTH / 2) - (mTimerText.getCharacterSize() / 2), HUD_Y_OFFSET));
	mTimerText.setFont(*mFont);
}

HUD::~HUD()
{
	delete mFont;
	delete mWaveText;
}

Font* HUD::GetGameFont()
{
	return mFont;
}

void HUD::UpdateTimerText(const float& _currentTime)
{
	int minutes = (int)_currentTime / 60;
	int seconds = (int)_currentTime % 60;
	char* test = (char*)malloc(sizeof(char) * 6);
	snprintf(test, 6, "%02d:%02d", minutes, seconds);

	mTimerText.setString(test);
	free(test);
}

void HUD::UpdateWaveText(const bool& _incomingWave)
{
	if (_incomingWave)
	{
		mWaveText->GetFlickerTimeline()->Start();
	}

	mWaveText->GetFlickerTimeline()->UpdateTimeline();
}

void HUD::DrawHUD(RenderWindow* _window) const
{
	_window->draw(mBackground);
	_window->draw(mTimerText);
	_window->draw(*mWaveText);
}
