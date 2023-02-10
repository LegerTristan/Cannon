#include "Entity.h"
#include "LevelState.h"

Entity::Entity(const Vector2f _position, const Texture* _texture)
{

	// Set entity's sprite & settings
	setTexture(*_texture, true);
	setOrigin(Vector2f(_texture->getSize().x / 2, (_texture->getSize().y / 2)));
	setPosition(_position);

	mCollisionComp = nullptr;
	mMoveComp = nullptr;

	mLife = 0;
}

Entity::~Entity()
{
	if (mCollisionComp)
		delete mCollisionComp;

	if (mMoveComp)
		delete mMoveComp;
}

CollisionComponent* Entity::GetCollisionComp() const
{
	return mCollisionComp;
}

bool Entity::HasLife() const
{
	return mLife > 0;
}

void Entity::DecreaseLife()
{
	mLife--;
}

void Entity::Die()
{
	LevelState::GetInstance()->RemoveEntity(this);
}
