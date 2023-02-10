#include "LifeBar.h"
#include "Game.h"

LifeBar::LifeBar(Vector2f _position)
{
	mPlayerLife = DEFAULT_PLAYER_LIFE;
	mPosition = _position;

	// Set heart's texture and sprites of life bar.
	Texture* temp = Game::GetInstance()->GetTextureManager()->GetTexture("Assets/Textures/Heart.png").get();

	for (int i = 0; i < DEFAULT_PLAYER_LIFE; ++i)
	{
		mLifeSprites[i] = Sprite();
		mLifeSprites[i].setTexture(*temp);
		mLifeSprites[i].setOrigin(Vector2f(temp->getSize().x / 2.0f, temp->getSize().y / 2.0f));
		mLifeSprites[i].setPosition(Vector2f(mPosition.x + i * SPACE_BETWEEN_LIFE, mPosition.y));
		mLifeSprites[i].setScale(HEART_SPRITE_SCALE);
	}
}

int LifeBar::GetPlayerLife() const
{
	return mPlayerLife;
}

void LifeBar::DrawHP(RenderWindow* _window)
{
	for (int i = 0; i < DEFAULT_PLAYER_LIFE; ++i)
	{
		_window->draw(mLifeSprites[i]);
	}
}

void LifeBar::DecreaseHP(const int& _amount)
{
	unsigned int i = 0;

	while ( i < _amount && mPlayerLife > 0)
	{
		mPlayerLife--;
		mLifeSprites[mPlayerLife].setColor(Color::Transparent);
	}
		
}
