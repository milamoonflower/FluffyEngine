#pragma once
#include "SpriteColliderComponent.h"
#include "GameObject.h"
#include "Rectf.h"
#include "Sprite.h"

namespace Fluffy
{
	SpriteColliderComponent::SpriteColliderComponent(GameObject* pOwner, const Sprite* pSprite, const std::string& collisionLayerName)
		: RectColliderComponent(pOwner, {}, collisionLayerName)
		, m_pSprite{ pSprite }
	{

	}

	Rectf SpriteColliderComponent::GetRect() const
	{
		return m_pSprite->GetRect();
	}
}
