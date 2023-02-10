#include <fstream>
#include <iostream>

#include "CollisionComponent.h"
#include "json.hpp"

using json = nlohmann::json;

CollisionComponent::CollisionComponent(Entity* _entity, const CollisionTag _tag, const char* _hitBoxPath)
    : EntityComponent(_entity)
{
    mCollisionTag = _tag;

    json tempFile;
    std::ifstream i(_hitBoxPath);
    i >> tempFile;

    if (tempFile.is_object())
    {
        mHitBox.setSize({ tempFile["hitbox"]["w"] * mOwner->getScale().x,
            tempFile["hitbox"]["h"] * mOwner->getScale().y});
        mHitBox.setOrigin((mHitBox.getSize().x / 2.0f) + tempFile["hitbox"]["offsetX"],
            (mHitBox.getSize().y / 2.0f) + tempFile["hitbox"]["offsetY"]);
    }
    else
        throw "JSON file element \"hitbox\" not corresponding to type object.";

    mHitBox.setFillColor(Color::Transparent);
    mHitBox.setOutlineThickness(1);
    mHitBox.setOutlineColor(Color::Black);
}

CollisionTag CollisionComponent::GetCollisionTag() const
{
    return mCollisionTag;
}

RectangleShape CollisionComponent::GetHitBox() const
{
    return mHitBox;
}

void CollisionComponent::SetHitBox(const FloatRect& _newHitBox)
{
    mHitBox.setPosition(_newHitBox.left, _newHitBox.top);

}

bool CollisionComponent::CollideWith(const CollisionComponent* _otherCollision)
{
    const FloatRect otherRect = _otherCollision->GetHitBox().getGlobalBounds();

    return mHitBox.getGlobalBounds().intersects(otherRect);
}
